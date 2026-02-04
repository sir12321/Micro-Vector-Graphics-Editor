// Implementation of the Hexagon class.

#include "../../headers/hexagon.h"

#include <cmath>
#include <iostream>
#include <sstream>

using namespace std;

// Constructor calculates bounding box based on the circumcircle.
Hexagon::Hexagon(double cx, double cy, double x, double y, int stroke_width)
    : cx_(cx), cy_(cy), x_(x), y_(y) {
  id_ = "hexagon";
  double r = std::sqrt((x_ - cx_) * (x_ - cx_) + (y_ - cy_) * (y_ - cy_));
  SetStrokeWidth(stroke_width);
  bbox_x_ = cx_ - (r + stroke_width_);
  bbox_y_ = cy_ - (r + stroke_width_);
  bbox_width_ = 2 * (r + stroke_width_);
  bbox_height_ = 2 * (r + stroke_width_);
}

// Draws a regular hexagon by calculating 6 vertices.
void Hexagon::Draw(QPainter& painter) const {
  QPen pen(QColor(QString::fromStdString(stroke_color_)));
  pen.setWidth(stroke_width_);
  painter.setPen(pen);

  painter.setBrush(QColor(QString::fromStdString(fill_color_)));
  QPolygonF polygon;
  polygon.clear();
  double vx = x_ - cx_;
  double vy = y_ - cy_;
  for (int i = 0; i < 6; ++i) {
    double angle = i * M_PI / 3.0;
    // Rotate the generating vertex around the center
    double rx = vx * std::cos(angle) - vy * std::sin(angle);
    double ry = vx * std::sin(angle) + vy * std::cos(angle);
    polygon << QPointF(cx_ + rx, cy_ + ry);
  }

  painter.drawPolygon(polygon);
}

// Translates both the center and the defining vertex.
void Hexagon::Move(double dx, double dy) {
  x_ += dx;
  y_ += dy;
  cx_ += dx;
  cy_ += dy;
  bbox_x_ += dx;
  bbox_y_ += dy;
}

// Updates the defining vertex during creation.
void Hexagon::SetGeometry(double x, double y, double w, double h,
                          double rounded_rect_radius, double end_x,
                          double end_y) {
  x_ = end_x;
  y_ = end_y;
  double r = std::sqrt((x_ - cx_) * (x_ - cx_) + (y_ - cy_) * (y_ - cy_));

  bbox_x_ = cx_ - (r + stroke_width_);
  bbox_y_ = cy_ - (r + stroke_width_);
  bbox_width_ = 2 * (r + stroke_width_);
  bbox_height_ = 2 * (r + stroke_width_);
}

std::unique_ptr<GraphicsObject> Hexagon::Clone() const {
  auto h = std::make_unique<Hexagon>(cx_, cy_, x_, y_, stroke_width_);
  h->SetStrokeColor(stroke_color_);
  h->SetStrokeWidth(stroke_width_);
  h->SetFillColor(fill_color_);
  return h;
}

void Hexagon::MoveStart(double x, double y) {
  cx_ = x;
  cy_ = y;
  double r = std::sqrt((x_ - cx_) * (x_ - cx_) + (y_ - cy_) * (y_ - cy_));

  bbox_x_ = cx_ - (r + stroke_width_);
  bbox_y_ = cy_ - (r + stroke_width_);
  bbox_width_ = 2 * (r + stroke_width_);
  bbox_height_ = 2 * (r + stroke_width_);
}

void Hexagon::MoveEnd(double x, double y) {
  x_ = x;
  y_ = y;
  double r = std::sqrt((x_ - cx_) * (x_ - cx_) + (y_ - cy_) * (y_ - cy_));

  bbox_x_ = cx_ - (r + stroke_width_);
  bbox_y_ = cy_ - (r + stroke_width_);
  bbox_width_ = 2 * (r + stroke_width_);
  bbox_height_ = 2 * (r + stroke_width_);
}

std::pair<double, double> Hexagon::GetStart() const { return {cx_, cy_}; }

std::pair<double, double> Hexagon::GetEnd() const { return {x_, y_}; }