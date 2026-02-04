#include <QKeyEvent>

#include "../../headers/canvas.h"

// Handles keyboard events for deletion and text entry
void Canvas::keyPressEvent(QKeyEvent* event) {
  // ---- Global shortcuts ----
  if (event->key() == Qt::Key_Delete) {
    // Don't delete while actively dragging or editing text
    if (!dragging_object_ && !is_typing_text_) {
      PushUndoState();
      DeleteSelectedObject();
      update();
    }
    return;
  }

  // ---- Text editing mode only ----
  if (!is_typing_text_ || !editing_text_) {
    QWidget::keyPressEvent(event);
    return;
  }

  // ---- Finish text editing ----
  if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
    is_typing_text_ = false;
    editing_text_->SetEditing(false);
    editing_text_ = nullptr;
    update();
    return;
  }

  // ---- Backspace ----
  if (event->key() == Qt::Key_Backspace) {
    editing_text_->Backspace();
    update();
    return;
  }

  // ---- Regular character input ----
  QString text = event->text();
  if (!text.isEmpty()) {
    editing_text_->AppendChar(text[0].toLatin1());
    update();
    return;
  }

  QWidget::keyPressEvent(event);
}

void Canvas::CopySelected() {
  if (!selected_object_) return;
  clipboard_ = selected_object_->Clone();
}

void Canvas::CutSelected() {
  if (!selected_object_) return;
  PushUndoState();
  clipboard_ = selected_object_->Clone();
  DeleteSelectedObject();
}

void Canvas::Paste() {
  if (!clipboard_) return;
  PushUndoState();
  auto obj = clipboard_->Clone();
  obj->Move(20, 20);  // offset so user sees it
  diagram_.AddObject(std::move(obj));
  update();
}
