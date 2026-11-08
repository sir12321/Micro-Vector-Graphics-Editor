#include <cctype>
#include <stdexcept>

#include "diagram.h"

// Generates SVG string representation of the diagram
// The canvas is infinite, so objects can be at negative or far-away
// coordinates. The SVG size/viewBox is the union of all bounding boxes (plus a
// margin) so other viewers show the whole drawing. It is only added for files:
// undo snapshots and change detection leave it out, since text bounding boxes
// are only refreshed when the text is drawn.
std::string Diagram::ToSvg(bool fit_view_box) const {
  // Objects that write nothing (e.g. an empty text box) are skipped entirely
  std::string body;
  for (const auto& obj : objects_) {
    std::string element = obj->ToSvg();
    if (!element.empty()) body += "    " + element;
  }

  std::string out = "<svg xmlns=\"http://www.w3.org/2000/svg\"";
  if (fit_view_box && !body.empty()) {
    const double margin = 10;
    QRectF r = BoundingRect().adjusted(-margin, -margin, margin, margin);
    std::string w = std::to_string(r.width());
    std::string h = std::to_string(r.height());
    out += " width=\"" + w + "\" height=\"" + h + "\" viewBox=\"" +
           std::to_string(r.left()) + " " + std::to_string(r.top()) + " " + w +
           " " + h + "\"";
  }
  out += ">\n" + body + "</svg>\n";
  return out;
}

// Helper to split string by newlines for parsing
std::vector<std::string> split_by_newline(const std::string& s) {
  std::vector<std::string> result;
  std::string current;
  for (char c : s) {
    if (c == '\n') {
      result.push_back(current);
      current.clear();
    } else {
      current += c;
    }
  }
  if (!current.empty()) {
    result.push_back(current);
  }
  return result;
}

// Parses SVG string to reconstruct diagram objects
// Here npos is a const, predefined by std::string class
void Diagram::FromSvg(const std::string& svg) {
  Clear();
  std::size_t pos = 0;
  while ((pos = svg.find('<', pos)) != std::string::npos) {
    std::size_t end = std::string::npos;
    std::string tag_name;

    // Check for each tag type
    if (svg.compare(pos, 5, "<rect") == 0) {
      tag_name = "rect";
      end = svg.find('>', pos);
    } else if (svg.compare(pos, 8, "<ellipse") == 0) {
      tag_name = "ellipse";
      end = svg.find('>', pos);
    } else if (svg.compare(pos, 7, "<circle") == 0) {
      tag_name = "ellipse";  // circle is read as an ellipse with rx = ry = r
      end = svg.find('>', pos);
    } else if (svg.compare(pos, 5, "<line") == 0) {
      tag_name = "line";
      end = svg.find('>', pos);
    } else if (svg.compare(pos, 8, "<polygon") == 0) {
      tag_name = "polygon";
      end = svg.find('>', pos);
    } else if (svg.compare(pos, 5, "<text") == 0) {
      tag_name = "text";
      end = svg.find("</text>", pos);
      if (end != std::string::npos) end += 6;
    } else if (svg.compare(pos, 5, "<path") == 0) {
      tag_name = "path";
      end = svg.find('>', pos);
    }

    if (end != std::string::npos) {
      std::string element = svg.substr(pos, end - pos + 1);
      // Bad numbers make stod/stoi throw: skip that element instead of crashing
      try {
        if (tag_name == "rect") {
          if (element.find("rx=\"") != std::string::npos) {
            RoundedRectangle temp(0, 0, 0, 0, 10.0, 1);
            AddObject(temp.FromSvg(element));
          } else {
            Rectangle temp(0, 0, 0, 0, 1);
            AddObject(temp.FromSvg(element));
          }
        } else if (tag_name == "ellipse") {
          // For <circle>, rewrite r="v" as rx="v" ry="v" to parse as ellipse
          if (element.compare(0, 7, "<circle") == 0) {
            std::size_t r = element.find("r=\"");
            while (r != std::string::npos && !std::isspace(element[r - 1]))
              r = element.find("r=\"", r + 1);
            std::size_t r_end = element.find('"', r + 3);
            if (r != std::string::npos && r_end != std::string::npos) {
              std::string v = element.substr(r + 3, r_end - r - 3);
              element.replace(r, r_end - r + 1,
                              "rx=\"" + v + "\" ry=\"" + v + "\"");
            }
          }
          Circle temp(0, 0, 0, 1);
          AddObject(temp.FromSvg(element));
        } else if (tag_name == "line") {
          Line temp(0, 0, 0, 0, 1);
          AddObject(temp.FromSvg(element));
        } else if (tag_name == "polygon") {
          Hexagon temp(0, 0, 0, 0, 1);
          AddObject(temp.FromSvg(element));
        } else if (tag_name == "text") {
          TextObject temp(0, 0, "", 12, "DejaVu Sans");
          AddObject(temp.FromSvg(element));
        } else if (tag_name == "path") {
          Freehand temp;
          AddObject(temp.FromSvg(element));
        }
      } catch (const std::exception&) {
        // Malformed element: ignored, rest of the file still loads
      }
      pos = end + 1;
    } else {
      pos++;
    }
  }
}