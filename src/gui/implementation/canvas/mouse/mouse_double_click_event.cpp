#include "../../../headers/canvas.h"

// Handles double click: in select mode, double-clicking a text object starts
// editing it. Qt delivers the second click of a double-click here instead of
// to mousePressEvent, so every other double-click is treated as a normal press
// (otherwise quick second clicks with any tool would be lost).
void Canvas::mouseDoubleClickEvent(QMouseEvent* event) {
  if (event->button() == Qt::LeftButton && active_tool_ == Tool::None &&
      !is_typing_text_) {
    // Mouse position in world (diagram) coordinates
    const QPointF pos = ToWorld(event->localPos());
    // Top-most object under the cursor; edit it only if it is text
    auto* text_obj = dynamic_cast<TextObject*>(GetObjectAt(pos));
    if (text_obj) {
      // Remember the state before editing; it becomes an undo step only when
      // the text actually changes (so an edit that changes nothing keeps redo)
      text_undo_state_ = diagram_.ToSvg();

      // Enter text editing mode
      editing_text_ = text_obj;
      is_typing_text_ = true;
      text_obj->SetEditing(true);
      selected_object_ = nullptr;
      dragging_object_ = nullptr;

      if (edit_font_) {
        editing_text_->SetFontSize(active_font_size_);
        active_tool_text_ = true;
        // A different font size is itself a change worth undoing
        if (diagram_.ToSvg() != text_undo_state_) RecordTextEditUndo();
      }

      setFocus();
      update();
      return;
    }
  }

  // Not a text edit: handle it like an ordinary click (select, drag, draw,
  // fill, pan, ...)
  mousePressEvent(event);
}
