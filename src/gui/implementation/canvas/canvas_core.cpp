#include "../../headers/canvas.h"

// Initialize canvas with default drawing settings
Canvas::Canvas(Diagram& diagram, QWidget* parent)
    : QWidget(parent),
      diagram_(diagram),
      selected_object_(nullptr),
      dragging_object_(nullptr),
      preview_object_(nullptr),
      current_freehand_(nullptr),
      editing_text_(nullptr),
      active_rr_radius_(0.15),
      active_font_size_(9),
      active_tool_(Tool::None),
      active_fill_color_("white"),
      active_stroke_color_("black"),
      active_stroke_width_(2),
      active_font_family_("Deja Vu Sans"),
      is_creating_(false),
      is_typing_text_(false),
      is_drawing_freehand_(false),
      is_resize1_(false),
      is_resize2_(false),
      edit_font_(false),
      active_tool_text_(false) {
  setFocusPolicy(Qt::StrongFocus);
  setMouseTracking(true);
}

// Check if a point is within an object's bounding box
bool Canvas::IsPointInsideBoundingBox(GraphicsObject* obj,
                                      const QPoint& point) const {
  double x = obj->BboxX() - 5;
  double y = obj->BboxY() - 5;
  double w = obj->BboxWidth() + 10;
  double h = obj->BboxHeight() + 10;

  return point.x() >= x && point.x() <= x + w && point.y() >= y &&
         point.y() <= y + h;
}

// Check if a point is near the start handle for resizing
bool Canvas::IsPointInsideResizeStart(GraphicsObject* obj,
                                      const QPoint& point) const {
  double x = obj->GetStart().first - 10;
  double y = obj->GetStart().second - 10;
  double w = 20;
  double h = 20;

  return point.x() >= x && point.x() <= x + w && point.y() >= y &&
         point.y() <= y + h;
}
// Check if a point is near the end handle for resizing

bool Canvas::IsPointInsideResizeEnd(GraphicsObject* obj,
                                    const QPoint& point) const {
  double x = obj->GetEnd().first - 10;
  double y = obj->GetEnd().second - 10;
  double w = 20;
  double h = 20;

  return point.x() >= x && point.x() <= x + w && point.y() >= y &&
         point.y() <= y + h;
}

// Remove the currently selected object from the diagram
void Canvas::DeleteSelectedObject() {
  if (!selected_object_) return;

  for (std::size_t i = 0; i < diagram_.size(); ++i) {
    if (diagram_.objects()[i].get() == selected_object_) {
      if (editing_text_ == selected_object_) {
        editing_text_ = nullptr;
        is_typing_text_ = false;
      }
      if (dragging_object_ == selected_object_) {
        dragging_object_ = nullptr;
      }

      diagram_.RemoveObject(i);
      selected_object_ = nullptr;
      update();
      updateCursor();
      return;
    }
  }
}

// Get the diagram as an SVG string
std::string Canvas::ExportSvg() const { return diagram_.ToSvg(); }

// Replace diagram with objects parsed from SVG string
void Canvas::ImportSvg(const std::string& svg) {
  diagram_.FromSvg(svg);
  update();
}
