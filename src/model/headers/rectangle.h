#ifndef SRC_MODEL_HEADERS_RECTANGLE_H_
#define SRC_MODEL_HEADERS_RECTANGLE_H_

#include "graphics_object.h"

// Represents a basic rectangle shape
class Rectangle : public GraphicsObject {
 private:
  double cx_;      // X coordinate of center
  double cy_;      // Y coordinate of center
  double width_;   // Width of the rectangle
  double height_;  // Height of the rectangle
  double endx_;
  double endy_;

 public:
  // Constructs a Rectangle
  Rectangle(double cx, double cy, double width, double height,
            int stroke_width);

  // Draws the rectangle
  void Draw(QPainter& painter) const override;

  // Updates geometry during creation
  void SetGeometry(double x, double y, double w, double h,
                   double rounded_rect_radius, double end_x,
                   double end_y) override;

  // Moves the rectangle
  void Move(double dx, double dy) override;

  // Exports to SVG
  std::string ToSvg() const override;

  // Imports from SVG
  std::unique_ptr<GraphicsObject> FromSvg(const std::string& svg) override;

  // Creates a deep copy
  std::unique_ptr<GraphicsObject> Clone() const override;

  void MoveStart(double x, double y) override;

  void MoveEnd(double x, double y) override;

  std::pair<double, double> GetStart() const override;

  std::pair<double, double> GetEnd() const override;
};

#endif
