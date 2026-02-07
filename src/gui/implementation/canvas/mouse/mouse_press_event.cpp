#include <QMouseEvent>

#include "../../../../model/shape_factory/shape_factory.h"
#include "../../../headers/canvas.h"

// Handles tools usage (creation, selection, filling) on mouse press
void Canvas::mousePressEvent(QMouseEvent* event) {
  if (event->button() != Qt::LeftButton) {
    return;
  }
  // Deselect if tool is active to avoid conflict
  if (selected_object_ != nullptr && active_tool_ != Tool::None) {
    selected_object_ = nullptr;
    dragging_object_ = nullptr;
    update();
  }

  // Commit text editing if active
  if (is_typing_text_ && active_tool_text_) {
    if (editing_text_) {
      is_typing_text_ = false;
      editing_text_->SetEditing(false);
      editing_text_ = nullptr;
      active_tool_text_ = false;
      update();
    } else {
      return;
    }
  }

  if (active_tool_ == Tool::None) {
    if (editing_text_ && selected_object_ != editing_text_) {
      is_typing_text_ = false;
      editing_text_->SetEditing(false);
      editing_text_ = nullptr;
      active_tool_text_ = false;
      update();
    }
  }

  // ---- SHAPE CREATION MODE ----
  // freehand tool
  if (active_tool_ == Tool::Freehand && event->button() == Qt::LeftButton) {
    PushUndoState();
    auto fh = std::make_unique<Freehand>();

    fh->SetStrokeColor(active_stroke_color_);
    fh->SetStrokeWidth(active_stroke_width_);

    fh->AddPoint(event->pos());

    current_freehand_ = fh.get();
    diagram_.AddObject(std::move(fh));

    is_drawing_freehand_ = true;
    update();
    return;
  }

  // Handle Text Tool
  if (active_tool_ == Tool::Text && event->button() == Qt::LeftButton) {
    PushUndoState();
    active_tool_text_ = true;

    // Commit existing text if any
    if (is_typing_text_ && editing_text_) {
      is_typing_text_ = false;
      editing_text_->SetEditing(false);
      editing_text_ = nullptr;
      update();
    }

    auto text =
        std::make_unique<TextObject>(event->pos().x(), event->pos().y(), "",
                                     active_font_size_, active_font_family_);

    editing_text_ = text.get();
    editing_text_->SetEditing(true);
    is_typing_text_ = true;
    editing_text_->SetStrokeColor(active_stroke_color_);
    editing_text_->SetFillColor(active_fill_color_);

    diagram_.AddObject(std::move(text));
    update();
    return;
  }

  // Standard shape creation (rect, circle, line etc)
  if (active_tool_ != Tool::None && active_tool_ != Tool::Fill &&
      active_tool_ != Tool::StrokeFill && event->button() == Qt::LeftButton) {
    PushUndoState();
    drag_start_ = event->pos();
    create_start_ = event->pos();
    QPoint end = event->pos();
    auto obj = CreateShape(active_tool_, drag_start_, end, active_fill_color_,
                           active_stroke_color_, active_stroke_width_,
                           GetRoundedRectRadius(), GetTextFontSize());
    preview_object_ = obj.get();
    if (obj) {
      diagram_.AddObject(std::move(obj));
    }
    is_creating_ = true;

    update();
    return;
  }

  // ---- FILL / STROKEFILL MODE ----
  if (active_tool_ == Tool::Fill) {
    if (editing_text_) {
      is_typing_text_ = false;
      editing_text_->SetEditing(false);
      editing_text_ = nullptr;
      update();
    }
    GraphicsObject* obj = nullptr;
    for (int i = static_cast<int>(diagram_.size()) - 1; i >= 0; --i) {
      auto& object = diagram_.objects()[i];
      if (IsPointInsideBoundingBox(object.get(), event->pos()) &&
          object->GetId() != "freehand" && object->GetId() != "line") {
        obj = object.get();
        break;
      }
    }
    if (!obj) return;
    PushUndoState();
    obj->SetFillColor(active_fill_color_);

    update();
    return;
  }

  if (active_tool_ == Tool::StrokeFill) {
    if (editing_text_) {
      is_typing_text_ = false;
      editing_text_->SetEditing(false);
      editing_text_ = nullptr;
      update();
    }
    GraphicsObject* obj = GetObjectAt(event->pos());
    if (!obj) return;
    PushUndoState();
    obj->SetStrokeColor(active_stroke_color_);
    obj->SetStrokeWidth(active_stroke_width_);
    update();
    return;
  }

  // ---- SELECTION MODE ----
  selected_object_ = nullptr;
  dragging_object_ = nullptr;
  PushUndoState();

  // Hit test for selection and resize handles
  selected_object_ = GetObjectAt(event->pos());
  dragging_object_ = GetObjectAt(event->pos());

  if (selected_object_) {
    if (IsPointInsideResizeStart(selected_object_, event->pos())) {
      is_resize1_ = true;
    } else if (IsPointInsideResizeEnd(selected_object_, event->pos())) {
      is_resize2_ = true;
    }
  }

  last_mouse_pos_ = event->pos();
  update();
  updateCursor();
}