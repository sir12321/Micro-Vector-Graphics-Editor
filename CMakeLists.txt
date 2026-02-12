cmake_minimum_required(VERSION 3.16)

project(MicroVectorEditor LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Qt5
find_package(Qt5 REQUIRED COMPONENTS Widgets)

# Enable Qt code generators
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_executable(program
    src/main.cpp

    # GUI
    src/gui/implementation/mainwindow.cpp
    src/gui/headers/mainwindow.h
    src/gui/implementation/mainwindow.ui
    src/gui/implementation/mainwindow/color_setter.cpp
    src/gui/implementation/mainwindow/fill_color_setter.cpp
    src/gui/implementation/mainwindow/stroke_color_setter.cpp
    src/gui/implementation/mainwindow/connect.cpp
    src/gui/implementation/mainwindow/default_initialise.cpp
    src/gui/implementation/mainwindow/open_save_saveas.cpp
    src/gui/implementation/mainwindow/toggle_tool.cpp
    src/gui/implementation/canvas/canvas_core.cpp
    src/gui/implementation/canvas/canvas_get_set.cpp
    src/gui/implementation/canvas/canvas_key.cpp
    src/gui/implementation/canvas/canvas_paint.cpp
    src/gui/implementation/canvas/canvas_cursor.cpp
    src/gui/implementation/canvas/undo_redo.cpp
    src/gui/implementation/canvas/mouse/mouse_double_click_event.cpp
    src/gui/implementation/canvas/mouse/mouse_move_event.cpp
    src/gui/implementation/canvas/mouse/mouse_press_event.cpp
    src/gui/implementation/canvas/mouse/mouse_release_event.cpp
    src/gui/headers/canvas.h
    src/gui/headers/tools.h

    # Diagram
    src/diagram/diagram.cpp
    src/diagram/diagram.h

    # Model
    src/model/implementation/graphics_object.cpp
    src/model/headers/graphics_object.h
    
    src/model/implementation/circle/circle.cpp
    src/model/implementation/circle/circle_svg.cpp
    src/model/headers/circle.h
    
    src/model/implementation/freehand/freehand.cpp
    src/model/implementation/freehand/freehand_svg.cpp
    src/model/headers/freehand.h
    
    src/model/implementation/hexagon/hexagon.cpp
    src/model/implementation/hexagon/hexagon_svg.cpp
    src/model/headers/hexagon.h
    
    src/model/implementation/line/line.cpp
    src/model/implementation/line/line_svg.cpp
    src/model/headers/line.h
    
    src/model/implementation/rectangle/rectangle.cpp
    src/model/implementation/rectangle/rectangle_svg.cpp
    src/model/headers/rectangle.h
    
    src/model/implementation/rounded_rectangle/rounded_rectangle.cpp
    src/model/implementation/rounded_rectangle/rounded_rectangle_svg.cpp
    src/model/headers/rounded_rectangle.h
    
    src/model/implementation/text/text.cpp
    src/model/implementation/text/text_svg.cpp
    src/model/headers/text.h

    # Shape Factory
    src/model/shape_factory/shape_factory.cpp
    src/model/shape_factory/shape_factory.h

    # Resources
    resources/icons.qrc
)

target_include_directories(program PRIVATE
    ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(program
    Qt5::Widgets
)
