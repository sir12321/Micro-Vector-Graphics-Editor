#ifndef SRC_MODEL_SHAPE_FACTORY_H_
#define SRC_MODEL_SHAPE_FACTORY_H_

#include <QPointF>
#include <algorithm>
#include <cmath>
#include <memory>
#include <string>

#include "../../gui/headers/tools.h"
#include "../headers/circle.h"
#include "../headers/graphics_object.h"
#include "../headers/hexagon.h"
#include "../headers/line.h"
#include "../headers/rectangle.h"
#include "../headers/rounded_rectangle.h"
#include "../headers/text.h"

// Factory function to create shape objects (start/end in world coordinates)
std::unique_ptr<GraphicsObject> CreateShape(Tool tool, const QPointF& start,
                                            const QPointF& end,
                                            const std::string& fill_color,
                                            const std::string& stroke_color,
                                            int stroke_width,
                                            double rounded_rect_radius = 0.15,
                                            int canvas_font_size = 9);

#endif  // SRC_MODEL_SHAPE_FACTORY_H_
