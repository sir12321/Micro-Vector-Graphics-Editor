// Definition of the RoundedRectangle graphics object.

#ifndef SRC_MODEL_HEADERS_ROUNDED_RECTANGLE_H_
#define SRC_MODEL_HEADERS_ROUNDED_RECTANGLE_H_

#include "graphics_object.h"

// Represents a rectangle with rounded corners.
class RoundedRectangle : public GraphicsObject {
 private:
  double cx_;      // X coordinate of center
  double cy_;      // Y coordinate of center
  double width_;   // Width of the rectangle
  double height_;  // Height of the rectangle
  double radius_;  // Corner radius.
  double ratio_;
  double endx_;
  double endy_;

 public:
  // Constructs a RoundedRectangle.
  // @param cx Center X.
  // @param cy Center Y.
  // @param width Width.
  // @param height Height.
  // @param radius Corner radius (default 10.0).
  // @param stroke_width Outline width (default 1).
  RoundedRectangle(double cx, double cy, double width, double height,
                   double radius = 10.0, int stroke_width = 1);

  void Draw(QPainter& painter) const override;
  void SetGeometry(double x, double y, double w, double h,
                   double rounded_rect_radius, double end_x,
                   double end_y) override;
  void Move(double dx, double dy) override;
  std::string ToSvg() const override;
  std::unique_ptr<GraphicsObject> FromSvg(const std::string& svg) override;
  std::unique_ptr<GraphicsObject> Clone() const override;

  void MoveStart(double x, double y) override;

  void MoveEnd(double x, double y) override;

  std::pair<double, double> GetStart() const override;

  std::pair<double, double> GetEnd() const override;
};

#endif  // SRC_MODEL_HEADERS_ROUNDED_RECTANGLE_H_
