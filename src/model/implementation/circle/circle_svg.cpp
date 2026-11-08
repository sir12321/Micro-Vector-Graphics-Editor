#include "../../headers/circle.h"

// Exports to SVG
std::string Circle::ToSvg() const {
  return "<ellipse\n\tcx=\"" + std::to_string(cx_) + "\"\n\tcy=\"" +
         std::to_string(cy_) + "\"\n\trx=\"" + std::to_string(rx_) +
         "\"\n\try=\"" + std::to_string(ry_) + "\"\n\tfill=\"" + fill_color_ +
         "\"\n\tstroke=\"" + stroke_color_ + "\"\n\tstroke-width=\"" +
         std::to_string(stroke_width_) + "\" />\n";
}

// Imports from SVG
std::unique_ptr<GraphicsObject> Circle::FromSvg(const std::string& svg) {
  double cx = 0, cy = 0, rx = 0, ry = 0;
  int stroke_width = 0;
  std::string fill_color = "white", stroke_color = "black";

  // Read each attribute as attr="value", falling back to style="attr:value"
  const std::string attrs[7] = {"cx", "cy",           "rx",    "ry",
                                "stroke-width", "fill", "stroke"};
  std::string vals[7];
  for (int i = 0; i < 7; ++i) {
    const std::string& attr = attrs[i];
    std::size_t pos = svg.find(attr + "=\"");
    if (pos != std::string::npos) {
      std::size_t start = pos + attr.length() + 2;
      std::size_t end = svg.find("\"", start);
      if (end != std::string::npos) {
        vals[i] = svg.substr(start, end - start);
        continue;
      }
    }
    std::size_t style_pos = svg.find("style=\"");
    if (style_pos == std::string::npos) continue;
    std::size_t style_start = style_pos + 7;
    std::size_t style_end = svg.find("\"", style_start);
    if (style_end == std::string::npos) continue;
    std::string style = svg.substr(style_start, style_end - style_start);
    std::size_t attr_pos = style.find(attr + ":");
    if (attr_pos == std::string::npos) continue;
    std::size_t val_start = attr_pos + attr.length() + 1;
    std::size_t val_end = style.find(";", val_start);
    if (val_end == std::string::npos) val_end = style.length();
    vals[i] = style.substr(val_start, val_end - val_start);
  }

  if (!vals[0].empty()) cx = std::stod(vals[0]);
  if (!vals[1].empty()) cy = std::stod(vals[1]);
  if (!vals[2].empty()) rx = std::stod(vals[2]);
  if (!vals[3].empty()) ry = std::stod(vals[3]);
  if (!vals[4].empty()) stroke_width = std::stoi(vals[4]);
  if (!vals[5].empty()) fill_color = vals[5];
  if (!vals[6].empty()) stroke_color = vals[6];

  auto obj = std::make_unique<Circle>(cx, cy, (rx + ry) / 2, stroke_width);
  obj->SetGeometry(cx, cy, 0, 0, 0, cx + rx, cy + ry);
  obj->SetFillColor(fill_color);
  obj->SetStrokeWidth(stroke_width);
  obj->SetStrokeColor(stroke_color);
  return obj;
}