#include "diagram.h"

// Generates SVG string representation of the diagram
// here width and height of canvas is set to default, can't be controlled by
// user
std::string Diagram::ToSvg() const {
  std::string out = "";
  out += "<svg\">\n";
  for (const auto& obj : objects_) {
    out += "    " + obj->ToSvg();
  }
  out += "</svg>\n";
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
      if (tag_name == "rect") {
        if (element.find("rx=\"") != std::string::npos) {
          RoundedRectangle temp(0, 0, 0, 0, 10.0, 1);
          AddObject(temp.FromSvg(element));
        } else {
          Rectangle temp(0, 0, 0, 0, 1);
          AddObject(temp.FromSvg(element));
        }
      } else if (tag_name == "ellipse") {
        Circle temp(0, 0, 0, 1);
        AddObject(temp.FromSvg(element));
      } else if (tag_name == "line") {
        Line temp(0, 0, 0, 0, 1);
        AddObject(temp.FromSvg(element));
      } else if (tag_name == "polygon") {
        Hexagon temp(0, 0, 0, 0, 1);
        AddObject(temp.FromSvg(element));
      } else if (tag_name == "text") {
        TextObject temp(0, 0, "", 12, "Deja Vu Sans");
        AddObject(temp.FromSvg(element));
      } else if (tag_name == "path") {
        Freehand temp;
        AddObject(temp.FromSvg(element));
      }
      pos = end + 1;
    } else {
      pos++;
    }
  }
}