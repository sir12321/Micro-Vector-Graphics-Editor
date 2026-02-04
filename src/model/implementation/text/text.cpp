// Implementation of the TextObject class.

#include "../../headers/text.h"

using namespace std;

// Constructor sets up initial text properties and calculates approximate
// bounding box.
TextObject::TextObject(double x, double y, const string& text, int font_size,
                       const string& font_family)
    : x_(x),
      y_(y),
      text_(text),
      font_size_(font_size),
      font_family_(font_family),
      show_cursor_(false) {
  id_ = "text";
  stroke_width_ = 0;  // Text objects don't have strokes in this simple model
  bbox_x_ = x_;
  bbox_y_ = y_;                                      // baseline approximation
  bbox_width_ = (text_.length()) * font_size_ + 18;  // rough width heuristic
  bbox_height_ = font_size_ + 30;
}

// Adds a character to the string.
void TextObject::AppendChar(char c) { text_ += c; }

// Removes the last character.
void TextObject::Backspace() {
  if (!text_.empty()) {
    text_.pop_back();
  }
}

void TextObject::SetText(const std::string& text) { text_ = text; }

// Controls cursor visibility state.
void TextObject::SetEditing(bool editing) { show_cursor_ = editing; }

// Draws the text and optionally the cursor/editing box.
// Uses QFontMetrics to try and get accurate sizes, but relies on heuristics for
// bounding box elsewhere.
void TextObject::Draw(QPainter& painter) const {
  QFont font;
  font.setPointSize(font_size_);
  font.setFamily(QString::fromStdString(font_family_));
  painter.setFont(font);

  QFontMetrics fm(font);

  int text_width = fm.horizontalAdvance(QString::fromStdString(text_));
  int text_height = fm.height();
  int pad = 6;

  painter.setPen(QColor(QString::fromStdString(fill_color_)));
  painter.drawText(QPointF(bbox_x_ + pad, bbox_y_ + pad + fm.ascent()),
                   QString::fromStdString(text_));

  if (show_cursor_) {
    int cursor_x = bbox_x_ + pad + text_width;
    int top = bbox_y_ + pad;
    int bottom = top + text_height;

    painter.drawLine(cursor_x, top, cursor_x, bottom);

    // Update bounding box dynamically while typing so clicks register correctly
    bbox_width_ = (text_.length()) * font_size_ + 18;
    bbox_height_ = bottom - top + 12;
    QPen box_pen(Qt::blue);
    box_pen.setStyle(Qt::DashLine);
    painter.setPen(box_pen);
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(bbox_x_, bbox_y_, bbox_width_, bbox_height_);
  }
}

// Translates the text object.
void TextObject::Move(double dx, double dy) {
  x_ += dx;
  y_ += dy;
  bbox_x_ += dx;
  bbox_y_ += dy;
}

void TextObject::SetGeometry(double x, double y, double w, double h,
                             double rounded_rect_radius, double end_x,
                             double end_y) {}

std::unique_ptr<GraphicsObject> TextObject::Clone() const {
  auto t =
      std::make_unique<TextObject>(x_, y_, text_, font_size_, font_family_);
  t->SetStrokeColor(stroke_color_);
  t->SetStrokeWidth(stroke_width_);
  t->SetFillColor(fill_color_);
  return t;
}

void TextObject::MoveStart(double x, double y) {}

void TextObject::MoveEnd(double x, double y) {}

std::pair<double, double> TextObject::GetStart() const { return {x_, y_}; }

std::pair<double, double> TextObject::GetEnd() const { return {x_, y_}; }