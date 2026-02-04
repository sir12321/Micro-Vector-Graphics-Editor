#ifndef SRC_MODEL_GRAPHICS_OBJECT_H_
#define SRC_MODEL_GRAPHICS_OBJECT_H_

#include <QPainter>
#include <string>

// Abstract base class for all graphics objects.
class GraphicsObject {
 protected:
  // styling attributes
  std::string stroke_color_;
  std::string fill_color_;
  int stroke_width_;
  std::string id_;

  // bounding box attributes
  double bbox_x_;
  double bbox_y_;
  mutable double bbox_width_;
  mutable double bbox_height_;

 public:
  virtual ~GraphicsObject() = default;
  virtual std::unique_ptr<GraphicsObject> Clone() const = 0;

  virtual std::string ToSvg() const = 0;
  virtual std::unique_ptr<GraphicsObject> FromSvg(const std::string& svg) = 0;

  // Bounding box getters (used by GUI later)
  double BboxX() const;
  double BboxY() const;
  double BboxWidth() const;
  double BboxHeight() const;

  virtual std::pair<double, double> GetStart() const = 0;
  virtual std::pair<double, double> GetEnd() const = 0;

  virtual void Draw(QPainter& painter) const = 0;
  virtual void Move(double dx, double dy) = 0;
  virtual void SetGeometry(double x, double y, double w, double h,
                           double rounded_rect_radius, double end_x,
                           double end_y) = 0;
  virtual void MoveStart(double x, double y) = 0;

  virtual void MoveEnd(double x, double y) = 0;

  // Sets the stroke color.
  void SetStrokeColor(const std::string& color);
  // Sets the fill color.
  void SetFillColor(const std::string& color);
  // Sets the stroke width.
  void SetStrokeWidth(int width);

  std::string GetStrokeColor() const;
  std::string GetFillColor() const;
  int GetStrokeWidth() const;

  // Returns the object ID.
  std::string GetId() const;
};

#endif  // SRC_MODEL_GRAPHICS_OBJECT_H_
