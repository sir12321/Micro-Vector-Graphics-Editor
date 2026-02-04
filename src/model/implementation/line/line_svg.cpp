#include <algorithm>

#include "../../headers/line.h"

using namespace std;

// Exports to SVG.
string Line::ToSvg() const {
  return "<line x1=\"" + to_string(x1_) + "\" y1=\"" + to_string(y1_) +
         "\" x2=\"" + to_string(x2_) + "\" y2=\"" + to_string(y2_) +
         "\" stroke=\"" + stroke_color_ + "\" stroke-width=\"" +
         to_string(stroke_width_) + "\" />\n";
}

// Helper for parsing line SVG.
vector<std::string> split_by_space_line(const std::string& s) {
  vector<std::string> result;
  std::string current;
  for (char c : s) {
    if (c == ' ') {
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

// Parses SVG string to check for x1, y1, x2, y2 attributes.
std::unique_ptr<GraphicsObject> Line::FromSvg(const std::string& svg) {
  double x1 = 0, y1 = 0, x2 = 0, y2 = 0;
  int stroke_width = 0;
  std::string stroke_color = "black";
  vector<std::string> parts = split_by_space_line(svg);
  for (const std::string& part : parts) {
    try {
      // Check complex attributes first to avoid substring matches
      if (part.find("stroke-width=\"") != std::string::npos) {
        stroke_width = std::stoi(
            part.substr(part.find("stroke-width=\"") + 14,
                        part.find("\"", part.find("stroke-width=\"") + 14) -
                            (part.find("stroke-width=\"") + 14)));
      } else if (part.find("stroke=\"") != std::string::npos) {
        stroke_color = part.substr(part.find("stroke=\"") + 8,
                                   part.find("\"", part.find("stroke=\"") + 8) -
                                       (part.find("stroke=\"") + 8));
      } else if (part.find("x1=\"") != std::string::npos) {
        x1 = std::stod(part.substr(part.find("x1=\"") + 4,
                                   part.find("\"", part.find("x1=\"") + 4) -
                                       (part.find("x1=\"") + 4)));
      } else if (part.find("y1=\"") != std::string::npos) {
        y1 = std::stod(part.substr(part.find("y1=\"") + 4,
                                   part.find("\"", part.find("y1=\"") + 4) -
                                       (part.find("y1=\"") + 4)));
      } else if (part.find("x2=\"") != std::string::npos) {
        x2 = std::stod(part.substr(part.find("x2=\"") + 4,
                                   part.find("\"", part.find("x2=\"") + 4) -
                                       (part.find("x2=\"") + 4)));
      } else if (part.find("y2=\"") != std::string::npos) {
        y2 = std::stod(part.substr(part.find("y2=\"") + 4,
                                   part.find("\"", part.find("y2=\"") + 4) -
                                       (part.find("y2=\"") + 4)));
      }
    } catch (...) {
      // Skip invalid attributes
    }
  }

  auto obj = std::make_unique<Line>(x1, y1, x2, y2, stroke_width);
  obj->SetStrokeColor(stroke_color);
  obj->SetStrokeWidth(stroke_width);
  return obj;
}