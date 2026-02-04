#ifndef SRC_MODEL_SHAPE_FACTORY_H_
#define SRC_MODEL_SHAPE_FACTORY_H_

#include <QPoint>
#include <memory>

#include "../../gui/headers/tools.h"
#include "../headers/graphics_object.h"

std::unique_ptr<GraphicsObject> CreateShape(Tool tool, const QPoint& start,
                                            const QPoint& end,
                                            const std::string& fill_color,
                                            const std::string& stroke_color,
                                            int stroke_width,
                                            double rounded_rect_radius = 0.15,
                                            int canvas_font_size = 9);

#endif  // SRC_MODEL_SHAPE_FACTORY_H_
