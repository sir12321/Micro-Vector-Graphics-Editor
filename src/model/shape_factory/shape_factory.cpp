#include "shape_factory.h"

#include <algorithm>
#include <cmath>
#include <memory>
#include <string>

#include "../headers/circle.h"
#include "../headers/hexagon.h"
#include "../headers/line.h"
#include "../headers/rectangle.h"
#include "../headers/rounded_rectangle.h"
#include "../headers/text.h"

std::unique_ptr<GraphicsObject> CreateShape(
    Tool tool, const QPoint& start, const QPoint& end,
    const std::string& fill_color, const std::string& stroke_color,
    int stroke_width, double rounded_rect_radius, int canvas_font_size) {
  switch (tool) {
    case Tool::Rectangle: {
      double w = 2 * std::abs(start.x() - end.x());
      double h = 2 * std::abs(start.y() - end.y());
      double cx = start.x();
      double cy = start.y();

      auto rect = std::make_unique<Rectangle>(cx, cy, w, h, stroke_width);
      rect->SetFillColor(fill_color);
      rect->SetStrokeColor(stroke_color);
      rect->SetStrokeWidth(stroke_width);

      return rect;
    }

    case Tool::RoundedRectangle: {
      double w = 2 * std::abs(start.x() - end.x());
      double h = 2 * std::abs(start.y() - end.y());
      double cx = start.x();
      double cy = start.y();

      auto rrect = std::make_unique<RoundedRectangle>(
          cx, cy, w, h, std::min(w, h) * rounded_rect_radius, stroke_width);
      rrect->SetFillColor(fill_color);
      rrect->SetStrokeColor(stroke_color);
      rrect->SetStrokeWidth(stroke_width);

      return rrect;
    }

    case Tool::Circle: {
      double cx = (start.x() + end.x()) / 2.0;
      double cy = (start.y() + end.y()) / 2.0;
      double rx = std::abs(start.x() - end.x());
      double ry = std::abs(start.y() - end.y());
      double r = std::sqrt(rx * rx + ry * ry) / 2.0;

      auto circle = std::make_unique<Circle>(cx, cy, r, stroke_width);
      circle->SetFillColor(fill_color);
      circle->SetStrokeColor(stroke_color);
      circle->SetStrokeWidth(stroke_width);

      return circle;
    }

    case Tool::Hexagon: {
      double cx = (start.x());
      double cy = (start.y());
      QPointF d = end;
      auto hex = std::make_unique<Hexagon>(cx, cy, d.x(), d.y(), stroke_width);
      hex->SetFillColor(fill_color);
      hex->SetStrokeColor(stroke_color);
      hex->SetStrokeWidth(stroke_width);

      return hex;
    }

    case Tool::Line: {
      auto line = std::make_unique<Line>(start.x(), start.y(), end.x(), end.y(),
                                         stroke_width);
      line->SetStrokeColor(stroke_color);
      line->SetStrokeWidth(stroke_width);

      return line;
    }

    case Tool::Text: {
      auto text = std::make_unique<TextObject>(start.x(), start.y(), "Text",
                                               canvas_font_size);
      text->SetFillColor(fill_color);
      text->SetStrokeColor(stroke_color);
      text->SetStrokeWidth(stroke_width);

      return text;
    }

    default:
      return nullptr;
  }
}
