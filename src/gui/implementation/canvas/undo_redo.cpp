#include "../../headers/canvas.h"

// Clear undo and redo history
void Canvas::UndoRedoReset() {
  undo_stack_.clear();
  redo_stack_.clear();
}

// Save current state to undo history
void Canvas::PushUndoState() {
  std::string svg = diagram_.ToSvg();
  if (!undo_stack_.empty() && undo_stack_.back() == svg) {
    return;  // Avoid pushing duplicate states
  }
  undo_stack_.push_back(svg);
  redo_stack_.clear();

  constexpr int MAX_UNDO = 50;
  if (undo_stack_.size() > MAX_UNDO) {
    undo_stack_.erase(undo_stack_.begin());
  }
}

// Revert to the previous saved state
void Canvas::Undo() {
  if (undo_stack_.empty()) return;
  redo_stack_.push_back(diagram_.ToSvg());
  diagram_.Clear();
  diagram_.FromSvg(undo_stack_.back());
  undo_stack_.pop_back();

  selected_object_ = nullptr;
  update();
  updateCursor();
}

// Restore a previously undone state
void Canvas::Redo() {
  if (redo_stack_.empty()) return;
  undo_stack_.push_back(diagram_.ToSvg());
  diagram_.Clear();
  diagram_.FromSvg(redo_stack_.back());
  redo_stack_.pop_back();

  selected_object_ = nullptr;
  update();
  updateCursor();
}
