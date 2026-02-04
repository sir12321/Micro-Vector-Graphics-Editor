// Implementation of the Freehand class.

#include "../../headers/freehand.h"

#include <QColor>
#include <QPainterPath>
#include <QPen>
#include <sstream>

using namespace std;

// Constructs an empty Freehand object.
// Initializes the bounding box to zero and sets the ID to "freehand".
Freehand::Freehand() {
  id_ = "freehand";
  bbox_x_ = 0;
  bbox_y_ = 0;
  bbox_width_ = 0;
  bbox_height_ = 0;
}

// Adds a point to the freehand drawing path.
// Updates the bounding box dynamically to encompass the new point.
void Freehand::AddPoint(const QPointF& p) {
  points_.push_back(p);

  if (points_.size() == 1) {
    bbox_x_ = p.x();
    bbox_y_ = p.y();
    bbox_width_ = 1;
    bbox_height_ = 1;
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
}

// Draws the connected line segments using smooth joins.
// Uses QPainterPath to render the continuous line.
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
  for (size_t i = 1; i < points_.size(); ++i) {
    path.lineTo(points_[i]);
  }

  painter.drawPath(path);
}

// Translates all points in the path by a given offset.
// Updates the bounding box position accordingly.
void Freehand::Move(double dx, double dy) {
  for (auto& p : points_) {
    p += QPointF(dx, dy);
  }

  bbox_x_ += dx;
  bbox_y_ += dy;
}

void Freehand::set_points(const std::vector<QPointF>& points) {
  points_ = points;
}

// Sets geometric properties (Unused for Freehand).
// Freehand shape is defined by its points, not a bounding box geometry.
void Freehand::SetGeometry(double x, double y, double w, double h,
                           double rounded_rect_radius, double end_x,
                           double end_y) {}

// Creates a deep copy of the Freehand object.
// Clones all points and visual properties.
std::unique_ptr<GraphicsObject> Freehand::Clone() const {
  auto f = std::make_unique<Freehand>(*this);
  f->set_points(points_);
  f->SetStrokeColor(stroke_color_);
  f->SetStrokeWidth(stroke_width_);
  f->SetFillColor(fill_color_);
  return f;
}

void Freehand::MoveStart(double x, double y) {
  Freehand::AddPoint(QPointF(x, y));
}

void Freehand::MoveEnd(double x, double y) {
  Freehand::AddPoint(QPointF(x, y));
}

std::pair<double, double> Freehand::GetStart() const {
  return {points_[points_.size() - 1].x(), points_[points_.size() - 1].y()};
}

std::pair<double, double> Freehand::GetEnd() const {
  return {points_[points_.size() - 1].x(), points_[points_.size() - 1].y()};
}