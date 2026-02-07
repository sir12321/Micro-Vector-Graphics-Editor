#include <QCursor>
#include <QMouseEvent>
#include <QPixmap>

#include "../../headers/canvas.h"

void Canvas::updateCursor() {
  if (active_tool_ != Tool::None) {
    if (active_tool_ == Tool::Fill) {
      QPixmap pixmap(":/icons/icons/fill.png");
      setCursor(QCursor(
          pixmap.scaled(32, 32, Qt::KeepAspectRatio, Qt::SmoothTransformation),
          0, 32));
    } else if (active_tool_ == Tool::StrokeFill) {
      QPixmap pixmap(":/icons/icons/marker.png");
      setCursor(QCursor(
          pixmap.scaled(32, 32, Qt::KeepAspectRatio, Qt::SmoothTransformation),
          0, 32));
    } else if (active_tool_ == Tool::Text) {
      QPixmap pixmap(":/icons/icons/text.png");
      setCursor(QCursor(
          pixmap.scaled(32, 32, Qt::KeepAspectRatio, Qt::SmoothTransformation),
          0, 0));
    } else {
      setCursor(Qt::CrossCursor);
    }
    return;
  }

  QPoint pos = mapFromGlobal(QCursor::pos());

  if (dragging_object_) {
    setCursor(Qt::ClosedHandCursor);
    return;
  }

  if (is_resize1_ || is_resize2_) {
    setCursor(Qt::SizeFDiagCursor);
    return;
  }

  if (selected_object_) {
    if (IsPointInsideResizeStart(selected_object_, pos) ||
        IsPointInsideResizeEnd(selected_object_, pos)) {
      setCursor(Qt::SizeFDiagCursor);
      return;
    }
  }

  if (GetObjectAt(pos)) {
    setCursor(Qt::OpenHandCursor);
  } else {
    setCursor(Qt::ArrowCursor);
  }
}
