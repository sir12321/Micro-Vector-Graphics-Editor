// Definition of the Circle graphics object.

#ifndef SRC_MODEL_HEADERS_CIRCLE_H_
#define SRC_MODEL_HEADERS_CIRCLE_H_

#include "graphics_object.h"

// Represents a circle shape.
//
// Defined by a center point (cx, cy) and a radius (r).
class Circle : public GraphicsObject {
 private:
  double cx_;  ///< X-coordinate of the center.
  double cy_;  ///< Y-coordinate of the center.
  double rx_;  ///< X-radius for ellipse (same as r_ for circle).
  double ry_;  ///< Y-radius for ellipse (same as r_ for circle).
  double endx_;
  double endy_;

 public:
  // Constructs a circle.
  // @param cx Center X.
  // @param cy Center Y.
  // @param r Radius.
  // @param stroke_width Width of the outline.
  Circle(double cx, double cy, double r, int stroke_width);

  // Draws the circle on the provided painter.
  void Draw(QPainter& painter) const override;

  // Updates the geometry during creation/editing.
  // Used when dragging the mouse to define radius.
  void SetGeometry(double x, double y, double w, double h,
                   double rounded_rect_radius, double end_x,
                   double end_y) override;

  // Moves the circle by a delta.
  void Move(double dx, double dy) override;

  // Converts to SVG format.
  std::string ToSvg() const override;

  // Creates a Circle object from an SVG string.
  std::unique_ptr<GraphicsObject> FromSvg(const std::string& svg) override;

  // Creates a deep copy of the circle.
  std::unique_ptr<GraphicsObject> Clone() const override;

  void MoveStart(double x, double y) override;

  void MoveEnd(double x, double y) override;

  std::pair<double, double> GetStart() const override;

  std::pair<double, double> GetEnd() const override;
};

#endif
