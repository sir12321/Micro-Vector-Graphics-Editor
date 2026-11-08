#include <QWheelEvent>
#include <algorithm>
#include <cmath>

#include "../../headers/canvas.h"

// Infinite canvas view
// Objects are stored in "world" coordinates. The widget shows them through a
// view transform: screen = world * zoom_ + pan_

namespace {
constexpr double kMinZoom = 0.05;  // 5%
constexpr double kMaxZoom = 40.0;  // 4000%
}  // namespace

// Converts a widget (screen) position into diagram (world) coordinates
QPointF Canvas::ToWorld(const QPointF& screen) const {
  return (screen - pan_) / zoom_;
}

// Zooms by `factor`, keeping the world point under `screen_pos` fixed on screen
void Canvas::ZoomAt(const QPointF& screen_pos, double factor) {
  QPointF world = ToWorld(screen_pos);
  zoom_ = std::clamp(zoom_ * factor, kMinZoom, kMaxZoom);
  pan_ = screen_pos - world * zoom_;
  update();
  updateCursor();
}

// Back to 100% zoom with the world origin at the top-left corner
void Canvas::ResetView() {
  zoom_ = 1.0;
  pan_ = QPointF(0, 0);
  update();
  updateCursor();
}

// Makes the whole drawing visible (used after opening a file). Keeps the
// default view if everything already fits; otherwise centres the drawing and
// zooms out (never in) until it fits.
void Canvas::FitToContent() {
  ResetView();
  QRectF r = diagram_.BoundingRect();
  if (r.isNull() || width() <= 0 || height() <= 0) return;  // Nothing to fit
  if (rect().contains(r.toAlignedRect())) return;  // Already fully visible

  const double margin = 20;  // Screen pixels around the drawing
  double fit = 1.0;
  if (r.width() > 0) fit = std::min(fit, (width() - 2 * margin) / r.width());
  if (r.height() > 0) fit = std::min(fit, (height() - 2 * margin) / r.height());
  zoom_ = std::clamp(fit, kMinZoom, kMaxZoom);
  pan_ = QPointF(width() / 2.0, height() / 2.0) - r.center() * zoom_;
  update();
  updateCursor();
}

// Mouse wheel / touchpad: Ctrl + scroll zooms at the cursor, scroll pans
void Canvas::wheelEvent(QWheelEvent* event) {
  if (event->modifiers() & Qt::ControlModifier) {
    // One wheel notch (120 units) zooms by 15%
    double steps = event->angleDelta().y() / 120.0;
    ZoomAt(event->position(), std::pow(1.15, steps));
  } else {
    // Touchpads report exact pixels; mouse wheels report angles (120/notch)
    QPointF delta = event->pixelDelta().isNull()
                        ? QPointF(event->angleDelta()) / 2.0
                        : QPointF(event->pixelDelta());
    // Shift + wheel pans sideways on mice without a horizontal wheel
    if ((event->modifiers() & Qt::ShiftModifier) && delta.x() == 0) {
      delta = QPointF(delta.y(), 0);
    }
    pan_ += delta;
    update();
    updateCursor();
  }
  event->accept();
}
