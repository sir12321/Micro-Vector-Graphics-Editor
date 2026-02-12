#include <cmath>
#include <iostream>
#include <sstream>

#include "../../headers/hexagon.h"

// Exports to SVG
std::string Hexagon::ToSvg() const {
  std::string points;

  double vx = x_ - cx_;
  double vy = y_ - cy_;
  for (int i = 0; i < 6; ++i) {
    double angle = i * M_PI / 3.0;
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
  if (points_pos != std::string::npos) {
    try {
      std::size_t points_start = points_pos + 8;
      std::size_t points_end = svg.find("\"", points_start);
      std::string points_str =
          svg.substr(points_start, points_end - points_start);

      std::vector<std::pair<double, double>> points_list;
      std::stringstream ss(points_str);
      std::string point_pair;
      while (ss >> point_pair) {
        std::size_t comma = point_pair.find(',');
        if (comma != std::string::npos) {
          double px = std::stod(point_pair.substr(0, comma));
          double py = std::stod(point_pair.substr(comma + 1));
          points_list.push_back({px, py});
        }
      }
      if (points_list.size() >= 4) {
        x = points_list[0].first;
        y = points_list[0].second;
        cx = (points_list[0].first + points_list[3].first) / 2.0;
        cy = (points_list[0].second + points_list[3].second) / 2.0;
      }
    } catch (...) {
      // Skip invalid attributes
    }
  }

  auto obj = std::make_unique<Hexagon>(cx, cy, x, y, stroke_width);
  obj->SetFillColor(fill_color);
  obj->SetStrokeWidth(stroke_width);
  obj->SetStrokeColor(stroke_color);
  return obj;
}