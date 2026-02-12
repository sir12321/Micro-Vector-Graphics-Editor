#ifndef SRC_MODEL_HEADERS_DIAGRAM_H_
#define SRC_MODEL_HEADERS_DIAGRAM_H_

#include <iostream>
#include <memory>
#include <vector>

#include "../model/headers/circle.h"
#include "../model/headers/freehand.h"
#include "../model/headers/graphics_object.h"
#include "../model/headers/hexagon.h"
#include "../model/headers/line.h"
#include "../model/headers/rectangle.h"
#include "../model/headers/rounded_rectangle.h"
#include "../model/headers/text.h"

// Represents the drawing canvas containing graphics objects
class Diagram {
 public:
  Diagram() = default;

  // Disable copy (important for unique_ptr)
  // Marking these as = delete tells the compiler to prevent anyone from
  // creating a copy of a Diagram object
  Diagram(const Diagram&) = delete;
  Diagram& operator=(const Diagram&) = delete;

  // Enable move
  // These allow a Diagram to be "moved" rather than copied
  Diagram(Diagram&&) = default;
  Diagram& operator=(Diagram&&) = default;

  // Object management
  void AddObject(std::unique_ptr<GraphicsObject> object);
  void RemoveObject(std::size_t index);
  void Clear();

  // Accessors
  const std::vector<std::unique_ptr<GraphicsObject>>& objects() const;

  std::size_t size() const;

  // SVG
  std::string ToSvg() const;
  void FromSvg(const std::string& svg);

 private:
  std::vector<std::unique_ptr<GraphicsObject>> objects_;
};

#endif  // SRC_MODEL_HEADERS_DIAGRAM_H_
