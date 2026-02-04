// Implementation of the Line class.

#include "../../headers/line.h"

#include <algorithm>

using namespace std;

// Constructor for Line. Calculates bounding box around the segment.
Line::Line(double x1, double y1, double x2, double y2, int stroke_width)
    : x1_(x1), y1_(y1), x2_(x2), y2_(y2) {
  id_ = "line";
  SetStrokeWidth(stroke_width);
  // Bounding box logic uses min/max logic to encompass the line + stroke width.
  bbox_x_ = min(x1_, x2_) - stroke_width_;
  bbox_y_ = min(y1_, y2_) - stroke_width_;
  bbox_width_ = abs(x2_ - x1_) + stroke_width_ * 2;
  bbox_height_ = abs(y2_ - y1_) + stroke_width_ * 2;
}

// Draws the line.
void Line::Draw(QPainter& painter) const {
  QPen pen(QColor(QString::fromStdString(stroke_color_)));
  pen.setWidth(stroke_width_);
  painter.setPen(pen);

  painter.drawLine(x1_, y1_, x2_, y2_);
}

// Updates geometry. Used when dragging to set the endpoint (x2, y2).
void Line::SetGeometry(double x, double y, double w, double h,
                       double rounded_rect_radius, double end_x, double end_y) {
  x2_ = end_x;
  y2_ = end_y;

  bbox_x_ = min(x1_, x2_) - stroke_width_;
  bbox_y_ = min(y1_, y2_) - stroke_width_;
  bbox_width_ = abs(x2_ - x1_) + stroke_width_ * 2;
  bbox_height_ = abs(y2_ - y1_) + stroke_width_ * 2;
}

// Moves the line by adding delta (dx, dy) to both start and end points.
void Line::Move(double dx, double dy) {
  x1_ += dx;
  y1_ += dy;
  x2_ += dx;
  y2_ += dy;
  bbox_x_ += dx;
  bbox_y_ += dy;
}

std::unique_ptr<GraphicsObject> Line::Clone() const {
  auto l = std::make_unique<Line>(x1_, y1_, x2_, y2_, stroke_width_);
  l->SetStrokeColor(stroke_color_);
  l->SetStrokeWidth(stroke_width_);
  l->SetFillColor(fill_color_);
  return l;
}

void Line::MoveStart(double x, double y) {
  x1_ = x;
  y1_ = y;

  bbox_x_ = min(x1_, x2_) - stroke_width_;
  bbox_y_ = min(y1_, y2_) - stroke_width_;
  bbox_width_ = abs(x2_ - x1_) + stroke_width_ * 2;
  bbox_height_ = abs(y2_ - y1_) + stroke_width_ * 2;
}

void Line::MoveEnd(double x, double y) {
  x2_ = x;
  y2_ = y;

  bbox_x_ = min(x1_, x2_) - stroke_width_;
  bbox_y_ = min(y1_, y2_) - stroke_width_;
  bbox_width_ = abs(x2_ - x1_) + stroke_width_ * 2;
  bbox_height_ = abs(y2_ - y1_) + stroke_width_ * 2;
}

std::pair<double, double> Line::GetStart() const { return {x1_, y1_}; }

std::pair<double, double> Line::GetEnd() const { return {x2_, y2_}; }