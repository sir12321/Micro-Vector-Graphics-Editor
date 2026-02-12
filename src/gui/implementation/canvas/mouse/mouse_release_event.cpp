#include "../../../headers/canvas.h"

// Handles finishing operations (resizing, drawing, creation) on mouse release
void Canvas::mouseReleaseEvent(QMouseEvent* event) {
  // Reset resize
  if (is_resize1_ || is_resize2_) {
    is_resize1_ = false;
    is_resize2_ = false;
    update();
  }

  // Finish freehand drawing
  if (is_drawing_freehand_ && event->button() == Qt::LeftButton) {
    current_freehand_ = nullptr;
    is_drawing_freehand_ = false;
    update();
    updateCursor();
    return;
  }

  // End object dragging
  if (event->button() == Qt::LeftButton && active_tool_ == Tool::None) {
    dragging_object_ = nullptr;
    updateCursor();
    return;
  }

  // Finalize shape creation
  if (!is_creating_ || event->button() != Qt::LeftButton) {
    updateCursor();
    return;
  }
  if (is_creating_ && event->button() == Qt::LeftButton) {
    preview_object_ = nullptr;
    is_creating_ = false;
    update();
    updateCursor();
    return;
  }

  update();
  updateCursor();
}