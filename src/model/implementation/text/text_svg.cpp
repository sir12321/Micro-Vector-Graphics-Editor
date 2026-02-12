#include "../../headers/text.h"

// Exports to SVG
std::string TextObject::ToSvg() const {
  return "<text\n\tx=\"" + std::to_string(x_) + "\"\n\ty=\"" +
         std::to_string(y_) + "\"\n\tstroke=\"" + stroke_color_ +
         "\"\n\tfill=\"" + fill_color_ + "\"\n\tfont-size=\"" +
         std::to_string(font_size_) + "\"\n\tfont-family=\"" + font_family_ +
         "\">" + text_ + "</text>\n";
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
  std::string text, fill_color = "black", font_family = "Deja Vu Sans",
                    stroke_color = "black";

  std::string val;
  if (!(val = get_attr_text(svg, "x")).empty()) x = std::stod(val);
  if (!(val = get_attr_text(svg, "y")).empty()) y = std::stod(val);
  if (!(val = get_attr_text(svg, "font-size")).empty())
    font_size = std::stoi(val);
  if (!(val = get_attr_text(svg, "font-family")).empty()) font_family = val;
  if (!(val = get_attr_text(svg, "fill")).empty()) fill_color = val;
  if (!(val = get_attr_text(svg, "stroke")).empty()) stroke_color = val;

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
  }

  auto obj = std::make_unique<TextObject>(x, y, text, font_size, font_family);
  obj->SetFillColor(fill_color);
  obj->SetStrokeColor(stroke_color);
  return obj;
}