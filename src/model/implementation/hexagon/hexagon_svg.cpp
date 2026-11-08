#include <algorithm>
#include <cmath>
#include <iostream>
#include <sstream>

#include "../../headers/hexagon.h"

namespace {
// Pi as a standard C++ constant (M_PI is non-standard and is missing on
// MSVC unless _USE_MATH_DEFINES is set)
constexpr double kPi = 3.14159265358979323846;
}  // namespace

// Exports to SVG
std::string Hexagon::ToSvg() const {
  std::string points;

  double vx = x_ - cx_;
  double vy = y_ - cy_;
  for (int i = 0; i < 6; ++i) {
    double angle = i * kPi / 3.0;
    double rx = vx * std::cos(angle) - vy * std::sin(angle);
    double ry = vx * std::sin(angle) + vy * std::cos(angle);
    points += std::to_string(cx_ + rx) + "," + std::to_string(cy_ + ry);
    if (i != 5) points += " ";
  }

  return "<polygon\n\tpoints=\"" + points + "\"\n\tfill=\"" + fill_color_ +
         "\"\n\tstroke=\"" + stroke_color_ + "\"\n\tstroke-width=\"" +
         std::to_string(stroke_width_) + "\" />\n";
}

// Helper for parsing SVG attributes
std::string get_attr_hexagon(const std::string& svg, const std::string& attr) {
  std::size_t pos = svg.find(attr + "=\"");
  if (pos != std::string::npos) {
    std::size_t start = pos + attr.length() + 2;
    std::size_t end = svg.find("\"", start);
    if (end != std::string::npos) return svg.substr(start, end - start);
  }
  // Try style attribute
  std::size_t style_pos = svg.find("style=\"");
  if (style_pos != std::string::npos) {
    std::size_t style_start = style_pos + 7;
    std::size_t style_end = svg.find("\"", style_start);
    if (style_end != std::string::npos) {
      std::string style = svg.substr(style_start, style_end - style_start);
      std::size_t attr_pos = style.find(attr + ":");
      if (attr_pos != std::string::npos) {
        std::size_t val_start = attr_pos + attr.length() + 1;
        std::size_t val_end = style.find(";", val_start);
        if (val_end == std::string::npos) val_end = style.length();
        return style.substr(val_start, val_end - val_start);
      }
    }
  }
  return "";
}

// Imports from SVG
std::unique_ptr<GraphicsObject> Hexagon::FromSvg(const std::string& svg) {
  double cx = 0, cy = 0, x = 0, y = 0;
  int stroke_width = 0;
  std::string fill_color = "white", stroke_color = "black";

  std::string val;
  if (!(val = get_attr_hexagon(svg, "stroke-width")).empty())
    stroke_width = std::stoi(val);
  if (!(val = get_attr_hexagon(svg, "fill")).empty()) fill_color = val;
  if (!(val = get_attr_hexagon(svg, "stroke")).empty()) stroke_color = val;

  std::size_t points_pos = svg.find("points=\"");
  if (points_pos == std::string::npos) return nullptr;
  std::size_t points_start = points_pos + 8;
  std::size_t points_end = svg.find("\"", points_start);
  std::string points_str = svg.substr(points_start, points_end - points_start);

  // Coordinates may be "x,y x,y ..." or "x y x y ..." (both valid SVG):
  // treat commas as spaces and read the numbers in pairs
  std::replace(points_str.begin(), points_str.end(), ',', ' ');
  std::vector<std::pair<double, double>> points_list;
  std::stringstream ss(points_str);
  double px = 0, py = 0;
  while (ss >> px >> py) points_list.push_back({px, py});

  // The hexagon is rebuilt from vertex 0 and the opposite vertex 3. With
  // fewer points (or zero size) it can't be shown, so don't create an
  // invisible object at all
  if (points_list.size() < 4) return nullptr;
  x = points_list[0].first;
  y = points_list[0].second;
  cx = (points_list[0].first + points_list[3].first) / 2.0;
  cy = (points_list[0].second + points_list[3].second) / 2.0;
  if (x == cx && y == cy) return nullptr;

  auto obj = std::make_unique<Hexagon>(cx, cy, x, y, stroke_width);
  obj->SetFillColor(fill_color);
  obj->SetStrokeWidth(stroke_width);
  obj->SetStrokeColor(stroke_color);
  return obj;
}