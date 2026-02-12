#include <QColor>
#include <QPainterPath>
#include <QPen>
#include <sstream>

#include "../../headers/freehand.h"

// Exports to SVG
std::string Freehand::ToSvg() const {
  if (points_.size() < 2) return "";

  // Start path
  std::string d = "M " + std::to_string(points_[0].x()) + " " +
                  std::to_string(points_[0].y());
  // Line to subsequent points
  for (std::size_t i = 1; i < points_.size(); ++i) {
    d += " L " + std::to_string(points_[i].x()) + " " +
         std::to_string(points_[i].y());
  }

  // Match drawing style: no fill, round caps/joins
  return "<path\n\td=\"" + d + "\"\n\tfill=\"none\"\n\tstroke=\"" +
         stroke_color_ + "\"\n\tstroke-width=\"" +
         std::to_string(stroke_width_) +
         "\"\n\tstroke-linecap=\"round\"\n\tstroke-linejoin=\"round\" />\n";
}

// Helper for parsing SVG attributes
std::string get_attr_freehand(const std::string& svg, const std::string& attr) {
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
std::unique_ptr<GraphicsObject> Freehand::FromSvg(const std::string& svg) {
  int stroke_width = 0;
  std::string stroke_color = "black";
  std::vector<QPointF> points;

  std::string val;
  if (!(val = get_attr_freehand(svg, "stroke-width")).empty())
    stroke_width = std::stoi(val);
  if (!(val = get_attr_freehand(svg, "stroke")).empty()) stroke_color = val;

  // Parse path data - find d="..." and extract everything between quotes
  std::size_t d_pos = svg.find("d=\"");
  if (d_pos != std::string::npos) {
    std::size_t d_start = d_pos + 3;
    std::size_t d_end = svg.find("\"", d_start);
    if (d_end != std::string::npos) {
      std::string d_str = svg.substr(d_start, d_end - d_start);
      std::stringstream ss(d_str);
      char cmd;
      double x, y;

      while (ss >> cmd) {
        if (cmd == 'M' || cmd == 'L' || cmd == 'm' || cmd == 'l') {
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
    obj->last_x_ = obj->bbox_x_ + obj->bbox_width_;
    obj->last_y_ = obj->bbox_y_ + obj->bbox_height_;
    obj->handle_start_x_ = obj->bbox_x_;
    obj->handle_start_y_ = obj->bbox_y_;
    obj->handle_end_x_ = obj->last_x_;
    obj->handle_end_y_ = obj->last_y_;
  }
  obj->SetStrokeWidth(stroke_width);

  return obj;
}
