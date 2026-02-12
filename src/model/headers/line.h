#ifndef SRC_MODEL_HEADERS_LINE_H_
#define SRC_MODEL_HEADERS_LINE_H_

#include <algorithm>

#include "graphics_object.h"

// Represents a straight line segment
class Line : public GraphicsObject {
 private:
  double x1_, y1_;  // Start point coordinates
  double x2_, y2_;  // End point coordinates

 public:
  // Constructs a Line segment
  Line(double x1, double y1, double x2, double y2, int stroke_width);

  // Draws the line
  void Draw(QPainter& painter) const override;

  // Updates geometry during creation
  void SetGeometry(double x, double y, double w, double h,
                   double rounded_rect_radius, double end_x,
                   double end_y) override;

  // Moves the line
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
