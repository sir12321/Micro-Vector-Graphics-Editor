#include <cmath>
#include <iostream>
#include <sstream>

#include "../../headers/hexagon.h"

using namespace std;

// Exports to SVG.
string Hexagon::ToSvg() const {
  string points;

  double vx = x_ - cx_;
  double vy = y_ - cy_;
  for (int i = 0; i < 6; ++i) {
    double angle = i * M_PI / 3.0;
    double rx = vx * std::cos(angle) - vy * std::sin(angle);
    double ry = vx * std::sin(angle) + vy * std::cos(angle);
    points += std::to_string(cx_ + rx) + "," + std::to_string(cy_ + ry);
    if (i != 5) points += " ";
  }

  return "<polygon points=\"" + points + "\" fill=\"" + fill_color_ +
         "\" stroke=\"" + stroke_color_ + "\" stroke-width=\"" +
         to_string(stroke_width_) + "\" />\n";
}

// Helper for parsing SVG attributes.
vector<std::string> split_by_space_hexagon(const std::string& s) {
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
std::unique_ptr<GraphicsObject> Hexagon::FromSvg(const std::string& svg) {
  double cx = 0, cy = 0, x = 0, y = 0;
  int stroke_width = 0;
  std::string fill_color = "white", stroke_color = "black";

  size_t sw_pos = svg.find("stroke-width=\"");
  if (sw_pos != std::string::npos) {
    try {
      size_t sw_end = svg.find("\"", sw_pos + 14);
      stroke_width = std::stoi(svg.substr(sw_pos + 14, sw_end - (sw_pos + 14)));
    } catch (...) {
    }
  }

  size_t stroke_pos = svg.find("stroke=\"");
  if (stroke_pos != std::string::npos) {
    try {
      size_t stroke_end = svg.find("\"", stroke_pos + 8);
      stroke_color = svg.substr(stroke_pos + 8, stroke_end - (stroke_pos + 8));
    } catch (...) {
    }
  }

  size_t fill_pos = svg.find("fill=\"");
  if (fill_pos != std::string::npos) {
    try {
      size_t fill_end = svg.find("\"", fill_pos + 6);
      fill_color = svg.substr(fill_pos + 6, fill_end - (fill_pos + 6));
    } catch (...) {
    }
  }

  size_t points_pos = svg.find("points=\"");
  if (points_pos != std::string::npos) {
    try {
      size_t points_start = points_pos + 8;
      size_t points_end = svg.find("\"", points_start);
      std::string points_str =
          svg.substr(points_start, points_end - points_start);

      std::vector<std::pair<double, double>> points_list;
      std::stringstream ss(points_str);
      std::string point_pair;
      while (ss >> point_pair) {
        size_t comma = point_pair.find(',');
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