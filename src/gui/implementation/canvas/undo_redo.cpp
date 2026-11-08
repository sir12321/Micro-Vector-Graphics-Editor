#include "../../headers/canvas.h"

// Clear undo and redo history
void Canvas::UndoRedoReset() {
  undo_stack_.clear();
  redo_stack_.clear();
}

// Forget every pointer into the diagram and any action in progress.
// Must be called whenever the diagram's objects are destroyed (undo, redo,
// open, new, close), otherwise these pointers would dangle.
void Canvas::ResetInteraction() {
  selected_object_ = nullptr;
  dragging_object_ = nullptr;
  preview_object_ = nullptr;
  current_freehand_ = nullptr;
  editing_text_ = nullptr;
  is_creating_ = false;
  is_typing_text_ = false;
  is_drawing_freehand_ = false;
  is_resize1_ = false;
  is_resize2_ = false;
  is_resize_3_ = false;
  active_tool_text_ = false;
  pending_undo_state_.clear();
  text_undo_state_.clear();
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

// Save an earlier state (taken before a change) to undo history
void Canvas::PushUndoSnapshot(const std::string& svg) {
  if (undo_stack_.empty() || undo_stack_.back() != svg) {
    undo_stack_.push_back(svg);
  }
  redo_stack_.clear();  // A real change happened, so redo is no longer valid

  constexpr int MAX_UNDO = 50;
  if (undo_stack_.size() > MAX_UNDO) {
    undo_stack_.erase(undo_stack_.begin());
  }
}

// Double-click text editing: record the pre-edit state only once, right
// before the first actual change, so an edit that changes nothing keeps redo
void Canvas::RecordTextEditUndo() {
  if (text_undo_state_.empty()) return;
  PushUndoSnapshot(text_undo_state_);
  text_undo_state_.clear();
}

// Revert to the previous saved state
void Canvas::Undo() {
  if (undo_stack_.empty()) return;
  redo_stack_.push_back(diagram_.ToSvg());
  diagram_.Clear();
  diagram_.FromSvg(undo_stack_.back());
  undo_stack_.pop_back();

  ResetInteraction();  // Old objects are gone; drop all pointers to them
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

  ResetInteraction();  // Old objects are gone; drop all pointers to them
  update();
  updateCursor();
}
