#include "../../headers/canvas.h"

void Canvas::keyPressEvent(QKeyEvent* event) {
  // Zoom shortcuts: Ctrl + '+' / '=' in, Ctrl + '-' out, Ctrl + 0 reset view
  if (event->modifiers() & Qt::ControlModifier) {
    QPointF center(width() / 2.0, height() / 2.0);
    if (event->key() == Qt::Key_Plus || event->key() == Qt::Key_Equal) {
      ZoomAt(center, 1.25);
      return;
    }
    if (event->key() == Qt::Key_Minus) {
      ZoomAt(center, 0.8);
      return;
    }
    if (event->key() == Qt::Key_0) {
      ResetView();
      return;
    }
  }

  // Global shortcuts
  if (event->key() == Qt::Key_Delete) {
    // Don't delete while actively dragging or editing text, and only record
    // undo (which clears redo) when something is actually selected
    if (selected_object_ && !dragging_object_ && !is_typing_text_) {
      PushUndoState();
      DeleteSelectedObject();
      update();
    }
    return;
  }

  // Text editing mode only
  if (!is_typing_text_ || !editing_text_) {
    QWidget::keyPressEvent(event);
    return;
  }

  // Finish text editing
  if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
    FinishTextEditing();
    return;
  }

  // Backspace (only a change if there is something to delete)
  if (event->key() == Qt::Key_Backspace) {
    if (!editing_text_->IsEmpty()) {
      RecordTextEditUndo();
      editing_text_->Backspace();
      update();
    }
    return;
  }

  // Regular character input: keep printable characters only, so keys like
  // Esc, Tab or Ctrl+letter don't insert invisible control characters.
  // Checked per code point (toUcs4) so emoji etc. made of 2 QChars survive.
  QString text;
  for (uint code : event->text().toUcs4()) {
    if (QChar::isPrint(code)) text += QString::fromUcs4(&code, 1);
  }
  if (!text.isEmpty()) {
    RecordTextEditUndo();
    // Store as UTF-8 bytes so any character (not just Latin-1) is kept
    for (char c : text.toStdString()) editing_text_->AppendChar(c);
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
  obj->Move(20, 20);
  diagram_.AddObject(std::move(obj));
  update();
}

// Ends any text edit in progress (Enter key, tool change). Does nothing if no
// text is being edited.
void Canvas::FinishTextEditing() {
  if (!is_typing_text_ || !editing_text_) return;
  is_typing_text_ = false;
  editing_text_->SetEditing(false);
  editing_text_ = nullptr;
  active_tool_text_ = false;
  text_undo_state_.clear();  // Editing ended; unchanged edits leave no undo
  RemoveEmptyTexts();
  update();
}

// Removes empty text objects, except the one currently being edited
void Canvas::RemoveEmptyTexts() {
  bool removed = false;
  for (std::size_t i = diagram_.size(); i-- > 0;) {
    auto* text = dynamic_cast<TextObject*>(diagram_.objects()[i].get());
    if (!text || text == editing_text_ || !text->IsEmpty()) continue;
    if (selected_object_ == text) selected_object_ = nullptr;
    if (dragging_object_ == text) dragging_object_ = nullptr;
    diagram_.RemoveObject(i);
    removed = true;
  }
  // Drop the undo entry that now matches the current state (no-op undo)
  if (removed && !undo_stack_.empty() &&
      undo_stack_.back() == diagram_.ToSvg()) {
    undo_stack_.pop_back();
  }
}
