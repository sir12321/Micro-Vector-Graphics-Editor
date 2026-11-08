#include <algorithm>

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
      active_font_family_("DejaVu Sans"),
      is_creating_(false),
      is_typing_text_(false),
      is_drawing_freehand_(false),
      is_resize1_(false),
      is_resize2_(false),
      is_resize_3_(false),
      edit_font_(false),
      active_tool_text_(false),
      zoom_(1.0),
      pan_(0, 0),
      is_panning_(false) {
  setFocusPolicy(Qt::StrongFocus);
  setMouseTracking(true);
}

// Points are in world coordinates; tolerances are divided by zoom_ so they
// stay the same number of screen pixels at every zoom level

// Check if a point is within an object's bounding box (5px margin)
bool Canvas::IsPointInsideBoundingBox(GraphicsObject* obj,
                                      const QPointF& point) const {
  double pad = 5 / zoom_;

  // Lines: only a hit near the line itself. A diagonal line's bounding box is
  // mostly empty space and would block clicks on shapes underneath it.
  if (obj->GetId() == "line") {
    auto a = obj->GetStart();
    auto b = obj->GetEnd();
    double dx = b.first - a.first, dy = b.second - a.second;
    double len2 = dx * dx + dy * dy;
    // Closest point on the segment: a + t * (b - a), with t clamped to [0, 1]
    double t = 0;
    if (len2 > 0) {
      t = ((point.x() - a.first) * dx + (point.y() - a.second) * dy) / len2;
      t = std::clamp(t, 0.0, 1.0);
    }
    double ox = a.first + t * dx - point.x();
    double oy = a.second + t * dy - point.y();
    double tolerance = obj->GetStrokeWidth() / 2.0 + pad;
    return ox * ox + oy * oy <= tolerance * tolerance;
  }

  double x = obj->BboxX() - pad;
  double y = obj->BboxY() - pad;
  double w = obj->BboxWidth() + 2 * pad;
  double h = obj->BboxHeight() + 2 * pad;

  return point.x() >= x && point.x() <= x + w && point.y() >= y &&
         point.y() <= y + h;
}

// Check if a point is near the start handle for resizing (20px square)
bool Canvas::IsPointInsideResizeStart(GraphicsObject* obj,
                                      const QPointF& point) const {
  double half = 10 / zoom_;
  double x = obj->GetStart().first - half;
  double y = obj->GetStart().second - half;
  double w = 2 * half;
  double h = 2 * half;

  return point.x() >= x && point.x() <= x + w && point.y() >= y &&
         point.y() <= y + h;
}

// Check if a point is near the end handle for resizing (20px square)
bool Canvas::IsPointInsideResizeEnd(GraphicsObject* obj,
                                    const QPointF& point) const {
  double half = 10 / zoom_;
  double x = obj->GetEnd().first - half;
  double y = obj->GetEnd().second - half;
  double w = 2 * half;
  double h = 2 * half;

  return point.x() >= x && point.x() <= x + w && point.y() >= y &&
         point.y() <= y + h;
}

// Check if a point is near the last handle for resizing (20px square)
bool Canvas::IsPointInsideLast(GraphicsObject* obj,
                               const QPointF& point) const {
  if (obj->GetId() != "freehand") return false;
  double half = 10 / zoom_;
  double x = obj->GetLast().first - half;
  double y = obj->GetLast().second - half;
  double w = 2 * half;
  double h = 2 * half;

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

// Get the diagram as an SVG string (fit_view_box: for writing to a file)
std::string Canvas::ExportSvg(bool fit_view_box) const {
  return diagram_.ToSvg(fit_view_box);
}

// Replace diagram with objects parsed from SVG string
void Canvas::ImportSvg(const std::string& svg) {
  diagram_.FromSvg(svg);
  ResetInteraction();  // Old objects are gone; drop all pointers to them
  update();
}
