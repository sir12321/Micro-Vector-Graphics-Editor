#include "../../headers/circle.h"

using namespace std;

// Exports to SVG.
string Circle::ToSvg() const {
  return "<circle cx=\"" + to_string(cx_) + "\" cy=\"" + to_string(cy_) +
         "\" rx=\"" + to_string(rx_) + "\" ry=\"" + to_string(ry_) +
         "\" fill=\"" + fill_color_ + "\" stroke=\"" + stroke_color_ +
         "\" stroke-width=\"" + to_string(stroke_width_) + "\" />\n";
}

// Helper to parse space-separated attributes.
vector<std::string> split_by_space_circle(const std::string& s) {
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

// Imports from SVG.
std::unique_ptr<GraphicsObject> Circle::FromSvg(const std::string& svg) {
  double cx = 0, cy = 0, rx = 0, ry = 0;
  int stroke_width = 0;
  std::string fill_color = "white", stroke_color = "black";
  vector<std::string> parts = split_by_space_circle(svg);
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
      } else if (part.find("fill=\"") != std::string::npos) {
        fill_color = part.substr(part.find("fill=\"") + 6,
                                 part.find("\"", part.find("fill=\"") + 6) -
                                     (part.find("fill=\"") + 6));
      } else if (part.find("cx=\"") != std::string::npos) {
        cx = std::stod(part.substr(part.find("cx=\"") + 4,
                                   part.find("\"", part.find("cx=\"") + 4) -
                                       (part.find("cx=\"") + 4)));
      } else if (part.find("cy=\"") != std::string::npos) {
        cy = std::stod(part.substr(part.find("cy=\"") + 4,
                                   part.find("\"", part.find("cy=\"") + 4) -
                                       (part.find("cy=\"") + 4)));
      } else if (part.find("rx=\"") != std::string::npos) {
        rx = std::stod(part.substr(part.find("rx=\"") + 4,
                                   part.find("\"", part.find("rx=\"") + 4) -
                                       (part.find("rx=\"") + 4)));
      } else if (part.find("ry=\"") != std::string::npos) {
        ry = std::stod(part.substr(part.find("ry=\"") + 4,
                                   part.find("\"", part.find("ry=\"") + 4) -
                                       (part.find("ry=\"") + 4)));
      } else if (part.find("stroke=\"") != std::string::npos) {
        stroke_color = part.substr(part.find("stroke=\"") + 8,
                                   part.find("\"", part.find("stroke=\"") + 8) -
                                       (part.find("stroke=\"") + 8));
      }
    } catch (...) {
      // Skip invalid attributes
    }
  }

  auto obj = std::make_unique<Circle>(cx, cy, (rx + ry) / 2, stroke_width);
  obj->SetGeometry(cx, cy, 0, 0, 0, cx + rx, cy + ry);
  obj->SetFillColor(fill_color);
  obj->SetStrokeWidth(stroke_width);
  obj->SetStrokeColor(stroke_color);
  return obj;
}