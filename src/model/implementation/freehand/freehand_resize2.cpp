#include "../../headers/freehand.h"
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