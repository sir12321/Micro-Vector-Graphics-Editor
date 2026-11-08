#include "../../../headers/canvas.h"

// Handles tools usage (creation, selection, filling) on mouse press
void Canvas::mousePressEvent(QMouseEvent* event) {
  // Middle or right drag pans the infinite canvas
  if (event->button() == Qt::MiddleButton ||
      event->button() == Qt::RightButton) {
    is_panning_ = true;
    pan_last_ = event->localPos();
    updateCursor();
    return;
  }
  if (event->button() != Qt::LeftButton || is_panning_) {
    return;
  }
  // Mouse position in world (diagram) coordinates
  const QPointF pos = ToWorld(event->localPos());
  // A click ends any double-click text edit; if nothing was typed, no undo
  text_undo_state_.clear();
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
  RemoveEmptyTexts();  // Discard any text that was committed with no content

  // SHAPE CREATION MODE
  // freehand tool
  if (active_tool_ == Tool::Freehand && event->button() == Qt::LeftButton) {
    PushUndoState();
    auto fh = std::make_unique<Freehand>();

    fh->SetStrokeColor(active_stroke_color_);
    fh->SetStrokeWidth(active_stroke_width_);

    fh->AddPoint(pos);

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
        std::make_unique<TextObject>(pos.x(), pos.y(), "",
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
    // Snapshot only; recorded on release if the new shape has a real size
    pending_undo_state_ = diagram_.ToSvg();
    drag_start_ = pos;
    create_start_ = pos;
    QPointF end = pos;
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

  // FILL / STROKEFILL MODE
  if (active_tool_ == Tool::Fill) {
    if (editing_text_) {
      is_typing_text_ = false;
      editing_text_->SetEditing(false);
      editing_text_ = nullptr;
      RemoveEmptyTexts();
      update();
    }
    GraphicsObject* obj = nullptr;
    for (int i = static_cast<int>(diagram_.size()) - 1; i >= 0; --i) {
      auto& object = diagram_.objects()[i];
      if (IsPointInsideBoundingBox(object.get(), pos) &&
          object->GetId() != "freehand" && object->GetId() != "line") {
        obj = object.get();
        break;
      }
    }
    if (!obj) return;
    // Record undo only if the colour actually changes (keeps redo otherwise)
    std::string before = diagram_.ToSvg();
    obj->SetFillColor(active_fill_color_);
    if (diagram_.ToSvg() != before) PushUndoSnapshot(before);

    update();
    return;
  }

  if (active_tool_ == Tool::StrokeFill) {
    if (editing_text_) {
      is_typing_text_ = false;
      editing_text_->SetEditing(false);
      editing_text_ = nullptr;
      RemoveEmptyTexts();
      update();
    }
    GraphicsObject* obj = GetObjectAt(pos);
    if (!obj) return;
    // Record undo only if colour/width actually change (keeps redo otherwise)
    std::string before = diagram_.ToSvg();
    obj->SetStrokeColor(active_stroke_color_);
    obj->SetStrokeWidth(active_stroke_width_);
    if (diagram_.ToSvg() != before) PushUndoSnapshot(before);
    update();
    return;
  }

  // SELECTION MODE
  selected_object_ = nullptr;
  dragging_object_ = nullptr;
  // Snapshot only; pushed on release if the diagram actually changed
  pending_undo_state_ = diagram_.ToSvg();

  // Hit test for selection and resize handles
  selected_object_ = GetObjectAt(pos);
  dragging_object_ = GetObjectAt(pos);

  if (selected_object_) {
    if (IsPointInsideResizeStart(selected_object_, pos)) {
      is_resize1_ = true;
    } else if (IsPointInsideResizeEnd(selected_object_, pos)) {
      is_resize2_ = true;
    } else if (IsPointInsideLast(selected_object_, pos)) {
      is_resize_3_ = true;
    }
  }

  last_mouse_pos_ = pos;
  update();
  updateCursor();
}