// Definition of the Hexagon graphics object.

#ifndef SRC_MODEL_HEADERS_HEXAGON_H_
#define SRC_MODEL_HEADERS_HEXAGON_H_

#include "graphics_object.h"

// Represents a regular hexagon.
//
// Defined by its center and one vertex (which determines size and rotation).
class Hexagon : public GraphicsObject {
 private:
  double cx_;     // Center X coordinate.
  double cy_;     // Center Y coordinate.
  double x_, y_;  // One vertex of the hexagon.

 public:
  // Constructs a Hexagon.
  // @param cx Center X.
  // @param cy Center Y.
  // @param x Vertex X.
  // @param y Vertex Y.
  // @param stroke_width Outline width.
  Hexagon(double cx, double cy, double x, double y, int stroke_width);

  // Draws the hexagon.
  void Draw(QPainter& painter) const override;

  // Updates geometry based on user mouse interaction.
  void SetGeometry(double x, double y, double w, double h,
                   double rounded_rect_radius, double end_x,
                   double end_y) override;

  // Move the hexagon.
  void Move(double dx, double dy) override;

  // Exports to SVG <polygon>.
  std::string ToSvg() const override;

  // Parses SVG <polygon> to create Hexagon.
  std::unique_ptr<GraphicsObject> FromSvg(const std::string& svg) override;

  // Creates a deep copy.
  std::unique_ptr<GraphicsObject> Clone() const override;

  void MoveStart(double x, double y) override;

  void MoveEnd(double x, double y) override;

  std::pair<double, double> GetStart() const override;

  std::pair<double, double> GetEnd() const override;
};

#endif
