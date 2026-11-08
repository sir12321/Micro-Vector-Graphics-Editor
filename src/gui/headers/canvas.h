#ifndef SRC_UI_HEADERS_CANVAS_H_
#define SRC_UI_HEADERS_CANVAS_H_

#include <QCursor>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QPixmap>  // for cursor images
#include <QPoint>
#include <QPointF>
#include <QWheelEvent>
#include <QWidget>  // for event handling and layout integration

#include "../../diagram/diagram.h"
#include "../../model/headers/freehand.h"
#include "../../model/headers/graphics_object.h"
#include "../../model/headers/text.h"
#include "../../model/shape_factory/shape_factory.h"
#include "tools.h"

class Canvas : public QWidget {
  Q_OBJECT
 public slots:
  // Undo/Redo operations
  void Undo();
  void Redo();

 public:
  bool edit_font_;
  explicit Canvas(Diagram& diagram, QWidget* parent = nullptr);
  // Tool and property setters/getters
  void SetActiveTool(Tool tool);
  void SetActiveFillColor(const std::string& color);
  void SetActiveStrokeColor(const std::string& color);
  void SetActiveStrokeWidth(int width);
  void SetActiveFontFamily(const QFont& font);
  void SetRoundedRectRadius(double radius);
  void SetTextFontSize(int size);
  int GetActiveStrokeWidth() const;
  double GetRoundedRectRadius() const;
  int GetTextFontSize() const;
  std::string GetActiveFillColor() const;
  std::string GetActiveStrokeColor() const;
  // Clipboard operations
  void CopySelected();
  void CutSelected();
  void Paste();
  // SVG
  std::string ExportSvg(bool fit_view_box = false) const;
  void ImportSvg(const std::string& svg);
  // Reset stacks
  void UndoRedoReset();
  // Drop selection/editing pointers; call after the diagram is cleared
  void ResetInteraction();
  // Infinite canvas: back to 100% zoom at the origin
  void ResetView();
  // Infinite canvas: show the whole drawing (zooming out if needed)
  void FitToContent();

 protected:
  // Drawing
  void paintEvent(QPaintEvent* event) override;
  void ApplyFillToSelected();
  void ApplyStrokeToSelected();
  // Mouse interaction
  void mousePressEvent(QMouseEvent* event) override;
  void mouseMoveEvent(QMouseEvent* event) override;
  void mouseReleaseEvent(QMouseEvent* event) override;
  void mouseDoubleClickEvent(QMouseEvent* event) override;
  void wheelEvent(QWheelEvent* event) override;  // Pan / zoom
  GraphicsObject* GetObjectAt(const QPointF& pos);
  // Keyboard interactions
  void keyPressEvent(QKeyEvent* event) override;
  void updateCursor();

 private:
  Diagram& diagram_;
  GraphicsObject* selected_object_;
  GraphicsObject* dragging_object_;
  GraphicsObject* preview_object_;
  std::unique_ptr<GraphicsObject> clipboard_;
  Freehand* current_freehand_;
  Tool active_tool_;
  std::string active_fill_color_;
  std::string active_stroke_color_;
  int active_stroke_width_;
  double active_rr_radius_;
  int active_font_size_;
  TextObject* editing_text_;
  std::string active_font_family_;
  // Mouse positions below are in world (diagram) coordinates
  QPointF last_mouse_pos_;
  QPointF create_start_;
  QPointF drag_start_;
  // Infinite canvas view: screen = world * zoom_ + pan_
  double zoom_;
  QPointF pan_;
  bool is_panning_;   // Middle/right mouse drag in progress
  QPointF pan_last_;  // Last screen position while panning
  QPointF ToWorld(const QPointF& screen) const;
  void ZoomAt(const QPointF& screen_pos, double factor);
  // Helpers
  bool IsPointInsideBoundingBox(GraphicsObject* obj,
                                const QPointF& point) const;
  bool IsPointInsideResizeStart(GraphicsObject* obj,
                                const QPointF& point) const;
  bool IsPointInsideResizeEnd(GraphicsObject* obj, const QPointF& point) const;
  bool IsPointInsideLast(GraphicsObject* obj, const QPointF& point) const;
  bool is_creating_;
  bool is_typing_text_;
  bool is_drawing_freehand_;
  bool is_resize1_;
  bool is_resize2_;
  bool is_resize_3_;
  bool active_tool_text_;
  void DeleteSelectedObject();
  void RemoveEmptyTexts();  // Drops empty text objects not being edited
  void FinishTextEditing();  // Ends a text edit in progress (Enter/tool change)
  std::vector<std::string> undo_stack_;
  std::vector<std::string> redo_stack_;
  std::string pending_undo_state_;  // State before a select/move/resize
  std::string text_undo_state_;     // State before a double-click text edit
  void PushUndoState();
  // Push an earlier state (a change happened, so redo is cleared)
  void PushUndoSnapshot(const std::string& svg);
  // Record text_undo_state_ right before the first real change to the text
  void RecordTextEditUndo();
};

#endif  // SRC_UI_HEADERS_CANVAS_H_