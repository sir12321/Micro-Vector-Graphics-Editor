#include "../../headers/rounded_rectangle.h"

// Constructor
RoundedRectangle::RoundedRectangle(double cx, double cy, double width,
                                   double height, double radius,
                                   int stroke_width)
    : cx_(cx),
      cy_(cy),
      width_(width),
      height_(height),
      endx_(cx + width / 2.0),
      endy_(cy + height / 2.0) {
  SetStrokeWidth(stroke_width);
  double min_dim = std::min(width_, height_);
  if (min_dim > 0) {
    ratio_ = radius / min_dim;
  } else {
    ratio_ = 0.15;
  }

  double max_radius = min_dim / 2.0;
  radius_ = std::clamp(radius, 0.0, max_radius);

  id_ = "rounded_rectangle";
  bbox_x_ = cx_ - width_ / 2.0 - stroke_width_;
  bbox_y_ = cy_ - height_ / 2.0 - stroke_width_;
  bbox_width_ = width_ + stroke_width_ * 2;
  bbox_height_ = height_ + stroke_width_ * 2;
}

// Draws the rounded rectangle
void RoundedRectangle::Draw(QPainter& painter) const {
  QPen pen(QColor(QString::fromStdString(stroke_color_)));
  pen.setWidth(stroke_width_);
  painter.setPen(pen);

  painter.setBrush(QColor(QString::fromStdString(fill_color_)));

  painter.drawRoundedRect(cx_ - width_ / 2.0, cy_ - height_ / 2.0, width_,
                          height_, radius_, radius_);
}

// Updates geometry
void RoundedRectangle::SetGeometry(double x, double y, double w, double h,
                                   double rounded_rect_radius, double end_x,
                                   double end_y) {
  cx_ = x + w / 2.0;
  cy_ = y + h / 2.0;
  width_ = w;
  height_ = h;
  endx_ = end_x;
  endy_ = end_y;

  ratio_ = rounded_rect_radius;
  radius_ = std::min(width_, height_) * ratio_;

  bbox_x_ = x - stroke_width_;
  bbox_y_ = y - stroke_width_;
  bbox_width_ = w + stroke_width_ * 2;
  bbox_height_ = h + stroke_width_ * 2;
}

// Moves the object
void RoundedRectangle::Move(double dx, double dy) {
  cx_ += dx;
  cy_ += dy;
  bbox_x_ += dx;
  bbox_y_ += dy;
  endx_ += dx;
  endy_ += dy;
}

std::unique_ptr<GraphicsObject> RoundedRectangle::Clone() const {
  auto rr = std::make_unique<RoundedRectangle>(cx_, cy_, width_, height_,
                                               radius_, stroke_width_);
  rr->SetStrokeColor(stroke_color_);
  rr->SetStrokeWidth(stroke_width_);
  rr->SetFillColor(fill_color_);
  return rr;
}

void RoundedRectangle::MoveStart(double x, double y) {
  cx_ = x;
  cy_ = y;
  width_ = 2 * std::abs(cx_ - endx_);
  height_ = 2 * std::abs(cy_ - endy_);
  bbox_x_ = cx_ - width_ / 2.0 - stroke_width_;
  bbox_y_ = cy_ - height_ / 2.0 - stroke_width_;
  bbox_width_ = width_ + stroke_width_ * 2;
  bbox_height_ = height_ + stroke_width_ * 2;
  radius_ = std::min(width_, height_) * ratio_;
  double max_radius = std::min(width_, height_) / 2.0;
  radius_ = std::clamp(radius_, 0.0, max_radius);
}

void RoundedRectangle::MoveEnd(double x, double y) {
  endx_ = x;
  endy_ = y;
  width_ = 2 * std::abs(cx_ - endx_);
  height_ = 2 * std::abs(cy_ - endy_);
  bbox_x_ = cx_ - width_ / 2.0 - stroke_width_;
  bbox_y_ = cy_ - height_ / 2.0 - stroke_width_;
  bbox_width_ = width_ + stroke_width_ * 2;
  bbox_height_ = height_ + stroke_width_ * 2;
  radius_ = std::min(width_, height_) * ratio_;
  double max_radius = std::min(width_, height_) / 2.0;
  radius_ = std::clamp(radius_, 0.0, max_radius);
}

void RoundedRectangle::MoveLast(double x, double y) {}

std::pair<double, double> RoundedRectangle::GetStart() const {
  return {cx_, cy_};
}

std::pair<double, double> RoundedRectangle::GetEnd() const {
  return {endx_, endy_};
}

std::pair<double, double> RoundedRectangle::GetLast() const {
  return {cx_, cy_};
}