// Definition of the Freehand graphics object.

#ifndef SRC_MODEL_HEADERS_FREEHAND_H_
#define SRC_MODEL_HEADERS_FREEHAND_H_

#include <QPainter>
#include <string>

#include "graphics_object.h"

// Represents a freehand drawing path.
// Stores a list of points connected by line segments.
class Freehand : public GraphicsObject {
 private:
  std::vector<QPointF> points_;  // List of points in the path.

 public:
  // Constructs an empty Freehand object.
  explicit Freehand();

  // Sets the entire path of points.
  void set_points(const std::vector<QPointF>& points);

  // Appends a new point to the drawing path.
  void AddPoint(const QPointF& p);

  // Draws the path using QPainterPath.
  void Draw(QPainter& painter) const override;

  // Moves the entire path.
  void Move(double dx, double dy) override;

  // Unused for freehand (geometry is defined by point list).
  void SetGeometry(double x, double y, double w, double h,
                   double rounded_rect_radius, double end_x,
                   double end_y) override;

  // Exports path to SVG <path> d attribute.
  std::string ToSvg() const override;

  // Parses SVG path data.
  std::unique_ptr<GraphicsObject> FromSvg(const std::string& svg) override;

  // Creates a deep copy.
  std::unique_ptr<GraphicsObject> Clone() const override;

  void MoveStart(double x, double y) override;

  void MoveEnd(double x, double y) override;

  std::pair<double, double> GetStart() const override;

  std::pair<double, double> GetEnd() const override;
};

#endif  // SRC_MODEL_HEADERS_FREEHAND_H_
