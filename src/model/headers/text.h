#ifndef SRC_MODEL_HEADERS_TEXT_OBJECT_H_
#define SRC_MODEL_HEADERS_TEXT_OBJECT_H_

#include "graphics_object.h"

// Represents a text label with basic editing
class TextObject : public GraphicsObject {
 private:
  double x_;                 // X coordinate of text origin
  double y_;                 // Y coordinate of text origin
  std::string text_;         // The string content
  int font_size_;            // Font size in points
  std::string font_family_;  // Font family name (default "Deja Vu Sans")
  bool show_cursor_;         // Whether to draw the editing cursor

 public:
  // Constructs a Text object
  TextObject(double x, double y, const std::string& text, int font_size,
             const std::string& font_family = "Deja Vu Sans");

  // Appends character
  void AppendChar(char c);

  // Removes last character
  void Backspace();

  // Replaces text content
  void SetText(const std::string& text);

  // Sets font size
  void SetFontSize(int size);

  // Toggles the editing cursor
  void SetEditing(bool editing);

  // Draws the text
  void Draw(QPainter& painter) const override;
  // Moves the text
  void Move(double dx, double dy) override;
  // Updates geometry (unused for text)
  void SetGeometry(double x, double y, double w, double h,
                   double rounded_rect_radius, double end_x,
                   double end_y) override;
  // Exports to SVG
  std::string ToSvg() const override;
  // Imports from SVG
  std::unique_ptr<GraphicsObject> FromSvg(const std::string& svg) override;
  // Creates a deep copy
  std::unique_ptr<GraphicsObject> Clone() const override;

  void MoveStart(double x, double y) override;

  void MoveEnd(double x, double y) override;

  void MoveLast(double x, double y) override;

  std::pair<double, double> GetStart() const override;

  std::pair<double, double> GetEnd() const override;

  std::pair<double, double> GetLast() const override;
};

#endif
