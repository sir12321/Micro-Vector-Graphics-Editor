#include "diagram.h"

// Adds a new graphics object to the diagram
void Diagram::AddObject(std::unique_ptr<GraphicsObject> object) {
  if (!object) return;  // Ignore failed parses / null shapes
  objects_.push_back(std::move(object));
}

// Removes the object at the specified index
void Diagram::RemoveObject(std::size_t index) {
  if (index < objects_.size()) {
    objects_.erase(objects_.begin() + index);
  }
}

// Clears all objects from the diagram
void Diagram::Clear() { objects_.clear(); }

// Vector that contains all the objects
const std::vector<std::unique_ptr<GraphicsObject>>& Diagram::objects() const {
  return objects_;
}
// Returns size of vector
std::size_t Diagram::size() const { return objects_.size(); }

// Union of all objects' bounding boxes, each grown by its stroke width.
// Objects that write nothing to the file (e.g. empty text) don't count.
QRectF Diagram::BoundingRect() const {
  double min_x = 0, min_y = 0, max_x = 0, max_y = 0;
  bool first = true;
  for (const auto& obj : objects_) {
    if (obj->ToSvg().empty()) continue;
    double sw = obj->GetStrokeWidth();
    double x0 = obj->BboxX() - sw, y0 = obj->BboxY() - sw;
    double x1 = obj->BboxX() + obj->BboxWidth() + sw;
    double y1 = obj->BboxY() + obj->BboxHeight() + sw;
    if (first || x0 < min_x) min_x = x0;
    if (first || y0 < min_y) min_y = y0;
    if (first || x1 > max_x) max_x = x1;
    if (first || y1 > max_y) max_y = y1;
    first = false;
  }
  if (first) return QRectF();  // Nothing drawn
  return QRectF(QPointF(min_x, min_y), QPointF(max_x, max_y));
}
