// Implementation of the Circle class.

#include "../../headers/circle.h"

#include <cmath>

using namespace std;

// Check header for documentation.
Circle::Circle(double cx, double cy, double r, int stroke_width)
    : cx_(cx), cy_(cy), rx_(r), ry_(r), endx_(cx + r), endy_(cy + r) {
  id_ = "circle";
  SetStrokeWidth(stroke_width);
  // Calculate bounding box based on center, radius, and stroke width.
  bbox_x_ = cx_ - (rx_ + stroke_width_ * 2);
  bbox_y_ = cy_ - (ry_ + stroke_width_ * 2);
  bbox_width_ = 2 * (rx_ + stroke_width_ * 2);
  bbox_height_ = 2 * (ry_ + stroke_width_ * 2);
}

// Draws the ellipse using QPainter in Qt.
void Circle::Draw(QPainter& painter) const {
  QPen pen(QColor(QString::fromStdString(stroke_color_)));
  pen.setWidth(stroke_width_);
  painter.setPen(pen);

  painter.setBrush(QColor(QString::fromStdString(fill_color_)));

  painter.drawEllipse(QPointF(cx_, cy_), rx_, ry_);
}

// Translate the center point and update the bounding box.
void Circle::Move(double dx, double dy) {
  cx_ += dx;
  cy_ += dy;
  bbox_x_ += dx;
  bbox_y_ += dy;
  endx_ += dx;
  endy_ += dy;
}

// Define the circle by center (implicit from creation) and end point.
// Radius is distance between center and current mouse point.
void Circle::SetGeometry(double x, double y, double w, double h,
                         double rounded_rect_radius, double end_x,
                         double end_y) {
  rx_ = abs(end_x - cx_);
  ry_ = abs(end_y - cy_);
  bbox_x_ = cx_ - (rx_ + stroke_width_ * 2);
  bbox_y_ = cy_ - (ry_ + stroke_width_ * 2);
  bbox_width_ = 2 * (rx_ + stroke_width_ * 2);
  bbox_height_ = 2 * (ry_ + stroke_width_ * 2);
  endx_ = end_x;
  endy_ = end_y;
}

std::unique_ptr<GraphicsObject> Circle::Clone() const {
  auto c = std::make_unique<Circle>(cx_, cy_, rx_, stroke_width_);
  c->SetGeometry(0, 0, 0, 0, 0, endx_, endy_);
  c->SetStrokeColor(stroke_color_);
  c->SetStrokeWidth(stroke_width_);
  c->SetFillColor(fill_color_);
  return c;
}

void Circle::MoveStart(double x, double y) {
  cx_ = x;
  cy_ = y;
  rx_ = abs(endx_ - cx_);
  ry_ = abs(endy_ - cy_);
  bbox_x_ = cx_ - (rx_ + stroke_width_ * 2);
  bbox_y_ = cy_ - (ry_ + stroke_width_ * 2);
  bbox_width_ = 2 * (rx_ + stroke_width_ * 2);
  bbox_height_ = 2 * (ry_ + stroke_width_ * 2);
}

void Circle::MoveEnd(double x, double y) {
  endx_ = x;
  endy_ = y;
  rx_ = abs(endx_ - cx_);
  ry_ = abs(endy_ - cy_);
  bbox_x_ = cx_ - (rx_ + stroke_width_ * 2);
  bbox_y_ = cy_ - (ry_ + stroke_width_ * 2);
  bbox_width_ = 2 * (rx_ + stroke_width_ * 2);
  bbox_height_ = 2 * (ry_ + stroke_width_ * 2);
}

std::pair<double, double> Circle::GetStart() const { return {cx_, cy_}; }

std::pair<double, double> Circle::GetEnd() const { return {endx_, endy_}; }