#include "../../headers/canvas.h"

void Canvas::paintEvent(QPaintEvent* /*event*/) {
  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);

  // Infinite canvas: map world coordinates to the screen (pan, then zoom)
  painter.translate(pan_);
  painter.scale(zoom_, zoom_);
  // Handle radius in world units, so handles stay 8px on screen at any zoom
  const double r = 8.0 / zoom_;

  // Draw all objects
  for (const auto& obj : diagram_.objects()) {
    if (obj != nullptr) {
      obj->Draw(painter);
    }

    // Selection highlight
    if (obj.get() == selected_object_) {
      // Resize handles: start + end, plus "last" for freehand (none for text)
      if (obj->GetId() != "text") {
        QPen pen(Qt::black);
        pen.setWidth(2);
        pen.setCosmetic(true);  // 2 screen pixels regardless of zoom

        painter.setPen(pen);
        painter.setBrush(
            QColor(QString::fromStdString("#626262")).lighter(170));
        painter.drawEllipse(
            QPointF(obj->GetStart().first, obj->GetStart().second), r, r);
        painter.drawEllipse(QPointF(obj->GetEnd().first, obj->GetEnd().second),
                            r, r);
        if (obj->GetId() == "freehand") {
          painter.drawEllipse(
              QPointF(obj->GetLast().first, obj->GetLast().second), r, r);
        }
      }
      QPen pen2(Qt::red);
      pen2.setStyle(Qt::DashLine);
      pen2.setWidth(2);
      pen2.setCosmetic(true);  // 2 screen pixels regardless of zoom

      painter.setPen(pen2);
      painter.setBrush(Qt::NoBrush);

      painter.drawRect(
          QRectF(obj->BboxX() - 3 - obj->GetStrokeWidth(),
                 obj->BboxY() - 3 - obj->GetStrokeWidth(),
                 obj->BboxWidth() + 6 + obj->GetStrokeWidth() * 2,
                 obj->BboxHeight() + 6 + obj->GetStrokeWidth() * 2));
    }
  }
}
