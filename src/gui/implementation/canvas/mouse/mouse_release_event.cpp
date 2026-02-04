#include <QMouseEvent>

#include "../../../../model/shape_factory/shape_factory.h"
#include "../../../headers/canvas.h"

void Canvas::mouseReleaseEvent(QMouseEvent* event) {
  if (is_resize1_ || is_resize2_) {
    is_resize1_ = false;
    is_resize2_ = false;
    update();
  }
  if (is_drawing_freehand_ && event->button() == Qt::LeftButton) {
    current_freehand_ = nullptr;
    is_drawing_freehand_ = false;
    update();
    return;
  }

  if (event->button() == Qt::LeftButton && active_tool_ == Tool::None) {
    dragging_object_ = nullptr;
    return;
  }

  if (!is_creating_ || event->button() != Qt::LeftButton) {
    return;
  }
  if (is_creating_ && event->button() == Qt::LeftButton) {
    preview_object_ = nullptr;
    is_creating_ = false;
    update();
    return;
  }

  update();
}