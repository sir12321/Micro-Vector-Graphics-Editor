// Definition of the Text graphics object.

#ifndef SRC_MODEL_HEADERS_TEXT_OBJECT_H_
#define SRC_MODEL_HEADERS_TEXT_OBJECT_H_

#include "graphics_object.h"

// Represents a text label.
//
// Supports typing, backspace, and cursor display for basic editing.
class TextObject : public GraphicsObject {
 private:
  double x_;                 // X coordinate of text origin.
  double y_;                 // Y coordinate of text origin.
  std::string text_;         // The string content.
  int font_size_;            // Font size in points.
  std::string font_family_;  // Font family name (default "Deja Vu Sans").
  bool show_cursor_;         // Whether to draw the editing cursor.

 public:
  // Constructs a Text object.
  TextObject(double x, double y, const std::string& text, int font_size,
             const std::string& font_family = "Deja Vu Sans");

  // Appends a character to the text content.
  void AppendChar(char c);

  // Removes the last character (Backspace functionality).
  void Backspace();

  // Replaces text content entirely.
  void SetText(const std::string& text);

  // Toggles the visibility of the text cursor.
  // Called when selected/deselected or when finishing edit.
  void SetEditing(bool editing);

  void Draw(QPainter& painter) const override;
  void Move(double dx, double dy) override;
  void SetGeometry(double x, double y, double w, double h,
                   double rounded_rect_radius, double end_x,
                   double end_y) override;
  std::string ToSvg() const override;
  std::unique_ptr<GraphicsObject> FromSvg(const std::string& svg) override;
  std::unique_ptr<GraphicsObject> Clone() const override;

  void MoveStart(double x, double y) override;

  void MoveEnd(double x, double y) override;

  std::pair<double, double> GetStart() const override;

  std::pair<double, double> GetEnd() const override;
};

#endif
