#include "../../headers/freehand.h"

// Constructs an empty Freehand object
Freehand::Freehand() {
  id_ = "freehand";
  bbox_x_ = 0;
  bbox_y_ = 0;
  last_x_ = 0;
  last_y_ = 0;
  handle_start_x_ = 0;
  handle_start_y_ = 0;
  handle_end_x_ = 0;
  handle_end_y_ = 0;
  bbox_width_ = 0;
  bbox_height_ = 0;
}

// Draws the path
void Freehand::Draw(QPainter& painter) const {
  if (points_.size() < 2) return;

  QPen pen(QColor(QString::fromStdString(stroke_color_)));
  pen.setWidth(stroke_width_);
  pen.setCapStyle(Qt::RoundCap);
  pen.setJoinStyle(Qt::RoundJoin);

  painter.setPen(pen);
  painter.setBrush(Qt::NoBrush);

  QPainterPath path;
  path.moveTo(points_[0]);
  for (std::size_t i = 1; i < points_.size(); ++i) {
    path.lineTo(points_[i]);
  }

  painter.drawPath(path);
}

void Freehand::MoveLast(double x, double y) {
  Freehand::AddPoint(QPointF(x, y));
}

std::pair<double, double> Freehand::GetLast() const {
  return {points_[points_.size() - 1].x(), points_[points_.size() - 1].y()};
}

std::pair<double, double> Freehand::GetStart() const {
  return {handle_start_x_, handle_start_y_};
}

std::pair<double, double> Freehand::GetEnd() const {
  return {handle_end_x_, handle_end_y_};
}