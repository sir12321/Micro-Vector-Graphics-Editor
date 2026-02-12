#include "../../headers/rectangle.h"

Rectangle::Rectangle(double cx, double cy, double width, double height,
                     int stroke_width)
    : cx_(cx),
      cy_(cy),
      width_(width),
      height_(height),
      endx_(cx + width / 2.0),
      endy_(cy + height / 2.0) {
  id_ = "rectangle";
  SetStrokeWidth(stroke_width);
  // Calculate bounding box
  bbox_x_ = cx_ - width_ / 2.0 - stroke_width_;
  bbox_y_ = cy_ - height_ / 2.0 - stroke_width_;
  bbox_width_ = width_ + stroke_width_ * 2;
  bbox_height_ = height_ + stroke_width_ * 2;
}

// Draws the rectangle
void Rectangle::Draw(QPainter& painter) const {
  QPen pen(QColor(QString::fromStdString(stroke_color_)));
  pen.setWidth(stroke_width_);
  painter.setPen(pen);

  painter.setBrush(QColor(QString::fromStdString(fill_color_)));

  painter.drawRect(cx_ - width_ / 2.0, cy_ - height_ / 2.0, width_, height_);
}

// Updates geometry
void Rectangle::SetGeometry(double x, double y, double w, double h,
                            double rounded_rect_radius, double end_x,
                            double end_y) {
  cx_ = x + w / 2.0;
  cy_ = y + h / 2.0;
  width_ = w;
  height_ = h;

  bbox_x_ = x - stroke_width_;
  bbox_y_ = y - stroke_width_;
  bbox_width_ = w + stroke_width_ * 2;
  bbox_height_ = h + stroke_width_ * 2;
  endx_ = end_x;
  endy_ = end_y;
}

// Moves the rectangle
void Rectangle::Move(double dx, double dy) {
  cx_ += dx;
  cy_ += dy;
  bbox_x_ += dx;
  bbox_y_ += dy;
  endx_ += dx;
  endy_ += dy;
}

std::unique_ptr<GraphicsObject> Rectangle::Clone() const {
  auto r =
      std::make_unique<Rectangle>(cx_, cy_, width_, height_, stroke_width_);
  r->SetStrokeColor(stroke_color_);
  r->SetStrokeWidth(stroke_width_);
  r->SetFillColor(fill_color_);
  return r;
}
void Rectangle::MoveStart(double x, double y) {
  cx_ = x;
  cy_ = y;
  width_ = 2 * std::abs(cx_ - endx_);
  height_ = 2 * std::abs(cy_ - endy_);
  bbox_x_ = cx_ - width_ / 2.0 - stroke_width_;
  bbox_y_ = cy_ - height_ / 2.0 - stroke_width_;
  bbox_width_ = width_ + stroke_width_ * 2;
  bbox_height_ = height_ + stroke_width_ * 2;
}

void Rectangle::MoveEnd(double x, double y) {
  endx_ = x;
  endy_ = y;
  width_ = 2 * std::abs(cx_ - endx_);
  height_ = 2 * std::abs(cy_ - endy_);
  bbox_x_ = cx_ - width_ / 2.0 - stroke_width_;
  bbox_y_ = cy_ - height_ / 2.0 - stroke_width_;
  bbox_width_ = width_ + stroke_width_ * 2;
  bbox_height_ = height_ + stroke_width_ * 2;
}

void Rectangle::MoveLast(double x, double y) {}

std::pair<double, double> Rectangle::GetStart() const { return {cx_, cy_}; }

std::pair<double, double> Rectangle::GetEnd() const { return {endx_, endy_}; }

std::pair<double, double> Rectangle::GetLast() const { return {cx_, cy_}; }