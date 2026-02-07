#include <QMouseEvent>

#include "../../../../model/shape_factory/shape_factory.h"
#include "../../../headers/canvas.h"

// Handles double click to initiate text editing
void Canvas::mouseDoubleClickEvent(QMouseEvent* event) {
  if (event->button() != Qt::LeftButton) {
    return;
  }
  if (is_typing_text_) {
    return;
  }

  if (active_tool_ == Tool::None) {
    // Iterate top-to-bottom to find clicked text object
    for (int i = static_cast<int>(diagram_.size()) - 1; i >= 0; --i) {
      auto& obj = diagram_.objects()[i];

      if (!IsPointInsideBoundingBox(obj.get(), event->pos())) {
        continue;
      }

      auto* text_obj = dynamic_cast<TextObject*>(obj.get());
      if (!text_obj) {
        return;
      }

      // Enter text editing mode
      editing_text_ = text_obj;
      is_typing_text_ = true;

      text_obj->SetEditing(true);
      if (is_typing_text_) {
        selected_object_ = nullptr;
        dragging_object_ = nullptr;
      }
      if (editing_text_ && edit_font_) {
        editing_text_->SetFontSize(active_font_size_);
        active_tool_text_ = true;
      }

      setFocus();
      update();
      return;
    }
  }
}