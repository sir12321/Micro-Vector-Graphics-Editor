#ifndef SRC_MODEL_HEADERS_FREEHAND_H_
#define SRC_MODEL_HEADERS_FREEHAND_H_

#include <QColor>
#include <QPainter>
#include <QPainterPath>
#include <QPen>
#include <sstream>
#include <string>

#include "graphics_object.h"

// Represents a freehand drawing path
class Freehand : public GraphicsObject {
 private:
  std::vector<QPointF> points_;  // List of points in the path

 public:
  // Constructs an empty Freehand object
  explicit Freehand();

  // Sets the path points
  void set_points(const std::vector<QPointF>& points);

  // Appends a point to the path
  void AddPoint(const QPointF& p);

  // Draws the path
  void Draw(QPainter& painter) const override;

  // Moves the path
  void Move(double dx, double dy) override;

  // Updates geometry (unused for freehand)
  void SetGeometry(double x, double y, double w, double h,
                   double rounded_rect_radius, double end_x,
                   double end_y) override;

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

#endif  // SRC_MODEL_HEADERS_FREEHAND_H_
