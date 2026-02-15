#include "diagram.h"

// Adds a new graphics object to the diagram
void Diagram::AddObject(std::unique_ptr<GraphicsObject> object) {
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
