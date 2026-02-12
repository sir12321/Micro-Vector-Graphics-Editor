#include "../headers/graphics_object.h"

// Sets the stroke color
void GraphicsObject::SetStrokeColor(const std::string& color) {
  stroke_color_ = color;
}

// Sets the fill color
void GraphicsObject::SetFillColor(const std::string& color) {
  fill_color_ = color;
}

// Sets the stroke width
void GraphicsObject::SetStrokeWidth(int width) { stroke_width_ = width; }

// Bounding Box Accessors
double GraphicsObject::BboxX() const { return bbox_x_; }
double GraphicsObject::BboxY() const { return bbox_y_; }
double GraphicsObject::BboxWidth() const { return bbox_width_; }
double GraphicsObject::BboxHeight() const { return bbox_height_; }

// Style Accessors
std::string GraphicsObject::GetStrokeColor() const { return stroke_color_; }
std::string GraphicsObject::GetFillColor() const { return fill_color_; }
int GraphicsObject::GetStrokeWidth() const { return stroke_width_; }

// Returns the object ID
std::string GraphicsObject::GetId() const { return id_; }
