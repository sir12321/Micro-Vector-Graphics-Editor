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

// Adds a point to the path
void Freehand::AddPoint(const QPointF& p) {
  points_.push_back(p);

  if (points_.size() == 1) {
    bbox_x_ = p.x();
    bbox_y_ = p.y();
    bbox_width_ = 1;
    bbox_height_ = 1;
    last_x_ = bbox_x_ + bbox_width_;
    last_y_ = bbox_y_ + bbox_height_;
    handle_start_x_ = bbox_x_;
    handle_start_y_ = bbox_y_;
    handle_end_x_ = last_x_;
    handle_end_y_ = last_y_;
    return;
  }

  double min_x = bbox_x_;
  double min_y = bbox_y_;
  double max_x = bbox_x_ + bbox_width_;
  double max_y = bbox_y_ + bbox_height_;

  min_x = std::min(min_x, p.x());
  min_y = std::min(min_y, p.y());
  max_x = std::max(max_x, p.x());
  max_y = std::max(max_y, p.y());

  bbox_x_ = min_x;
  bbox_y_ = min_y;
  bbox_width_ = max_x - min_x;
  bbox_height_ = max_y - min_y;
  last_x_ = bbox_x_ + bbox_width_;
  last_y_ = bbox_y_ + bbox_height_;
  handle_start_x_ = bbox_x_;
  handle_start_y_ = bbox_y_;
  handle_end_x_ = last_x_;
  handle_end_y_ = last_y_;
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

void Freehand::Move(double dx, double dy) {
  for (auto& p : points_) {
    p += QPointF(dx, dy);
  }

  bbox_x_ += dx;
  bbox_y_ += dy;
  last_x_ += dx;
  last_y_ += dy;
  handle_start_x_ += dx;
  handle_start_y_ += dy;
  handle_end_x_ += dx;
  handle_end_y_ += dy;
}

void Freehand::set_points(const std::vector<QPointF>& points) {
  points_ = points;
}

void Freehand::SetGeometry(double x, double y, double w, double h,
                           double rounded_rect_radius, double end_x,
                           double end_y) {}

std::unique_ptr<GraphicsObject> Freehand::Clone() const {
  auto f = std::make_unique<Freehand>(*this);
  f->set_points(points_);
  f->SetStrokeColor(stroke_color_);
  f->SetStrokeWidth(stroke_width_);
  f->SetFillColor(fill_color_);
  return f;
}

void Freehand::MoveLast(double x, double y) {
  Freehand::AddPoint(QPointF(x, y));
}

std::pair<double, double> Freehand::GetLast() const {
  return {points_[points_.size() - 1].x(), points_[points_.size() - 1].y()};
}

void Freehand::MoveStart(double x, double y) {
  double old_start_x = handle_start_x_;
  double old_start_y = handle_start_y_;
  double old_end_x = handle_end_x_;
  double old_end_y = handle_end_y_;
  double denom_x = old_start_x - old_end_x;
  double denom_y = old_start_y - old_end_y;
  const double minsize = 1.0;
  if (std::abs(denom_x) < minsize || std::abs(denom_y) < minsize) {
    handle_start_x_ = x;
    handle_start_y_ = y;
    bbox_x_ = std::min(handle_start_x_, handle_end_x_);
    bbox_y_ = std::min(handle_start_y_, handle_end_y_);
    last_x_ = std::max(handle_start_x_, handle_end_x_);
    last_y_ = std::max(handle_start_y_, handle_end_y_);
    bbox_width_ = last_x_ - bbox_x_;
    bbox_height_ = last_y_ - bbox_y_;
    return;
  }

  double new_start_x = x;
  double new_start_y = y;
  double new_dx = new_start_x - old_end_x;
  double new_dy = new_start_y - old_end_y;
  if (std::abs(new_dx) < minsize) {
    double sign =
        (new_dx != 0) ? (new_dx > 0 ? 1.0 : -1.0) : (denom_x > 0 ? 1.0 : -1.0);
    new_start_x = old_end_x + sign * minsize;
    new_dx = new_start_x - old_end_x;
  }
  if (std::abs(new_dy) < minsize) {
    double sign =
        (new_dy != 0) ? (new_dy > 0 ? 1.0 : -1.0) : (denom_y > 0 ? 1.0 : -1.0);
    new_start_y = old_end_y + sign * minsize;
    new_dy = new_start_y - old_end_y;
  }

  double scale_x = new_dx / denom_x;
  double scale_y = new_dy / denom_y;
  std::vector<QPointF> points;
  points.reserve(points_.size());
  for (const auto& p : points_) {
    double new_px = old_end_x + (p.x() - old_end_x) * scale_x;
    double new_py = old_end_y + (p.y() - old_end_y) * scale_y;
    points.emplace_back(new_px, new_py);
  }
  set_points(points);
  handle_start_x_ = new_start_x;
  handle_start_y_ = new_start_y;
  bbox_x_ = std::min(handle_start_x_, handle_end_x_);
  bbox_y_ = std::min(handle_start_y_, handle_end_y_);
  last_x_ = std::max(handle_start_x_, handle_end_x_);
  last_y_ = std::max(handle_start_y_, handle_end_y_);
  bbox_width_ = last_x_ - bbox_x_;
  bbox_height_ = last_y_ - bbox_y_;
}

void Freehand::MoveEnd(double x, double y) {
  double old_start_x = handle_start_x_;
  double old_start_y = handle_start_y_;
  double old_end_x = handle_end_x_;
  double old_end_y = handle_end_y_;
  double denom_x = old_end_x - old_start_x;
  double denom_y = old_end_y - old_start_y;
  const double minsize = 1.0;
  if (std::abs(denom_x) < minsize || std::abs(denom_y) < minsize) {
    handle_end_x_ = x;
    handle_end_y_ = y;
    bbox_x_ = std::min(handle_start_x_, handle_end_x_);
    bbox_y_ = std::min(handle_start_y_, handle_end_y_);
    last_x_ = std::max(handle_start_x_, handle_end_x_);
    last_y_ = std::max(handle_start_y_, handle_end_y_);
    bbox_width_ = last_x_ - bbox_x_;
    bbox_height_ = last_y_ - bbox_y_;
    return;
  }

  double new_end_x = x;
  double new_end_y = y;
  double new_dx = new_end_x - old_start_x;
  double new_dy = new_end_y - old_start_y;
  if (std::abs(new_dx) < minsize) {
    double sign =
        (new_dx != 0) ? (new_dx > 0 ? 1.0 : -1.0) : (denom_x > 0 ? 1.0 : -1.0);
    new_end_x = old_start_x + sign * minsize;
    new_dx = new_end_x - old_start_x;
  }
  if (std::abs(new_dy) < minsize) {
    double sign =
        (new_dy != 0) ? (new_dy > 0 ? 1.0 : -1.0) : (denom_y > 0 ? 1.0 : -1.0);
    new_end_y = old_start_y + sign * minsize;
    new_dy = new_end_y - old_start_y;
  }

  double scale_x = new_dx / denom_x;
  double scale_y = new_dy / denom_y;
  std::vector<QPointF> points;
  points.reserve(points_.size());
  for (const auto& p : points_) {
    double new_px = old_start_x + (p.x() - old_start_x) * scale_x;
    double new_py = old_start_y + (p.y() - old_start_y) * scale_y;
    points.emplace_back(new_px, new_py);
  }
  set_points(points);
  handle_end_x_ = new_end_x;
  handle_end_y_ = new_end_y;
  bbox_x_ = std::min(handle_start_x_, handle_end_x_);
  bbox_y_ = std::min(handle_start_y_, handle_end_y_);
  last_x_ = std::max(handle_start_x_, handle_end_x_);
  last_y_ = std::max(handle_start_y_, handle_end_y_);
  bbox_width_ = last_x_ - bbox_x_;
  bbox_height_ = last_y_ - bbox_y_;
}

std::pair<double, double> Freehand::GetStart() const {
  return {handle_start_x_, handle_start_y_};
}

std::pair<double, double> Freehand::GetEnd() const {
  return {handle_end_x_, handle_end_y_};
}