#include <QFont>
#include <QFontMetrics>
#include <algorithm>
#include <cmath>

#include "../../headers/text.h"

namespace {
// Where Draw() puts the text baseline relative to the object's (x_, y_):
// 6px right and 6px + font ascent down. SVG x/y mean the baseline start, so
// this offset is added when saving and removed when loading.
// Must build the font exactly like TextObject::Draw().
QPointF BaselineOffset(const std::string& family, int point_size) {
  QFont font;
  font.setPointSize(point_size);
  font.setFamily(QString::fromStdString(family));
  return QPointF(6, 6 + QFontMetrics(font).ascent());
}

// Replaces XML special characters (& < >) with entities for saving
std::string EscapeXml(const std::string& s) {
  std::string out;
  for (char c : s) {
    if (c == '&') out += "&amp;";
    else if (c == '<') out += "&lt;";
    else if (c == '>') out += "&gt;";
    else out += c;
  }
  return out;
}

// Converts XML entities back to characters when loading
std::string UnescapeXml(const std::string& s) {
  const std::pair<std::string, char> entities[] = {
      {"&amp;", '&'}, {"&lt;", '<'}, {"&gt;", '>'},
      {"&quot;", '"'}, {"&apos;", '\''}};
  std::string out;
  for (std::size_t i = 0; i < s.size(); ++i) {
    bool replaced = false;
    for (const auto& e : entities) {
      if (s.compare(i, e.first.size(), e.first) == 0) {
        out += e.second;
        i += e.first.size() - 1;
        replaced = true;
        break;
      }
    }
    if (!replaced) out += s[i];
  }
  return out;
}
}  // namespace

// Exports to SVG
// In SVG, "fill" is the colour of the letters, so the text colour (kept in
// stroke_color_) is written as fill. The background box colour (fill_color_)
// has no SVG equivalent and is kept in data-background for this editor.
// x/y are written as the baseline start and the size with a "pt" unit, so
// other viewers place and size the text exactly as the editor draws it.
std::string TextObject::ToSvg() const {
  // An empty text box (just placed, nothing typed yet) is not part of the
  // drawing: write nothing, so it is never saved or counted as a change
  if (text_.empty()) return "";
  QPointF off = BaselineOffset(font_family_, font_size_);
  return "<text\n\tx=\"" + std::to_string(x_ + off.x()) + "\"\n\ty=\"" +
         std::to_string(y_ + off.y()) + "\"\n\tfill=\"" + stroke_color_ +
         "\"\n\tdata-background=\"" + fill_color_ + "\"\n\tfont-size=\"" +
         std::to_string(font_size_) + "pt\"\n\tfont-family=\"" +
         font_family_ + "\">" + EscapeXml(text_) + "</text>\n";
}

// Helper to extract attribute values
std::string get_attr_text(const std::string& svg, const std::string& attr) {
  std::size_t pos = svg.find(attr + "=\"");
  if (pos != std::string::npos) {
    std::size_t start = pos + attr.length() + 2;
    std::size_t end = svg.find("\"", start);
    if (end != std::string::npos) return svg.substr(start, end - start);
  }
  // Try style attribute
  std::size_t style_pos = svg.find("style=\"");
  if (style_pos != std::string::npos) {
    std::size_t style_start = style_pos + 7;
    std::size_t style_end = svg.find("\"", style_start);
    if (style_end != std::string::npos) {
      std::string style = svg.substr(style_start, style_end - style_start);
      std::size_t attr_pos = style.find(attr + ":");
      if (attr_pos != std::string::npos) {
        std::size_t val_start = attr_pos + attr.length() + 1;
        std::size_t val_end = style.find(";", val_start);
        if (val_end == std::string::npos) val_end = style.length();
        return style.substr(val_start, val_end - val_start);
      }
    }
  }
  return "";
}

// Imports from SVG
std::unique_ptr<GraphicsObject> TextObject::FromSvg(const std::string& svg) {
  double x = 0, y = 0;
  int font_size = 12;
  // stroke_color = letter colour, fill_color = background box colour
  // (defaults follow SVG: black letters, no background)
  std::string text, fill_color = "#00000000", font_family = "DejaVu Sans",
                    stroke_color = "black";

  std::string val;
  if (!(val = get_attr_text(svg, "x")).empty()) x = std::stod(val);
  if (!(val = get_attr_text(svg, "y")).empty()) y = std::stod(val);
  if (!(val = get_attr_text(svg, "font-family")).empty()) font_family = val;
  std::string bg = get_attr_text(svg, "data-background");

  // Text written by this editor always starts with exactly "<text\n\tx=".
  // Only such elements are checked for the older formats below, so a stroke
  // set by another program (e.g. stroke="none") is never misread.
  bool from_editor = svg.compare(0, 9, "<text\n\tx=") == 0;
  // Oldest format: stroke="..." attribute = letters, fill = background
  std::string legacy_stroke;
  std::size_t stroke_pos = svg.find("\n\tstroke=\"");
  if (from_editor && bg.empty() && stroke_pos != std::string::npos) {
    std::size_t start = stroke_pos + 10;
    legacy_stroke = svg.substr(start, svg.find('"', start) - start);
  }

  // Older editor files wrote x/y as the object origin (not the baseline)
  // and the size in points without a unit
  bool old_layout = false;
  if (!(val = get_attr_text(svg, "font-size")).empty()) {
    std::size_t used = 0;
    double size = std::stod(val, &used);
    std::string unit = val.substr(used);
    old_layout = from_editor && unit.empty();
    // The editor stores points; SVG sizes are px unless marked pt (1px=0.75pt)
    if (unit != "pt" && !old_layout) size *= 0.75;
    font_size = std::max(1, static_cast<int>(std::lround(size)));
  }
  // SVG x/y is the baseline start; convert back to the object's origin
  if (!old_layout) {
    QPointF off = BaselineOffset(font_family, font_size);
    x -= off.x();
    y -= off.y();
  }
  if (!legacy_stroke.empty()) {
    // Oldest editor files: stroke = letters, fill = background
    stroke_color = legacy_stroke;
    if (!(val = get_attr_text(svg, "fill")).empty()) fill_color = val;
  } else {
    if (!(val = get_attr_text(svg, "fill")).empty()) stroke_color = val;
    if (!bg.empty()) fill_color = bg;
  }

  // Extract text content between > and </text>
  std::size_t tag_end = svg.find('>');
  std::size_t closing_tag = svg.find("</text>");
  if (tag_end != std::string::npos && closing_tag != std::string::npos &&
      tag_end < closing_tag) {
    text = svg.substr(tag_end + 1, closing_tag - tag_end - 1);
    std::size_t tspan = text.find("<tspan");
    if (tspan != std::string::npos) {
      std::size_t tspan_end = text.find(">", tspan);
      std::size_t tspan_close = text.find("</tspan>", tspan_end);
      if (tspan_end != std::string::npos && tspan_close != std::string::npos) {
        text = text.substr(tspan_end + 1, tspan_close - tspan_end - 1);
      }
    }
    text = UnescapeXml(text);  // e.g. &lt; back to <
  }

  auto obj = std::make_unique<TextObject>(x, y, text, font_size, font_family);
  obj->SetFillColor(fill_color);
  obj->SetStrokeColor(stroke_color);
  return obj;
}