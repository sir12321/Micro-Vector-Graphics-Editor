// Definition of the Line graphics object.

#ifndef SRC_MODEL_HEADERS_LINE_H_
#define SRC_MODEL_HEADERS_LINE_H_

#include "graphics_object.h"

// Represents a straight line segment.
//
// Defined by a start point (x1, y1) and an end point (x2, y2).
class Line : public GraphicsObject {
 private:
  double x1_, y1_;  // Start point coordinates.
  double x2_, y2_;  // End point coordinates.

 public:
  // Constructs a Line segment.
  // @param x1 Start X.
  // @param y1 Start Y.
  // @param x2 End X.
  // @param y2 End Y.
  // @param stroke_width Line thickness.
  Line(double x1, double y1, double x2, double y2, int stroke_width);

  // Draws the line using QPainter.
  void Draw(QPainter& painter) const override;

  // Updates the line endpoint during creation.
  void SetGeometry(double x, double y, double w, double h,
                   double rounded_rect_radius, double end_x,
                   double end_y) override;

  // Translates the entire line.
  void Move(double dx, double dy) override;

  // Exports to SVG <line> tag.
  std::string ToSvg() const override;

  // Imports from SVG string.
  std::unique_ptr<GraphicsObject> FromSvg(const std::string& svg) override;

  // Creates a deep copy.
  std::unique_ptr<GraphicsObject> Clone() const override;

  void MoveStart(double x, double y) override;

  void MoveEnd(double x, double y) override;

  std::pair<double, double> GetStart() const override;

  std::pair<double, double> GetEnd() const override;
};

#endif
