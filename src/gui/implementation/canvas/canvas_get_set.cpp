#include "../../headers/canvas.h"

// Get and set active fill color
std::string Canvas::GetActiveFillColor() const { return active_fill_color_; }
void Canvas::SetActiveFillColor(const std::string& color) {
  active_fill_color_ = color;
}

// Get and set stroke width
int Canvas::GetActiveStrokeWidth() const { return active_stroke_width_; }
void Canvas::SetActiveStrokeWidth(int width) { active_stroke_width_ = width; }

// Get and set active stroke color
std::string Canvas::GetActiveStrokeColor() const {
  return active_stroke_color_;
}
void Canvas::SetActiveStrokeColor(const std::string& color) {
  active_stroke_color_ = color;
}

// Get and set font size for text objects
int Canvas::GetTextFontSize() const { return active_font_size_; }
void Canvas::SetTextFontSize(int size) { active_font_size_ = size; }

// Get and set corner radius for rounded rectangles
double Canvas::GetRoundedRectRadius() const { return active_rr_radius_; }
void Canvas::SetRoundedRectRadius(double radius) { active_rr_radius_ = radius; }

// Identify top-most object under a given point
GraphicsObject* Canvas::GetObjectAt(const QPoint& pos) {
  for (int i = static_cast<int>(diagram_.size()) - 1; i >= 0; --i) {
    auto& obj = diagram_.objects()[i];
    if (IsPointInsideBoundingBox(obj.get(), pos)) {
      return obj.get();
    }
  }
  return nullptr;
}

// Update font family based on user selection
void Canvas::SetActiveFontFamily(const QFont& font) {
  active_font_family_ = std::string(font.family().toUtf8().constData());
}

// Set drawing tool and update mouse cursor
void Canvas::SetActiveTool(Tool tool) {
  active_tool_ = tool;
  updateCursor();
}