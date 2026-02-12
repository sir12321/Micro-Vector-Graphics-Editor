#include <algorithm>

#include "../../headers/line.h"

// Exports to SVG
std::string Line::ToSvg() const {
  return "<line\n\tx1=\"" + std::to_string(x1_) + "\"\n\ty1=\"" +
         std::to_string(y1_) + "\"\n\tx2=\"" + std::to_string(x2_) +
         "\"\n\ty2=\"" + std::to_string(y2_) + "\"\n\tstroke=\"" +
         stroke_color_ + "\"\n\tstroke-width=\"" +
         std::to_string(stroke_width_) + "\" />\n";
}

// Helper for parsing SVG attributes
std::string get_attr_line(const std::string& svg, const std::string& attr) {
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
std::unique_ptr<GraphicsObject> Line::FromSvg(const std::string& svg) {
  double x1 = 0, y1 = 0, x2 = 0, y2 = 0;
  int stroke_width = 0;
  std::string stroke_color = "black";

  std::string val;
  if (!(val = get_attr_line(svg, "x1")).empty()) x1 = std::stod(val);
  if (!(val = get_attr_line(svg, "y1")).empty()) y1 = std::stod(val);
  if (!(val = get_attr_line(svg, "x2")).empty()) x2 = std::stod(val);
  if (!(val = get_attr_line(svg, "y2")).empty()) y2 = std::stod(val);
  if (!(val = get_attr_line(svg, "stroke-width")).empty())
    stroke_width = std::stoi(val);
  if (!(val = get_attr_line(svg, "stroke")).empty()) stroke_color = val;

  auto obj = std::make_unique<Line>(x1, y1, x2, y2, stroke_width);
  obj->SetStrokeColor(stroke_color);
  obj->SetStrokeWidth(stroke_width);
  return obj;
}