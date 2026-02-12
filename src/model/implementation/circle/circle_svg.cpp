#include "../../headers/circle.h"

// Exports to SVG
std::string Circle::ToSvg() const {
  return "<ellipse\n\tcx=\"" + std::to_string(cx_) + "\"\n\tcy=\"" +
         std::to_string(cy_) + "\"\n\trx=\"" + std::to_string(rx_) +
         "\"\n\try=\"" + std::to_string(ry_) + "\"\n\tfill=\"" + fill_color_ +
         "\"\n\tstroke=\"" + stroke_color_ + "\"\n\tstroke-width=\"" +
         std::to_string(stroke_width_) + "\" />\n";
}

// Helper to parse space-separated attributes
std::string get_attr_circle(const std::string& svg, const std::string& attr) {
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
std::unique_ptr<GraphicsObject> Circle::FromSvg(const std::string& svg) {
  double cx = 0, cy = 0, rx = 0, ry = 0;
  int stroke_width = 0;
  std::string fill_color = "white", stroke_color = "black";

  std::string val;
  if (!(val = get_attr_circle(svg, "cx")).empty()) cx = std::stod(val);
  if (!(val = get_attr_circle(svg, "cy")).empty()) cy = std::stod(val);
  if (!(val = get_attr_circle(svg, "rx")).empty()) rx = std::stod(val);
  if (!(val = get_attr_circle(svg, "ry")).empty()) ry = std::stod(val);
  if (!(val = get_attr_circle(svg, "stroke-width")).empty())
    stroke_width = std::stoi(val);
  if (!(val = get_attr_circle(svg, "fill")).empty()) fill_color = val;
  if (!(val = get_attr_circle(svg, "stroke")).empty()) stroke_color = val;

  auto obj = std::make_unique<Circle>(cx, cy, (rx + ry) / 2, stroke_width);
  obj->SetGeometry(cx, cy, 0, 0, 0, cx + rx, cy + ry);
  obj->SetFillColor(fill_color);
  obj->SetStrokeWidth(stroke_width);
  obj->SetStrokeColor(stroke_color);
  return obj;
}