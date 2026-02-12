#include "../../headers/rectangle.h"

// Exports to SVG
std::string Rectangle::ToSvg() const {
  return "<rect\n\tx=\"" + std::to_string(cx_ - width_ / 2.0) + "\"\n\ty=\"" +
         std::to_string(cy_ - height_ / 2.0) + "\"\n\twidth=\"" +
         std::to_string(width_) + "\"\n\theight=\"" + std::to_string(height_) +
         "\"\n\tstroke=\"" + stroke_color_ + "\"\n\tstroke-width=\"" +
         std::to_string(stroke_width_) + "\"\n\tfill=\"" + fill_color_ +
         "\" />\n";
}

// Helper for parsing SVG attributes
std::string get_attr(const std::string& svg, const std::string& attr) {
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
std::unique_ptr<GraphicsObject> Rectangle::FromSvg(const std::string& svg) {
  double x = 0, y = 0, width = 0, height = 0;
  int stroke_width = 0;
  std::string fill_color = "white", stroke_color = "black";

  std::string val;
  if (!(val = get_attr(svg, "x")).empty()) x = std::stod(val);
  if (!(val = get_attr(svg, "y")).empty()) y = std::stod(val);
  if (!(val = get_attr(svg, "width")).empty()) width = std::stod(val);
  if (!(val = get_attr(svg, "height")).empty()) height = std::stod(val);
  if (!(val = get_attr(svg, "stroke-width")).empty())
    stroke_width = std::stoi(val);
  if (!(val = get_attr(svg, "fill")).empty()) fill_color = val;
  if (!(val = get_attr(svg, "stroke")).empty()) stroke_color = val;

  auto obj = std::make_unique<Rectangle>(x + width / 2.0, y + height / 2.0,
                                         width, height, stroke_width);
  obj->SetFillColor(fill_color);
  obj->SetStrokeWidth(stroke_width);
  obj->SetStrokeColor(stroke_color);
  return obj;
}