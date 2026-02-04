#ifndef SRC_MODEL_HEADERS_DIAGRAM_H_
#define SRC_MODEL_HEADERS_DIAGRAM_H_

#include <memory>
#include <vector>

#include "../model/headers/graphics_object.h"

// Represents the drawing canvas containing graphics objects
class Diagram {
 public:
  Diagram() = default;

  // Disable copy (important for unique_ptr)
  Diagram(const Diagram&) = delete;
  Diagram& operator=(const Diagram&) = delete;

  // Enable move
  Diagram(Diagram&&) = default;
  Diagram& operator=(Diagram&&) = default;

  // Object management
  void AddObject(std::unique_ptr<GraphicsObject> object);
  void RemoveObject(size_t index);
  void Clear();

  // Accessors
  const std::vector<std::unique_ptr<GraphicsObject>>& objects() const;

  size_t size() const;

  // Serialization
  std::string ToSvg() const;
  void FromSvg(const std::string& svg);

 private:
  std::vector<std::unique_ptr<GraphicsObject>> objects_;
};

#endif  // SRC_MODEL_HEADERS_DIAGRAM_H_
