#include "../../../headers/canvas.h"

// Handles finishing operations (resizing, drawing, creation) on mouse release
void Canvas::mouseReleaseEvent(QMouseEvent* event) {
  // Finish panning
  if (is_panning_ && (event->button() == Qt::MiddleButton ||
                      event->button() == Qt::RightButton)) {
    is_panning_ = false;
    updateCursor();
    return;
  }

  // Reset resize
  if (is_resize1_ || is_resize2_ || is_resize_3_) {
    is_resize1_ = false;
    is_resize2_ = false;
    is_resize_3_ = false;
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
    // Record undo (and clear redo) only if a move/resize changed something
    if (!pending_undo_state_.empty() &&
        pending_undo_state_ != diagram_.ToSvg()) {
      PushUndoSnapshot(pending_undo_state_);
    }
    pending_undo_state_.clear();
    updateCursor();
    return;
  }

  // Finalize shape creation
  if (!is_creating_ || event->button() != Qt::LeftButton) {
    updateCursor();
    return;
  }
  if (is_creating_ && event->button() == Qt::LeftButton) {
    if (preview_object_) {
      // Start and end handles closer than 2 screen pixels means the mouse
      // was clicked without dragging: the shape would have zero size
      auto s = preview_object_->GetStart();
      auto e = preview_object_->GetEnd();
      double min_size = 2 / zoom_;
      bool too_small = std::abs(s.first - e.first) < min_size &&
                       std::abs(s.second - e.second) < min_size;
      if (too_small) {
        // Discard it; nothing changed, so undo/redo are left as they were
        for (std::size_t i = 0; i < diagram_.size(); ++i) {
          if (diagram_.objects()[i].get() == preview_object_) {
            diagram_.RemoveObject(i);
            break;
          }
        }
      } else if (!pending_undo_state_.empty()) {
        PushUndoSnapshot(pending_undo_state_);  // Undo removes the new shape
      }
    }
    pending_undo_state_.clear();
    preview_object_ = nullptr;
    is_creating_ = false;
    update();
    updateCursor();
    return;
  }

  update();
  updateCursor();
}