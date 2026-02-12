#include "../../headers/text.h"

TextObject::TextObject(double x, double y, const std::string& text,
                       int font_size, const std::string& font_family)
    : x_(x),
      y_(y),
      text_(text),
      font_size_(font_size),
      font_family_(font_family),
      show_cursor_(false) {
  id_ = "text";
  stroke_width_ = 0;
  bbox_x_ = x_ - 6;
  bbox_y_ = y_ - 6;
  bbox_width_ = (text_.length()) * font_size_ + 18;
  bbox_height_ = font_size_ + 30;
}

// Appends character
void TextObject::AppendChar(char c) { text_ += c; }

// Removes last character
void TextObject::Backspace() {
  if (!text_.empty()) {
    text_.pop_back();
  }
}

void TextObject::SetText(const std::string& text) { text_ = text; }

// Controls cursor visibility
void TextObject::SetEditing(bool editing) { show_cursor_ = editing; }

// Draws the text
void TextObject::Draw(QPainter& painter) const {
  QFont font;
  font.setPointSize(font_size_);
  font.setFamily(QString::fromStdString(font_family_));
  painter.setFont(font);

  QFontMetrics fm(font);

  int text_width = fm.horizontalAdvance(QString::fromStdString(text_));
  int text_height = fm.height();
  int pad = 6;

  bbox_width_ = text_width + pad * 4;
  bbox_height_ = text_height + pad * 4;

  painter.setBrush(QColor(QString::fromStdString(fill_color_)));
  painter.setPen(QColor(QString::fromStdString(fill_color_)));
  painter.drawRect(bbox_x_ + pad, bbox_y_ + pad, text_width + pad * 2,
                   text_height + pad * 2);

  painter.setPen(QColor(QString::fromStdString(stroke_color_)));
  painter.drawText(QPointF(bbox_x_ + 2 * pad, bbox_y_ + 2 * pad + fm.ascent()),
                   QString::fromStdString(text_));

  if (show_cursor_) {
    int cursor_x = bbox_x_ + 2 * pad + text_width;
    int top = bbox_y_ + 2 * pad;
    int bottom = top + text_height;
    painter.setPen(Qt::black);
    painter.drawLine(cursor_x, top, cursor_x, bottom);
    QPen box_pen(Qt::blue);
    box_pen.setStyle(Qt::DashLine);
    painter.setPen(box_pen);
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(bbox_x_, bbox_y_, bbox_width_, bbox_height_);
  }
}

// Moves the text
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

void TextObject::SetFontSize(int size) { font_size_ = size; }

void TextObject::MoveStart(double x, double y) {}

void TextObject::MoveEnd(double x, double y) {}

std::pair<double, double> TextObject::GetStart() const { return {x_, y_}; }

std::pair<double, double> TextObject::GetEnd() const { return {x_, y_}; }