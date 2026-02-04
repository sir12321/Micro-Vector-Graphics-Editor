#include <QColor>
#include <QPainterPath>
#include <QPen>
#include <sstream>

#include "../../headers/freehand.h"

using namespace std;

// Exports to SVG.
std::string Freehand::ToSvg() const {
  // A single point has no visible stroke in SVG; skip.
  if (points_.size() < 2) return "";

  // Start path
  std::string d = "M " + std::to_string(points_[0].x()) + " " +
                  std::to_string(points_[0].y());
  // Line to subsequent points
  for (size_t i = 1; i < points_.size(); ++i) {
    d += " L " + std::to_string(points_[i].x()) + " " +
         std::to_string(points_[i].y());
  }

  // Match drawing style: no fill, round caps/joins
  return "<path d=\"" + d + "\" fill=\"none\" stroke=\"" + stroke_color_ +
         "\" stroke-width=\"" + std::to_string(stroke_width_) +
         "\" stroke-linecap=\"round\" stroke-linejoin=\"round\" />\n";
}

// Helper.
vector<std::string> split_by_space_freehand(const std::string& s) {
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
std::unique_ptr<GraphicsObject> Freehand::FromSvg(const std::string& svg) {
  int stroke_width = 0;
  std::string stroke_color = "black";
  std::vector<QPointF> points;

  // Parse stroke-width first
  size_t sw_pos = svg.find("stroke-width=\"");
  if (sw_pos != std::string::npos) {
    try {
      size_t sw_end = svg.find("\"", sw_pos + 14);
      stroke_width = std::stoi(svg.substr(sw_pos + 14, sw_end - (sw_pos + 14)));
    } catch (...) {
    }
  }

  // Parse stroke color
  size_t stroke_pos = svg.find("stroke=\"");
  if (stroke_pos != std::string::npos) {
    try {
      size_t stroke_end = svg.find("\"", stroke_pos + 8);
      stroke_color = svg.substr(stroke_pos + 8, stroke_end - (stroke_pos + 8));
    } catch (...) {
    }
  }

  // Parse path data - find d="..." and extract everything between quotes
  size_t d_pos = svg.find("d=\"");
  if (d_pos != std::string::npos) {
    size_t d_start = d_pos + 3;
    size_t d_end = svg.find("\"", d_start);
    if (d_end != std::string::npos) {
      std::string d_str = svg.substr(d_start, d_end - d_start);

      // Parse path data: M x y L x y L x y ...
      std::stringstream ss(d_str);
      char cmd;
      double x, y;

      while (ss >> cmd) {
        if (cmd == 'M' || cmd == 'L') {
          if (ss >> x >> y) {
            points.push_back(QPointF(x, y));
          }
        }
      }
    }
  }

  auto obj = std::make_unique<Freehand>();
  obj->set_points(points);
  obj->SetStrokeColor(stroke_color);
  obj->SetStrokeWidth(stroke_width);

  // Recalculate bounding box
  if (!points.empty()) {
    double min_x = points[0].x(), max_x = points[0].x();
    double min_y = points[0].y(), max_y = points[0].y();

    for (const auto& p : points) {
      min_x = std::min(min_x, p.x());
      max_x = std::max(max_x, p.x());
      min_y = std::min(min_y, p.y());
      max_y = std::max(max_y, p.y());
    }

    obj->bbox_x_ = min_x;
    obj->bbox_y_ = min_y;
    obj->bbox_width_ = max_x - min_x;
    obj->bbox_height_ = max_y - min_y;
  }
  obj->SetStrokeWidth(stroke_width);

  return obj;
}
