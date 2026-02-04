#include <algorithm>

#include "../../headers/rounded_rectangle.h"

using namespace std;

// Exports to SVG. Note use of 'rx' and 'ry'.
string RoundedRectangle::ToSvg() const {
  return "<rect x=\"" + to_string(cx_ - width_ / 2.0) + "\" y=\"" +
         to_string(cy_ - height_ / 2.0) + "\" width=\"" + to_string(width_) +
         "\" height=\"" + to_string(height_) + "\" rx=\"" + to_string(radius_) +
         "\" ry=\"" + to_string(radius_) + "\" fill=\"" + fill_color_ +
         "\" stroke=\"" + stroke_color_ + "\" stroke-width=\"" +
         to_string(stroke_width_) + "\" />\n";
}

// Helper for parsing spaces.
vector<std::string> split_by_space_rr(const std::string& s) {
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

// Parses SVG to create RoundedRectangle.
std::unique_ptr<GraphicsObject> RoundedRectangle::FromSvg(
    const std::string& svg) {
  double x = 0, y = 0, width = 0, height = 0, radius = 10.0;
  int stroke_width = 0;
  std::string fill_color = "white", stroke_color = "black";
  vector<std::string> parts = split_by_space_rr(svg);
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
      } else if (part.find("width=\"") != std::string::npos) {
        width =
            std::stod(part.substr(part.find("width=\"") + 7,
                                  part.find("\"", part.find("width=\"") + 7) -
                                      (part.find("width=\"") + 7)));
      } else if (part.find("height=\"") != std::string::npos) {
        height =
            std::stod(part.substr(part.find("height=\"") + 8,
                                  part.find("\"", part.find("height=\"") + 8) -
                                      (part.find("height=\"") + 8)));
      } else if (part.find("rx=\"") != std::string::npos) {
        radius = std::stod(part.substr(part.find("rx=\"") + 4,
                                       part.find("\"", part.find("rx=\"") + 4) -
                                           (part.find("rx=\"") + 4)));
      } else if (part.find("ry=\"") != std::string::npos) {
        // ry is ignored since we use a single radius value
      } else if (part.find("fill=\"") != std::string::npos) {
        fill_color = part.substr(part.find("fill=\"") + 6,
                                 part.find("\"", part.find("fill=\"") + 6) -
                                     (part.find("fill=\"") + 6));
      } else if (part.find("x=\"") != std::string::npos) {
        x = std::stod(part.substr(
            part.find("x=\"") + 3,
            part.find("\"", part.find("x=\"") + 3) - (part.find("x=\"") + 3)));
      } else if (part.find("y=\"") != std::string::npos) {
        y = std::stod(part.substr(
            part.find("y=\"") + 3,
            part.find("\"", part.find("y=\"") + 3) - (part.find("y=\"") + 3)));
      }
    } catch (...) {
      // Skip invalid attributes
    }
  }

  auto obj = std::make_unique<RoundedRectangle>(
      x + width / 2.0, y + height / 2.0, width, height, radius, stroke_width);
  obj->SetFillColor(fill_color);
  obj->SetStrokeColor(stroke_color);
  return obj;
}