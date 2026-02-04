#include <QPainter>

#include "../../headers/canvas.h"

// Renders all diagram objects and selection indicators
void Canvas::paintEvent(QPaintEvent* /*event*/) {
  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);

  // ---- Draw all objects ----
  for (const auto& obj : diagram_.objects()) {
    if (obj != nullptr) {
      obj->Draw(painter);
    }

    // ---- Selection highlight (generic) ----
    if (obj.get() == selected_object_) {
      if (obj->GetId() != "text") {
        QPen pen(Qt::black);
        pen.setWidth(2);

        painter.setPen(pen);
        painter.setBrush(
            QColor(QString::fromStdString("#626262")).lighter(170));
        painter.drawEllipse(obj->GetStart().first - 5,
                            obj->GetStart().second - 5, 10, 10);
        painter.drawEllipse(obj->GetEnd().first - 5, obj->GetEnd().second - 5,
                            10, 10);
      }
      QPen pen2(Qt::red);
      pen2.setStyle(Qt::DashLine);
      pen2.setWidth(2);

      painter.setPen(pen2);
      painter.setBrush(Qt::NoBrush);

      painter.drawRect(obj->BboxX() - 3 - obj->GetStrokeWidth(),
                       obj->BboxY() - 3 - obj->GetStrokeWidth(),
                       obj->BboxWidth() + 6 + obj->GetStrokeWidth() * 2,
                       obj->BboxHeight() + 6 + obj->GetStrokeWidth() * 2);
    }
  }
}
