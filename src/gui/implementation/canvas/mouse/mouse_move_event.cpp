#include "../../../headers/canvas.h"

// Handles mouse movement for resizing, creating, and moving objects
void Canvas::mouseMoveEvent(QMouseEvent* event) {
  // Panning: shift the view by the screen distance moved
  if (is_panning_) {
    pan_ += event->localPos() - pan_last_;
    pan_last_ = event->localPos();
    update();
    return;
  }
  // Mouse position in world (diagram) coordinates
  const QPointF pos = ToWorld(event->localPos());

  // Handle resizing via control points
  if (is_resize1_ && selected_object_) {
    selected_object_->MoveStart(pos.x(), pos.y());
    update();
    return;
  }
  if (is_resize2_ && selected_object_) {
    selected_object_->MoveEnd(pos.x(), pos.y());
    update();
    return;
  }
  if (is_resize_3_ && selected_object_) {
    selected_object_->MoveLast(pos.x(), pos.y());
    update();
    return;
  }

  // Handle freehand drawing path updates
  if (is_drawing_freehand_ && current_freehand_) {
    current_freehand_->AddPoint(pos);
    update();
    return;
  }

  // Update preview object geometry during creation
  if (is_creating_ && preview_object_) {
    QPointF end = pos;
    double x, y, w, h;

    if (active_tool_ == Tool::Rectangle ||
        active_tool_ == Tool::RoundedRectangle) {
      w = 2 * std::abs(end.x() - create_start_.x());
      h = 2 * std::abs(end.y() - create_start_.y());
      x = create_start_.x() - w / 2.0;
      y = create_start_.y() - h / 2.0;
    } else {
      x = std::min(create_start_.x(), end.x());
      y = std::min(create_start_.y(), end.y());
      w = std::abs(end.x() - create_start_.x());
      h = std::abs(end.y() - create_start_.y());
    }

    preview_object_->SetGeometry(x, y, w, h, GetRoundedRectRadius(), end.x(),
                                 end.y());
    update();
    return;
  }

  // Handle object translation/dragging
  if (dragging_object_) {
    bool object_exists = false;
    for (const auto& obj : diagram_.objects()) {
      if (obj.get() == dragging_object_) {
        object_exists = true;
        break;
      }
    }

    if (object_exists) {
      QPointF delta = pos - last_mouse_pos_;
      dragging_object_->Move(delta.x(), delta.y());
      last_mouse_pos_ = pos;
      update();
    } else {
      dragging_object_ = nullptr;
      selected_object_ = nullptr;
      return;
    }
  }

  updateCursor();
}