#ifndef SRC_MODEL_HEADERS_HEXAGON_H_
#define SRC_MODEL_HEADERS_HEXAGON_H_

#include <cmath>
#include <iostream>
#include <sstream>

#include "graphics_object.h"

// Represents a regular hexagon
class Hexagon : public GraphicsObject {
 private:
  double cx_;     // Center X coordinate
  double cy_;     // Center Y coordinate
  double x_, y_;  // One vertex of the hexagon

 public:
  // Constructs a Hexagon
  Hexagon(double cx, double cy, double x, double y, int stroke_width);

  // Draws the hexagon
  void Draw(QPainter& painter) const override;

  // Updates geometry during creation
  void SetGeometry(double x, double y, double w, double h,
                   double rounded_rect_radius, double end_x,
                   double end_y) override;

  // Moves the hexagon
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
