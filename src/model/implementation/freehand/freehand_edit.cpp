#include "../../headers/freehand.h"

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