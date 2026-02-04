// Implementation of the GraphicsObject base class.
//
// This file contains the implementation of the setters and getters for the
// common attributes shared by all graphics objects, such as colors, stroke
// width, and bounding box coordinates.

#include "../headers/graphics_object.h"

using namespace std;

// Sets the stroke (outline) color of the object.
// The color is stored as a string (e.g., "#RRGGBB" or color name).
void GraphicsObject::SetStrokeColor(const std::string& color) {
  stroke_color_ = color;
}

// Sets the fill color of the object.
// The color is stored as a string (e.g., "#RRGGBB" or color name).
void GraphicsObject::SetFillColor(const std::string& color) {
  fill_color_ = color;
}

// Sets the width of the stroke (outline) in pixels.
void GraphicsObject::SetStrokeWidth(int width) { stroke_width_ = width; }

// --- Bounding Box Accessors ---
// These methods allow the GUI and other components to retrieve the
// geometric bounds of the object without knowing its specific shape.

double GraphicsObject::BboxX() const { return bbox_x_; }
double GraphicsObject::BboxY() const { return bbox_y_; }
double GraphicsObject::BboxWidth() const { return bbox_width_; }
double GraphicsObject::BboxHeight() const { return bbox_height_; }

// --- Style Accessors ---

string GraphicsObject::GetStrokeColor() const { return stroke_color_; }
string GraphicsObject::GetFillColor() const { return fill_color_; }
int GraphicsObject::GetStrokeWidth() const { return stroke_width_; }

// Returns the unique identifier for this object.
string GraphicsObject::GetId() const { return id_; }
