#ifndef SRC_MODEL_HEADERS_CIRCLE_H_
#define SRC_MODEL_HEADERS_CIRCLE_H_

#include <cmath>

#include "graphics_object.h"

// Represents a circle shape defined by center and radius
class Circle : public GraphicsObject {
 private:
  double cx_;  ///< X-coordinate of the center
  double cy_;  ///< Y-coordinate of the center
  double rx_;  ///< X-radius for ellipse (same as r_ for circle)
  double ry_;  ///< Y-radius for ellipse (same as r_ for circle)
  double endx_;
  double endy_;

 public:
  // Constructs a circle
  Circle(double cx, double cy, double r, int stroke_width);

  // Draws the circle
  void Draw(QPainter& painter) const override;

  // Updates geometry during creation
  void SetGeometry(double x, double y, double w, double h,
                   double rounded_rect_radius, double end_x,
                   double end_y) override;

  // Moves the circle
  void Move(double dx, double dy) override;

  // Exports to SVG
  std::string ToSvg() const override;

  // Imports from SVG
  std::unique_ptr<GraphicsObject> FromSvg(const std::string& svg) override;

  // Creates a deep copy
  std::unique_ptr<GraphicsObject> Clone() const override;

  void MoveStart(double x, double y) override;

  void MoveEnd(double x, double y) override;

  void MoveLast(double x, double y) override;

  std::pair<double, double> GetStart() const override;

  std::pair<double, double> GetEnd() const override;

  std::pair<double, double> GetLast() const override;
};

#endif
