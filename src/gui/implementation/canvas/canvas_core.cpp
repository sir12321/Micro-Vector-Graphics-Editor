#include <QKeyEvent>
#include <QMouseEvent>

#include "../../headers/canvas.h"

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
      active_tool_text_(false) {
  setFocusPolicy(Qt::StrongFocus);
  setMouseTracking(true);
}

bool Canvas::IsPointInsideBoundingBox(GraphicsObject* obj,
                                      const QPoint& point) const {
  double x = obj->BboxX() - 5;
  double y = obj->BboxY() - 5;
  double w = obj->BboxWidth() + 10;
  double h = obj->BboxHeight() + 10;

  return point.x() >= x && point.x() <= x + w && point.y() >= y &&
         point.y() <= y + h;
}

bool Canvas::IsPointInsideResizeStart(GraphicsObject* obj,
                                      const QPoint& point) const {
  double x = obj->GetStart().first - 5;
  double y = obj->GetStart().second - 5;
  double w = 10;
  double h = 10;

  return point.x() >= x && point.x() <= x + w && point.y() >= y &&
         point.y() <= y + h;
}

bool Canvas::IsPointInsideResizeEnd(GraphicsObject* obj,
                                    const QPoint& point) const {
  double x = obj->GetEnd().first - 5;
  double y = obj->GetEnd().second - 5;
  double w = 10;
  double h = 10;

  return point.x() >= x && point.x() <= x + w && point.y() >= y &&
         point.y() <= y + h;
}

void Canvas::DeleteSelectedObject() {
  if (!selected_object_) return;

  for (size_t i = 0; i < diagram_.size(); ++i) {
    if (diagram_.objects()[i].get() == selected_object_) {
      // Nullify all pointers to the object being deleted
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
      return;
    }
  }
}

std::string Canvas::ExportSvg() const { return diagram_.ToSvg(); }

void Canvas::ImportSvg(const std::string& svg) {
  diagram_.FromSvg(svg);
  update();
}

void Canvas::UndoRedoReset() {
  undo_stack_.clear();
  redo_stack_.clear();
}

void Canvas::PushUndoState() {
  undo_stack_.push_back(diagram_.ToSvg());
  redo_stack_.clear();

  constexpr int MAX_UNDO = 30;
  if (undo_stack_.size() > MAX_UNDO) {
    undo_stack_.erase(undo_stack_.begin());
  }
}

void Canvas::Undo() {
  if (undo_stack_.empty()) return;
  redo_stack_.push_back(diagram_.ToSvg());
  diagram_.Clear();
  diagram_.FromSvg(undo_stack_.back());
  undo_stack_.pop_back();

  selected_object_ = nullptr;
  update();
}

void Canvas::Redo() {
  if (redo_stack_.empty()) return;
  undo_stack_.push_back(diagram_.ToSvg());
  diagram_.Clear();
  diagram_.FromSvg(redo_stack_.back());
  redo_stack_.pop_back();

  selected_object_ = nullptr;
  update();
}
