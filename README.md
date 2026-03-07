# Micro Vector Graphics Editor

A lightweight vector graphics editor built with C++17 and the Qt5 framework. This application allows users to create, view, and modify vector graphics with various shapes and tools.

## Features

- **Shape Support**: Draw multiple geometric shapes including:
  - Circles
  - Rectangles & Rounded Rectangles (with adjustable corner radius)
  - Hexagons
  - Lines
- **Freehand Drawing**: Sketch freely on the canvas.
- **Text Support**: Add text annotations with font family and size customization. Double-click to edit existing text.
- **Object Manipulation**:
  - **Move**: Drag shapes around the canvas.
  - **Resize**: Interactive resizing handles for shapes.
  - **Delete**: Remove selected objects (Delete key).
- **Clipboard & History**:
  - **Undo/Redo**: Full history support to revert and re-apply changes.
  - **Cut, Copy, Paste**: Standard clipboard operations for shapes.
- **Styling**:
  - Customizable **Fill Color** and **Stroke Color** (support for transparency).
  - Adjustable **Stroke Width**.
  - Predefined color palette and custom color pickers.
  - Fill and Stroke tools for quick coloring.
- **File Operations**:
  - Create **New** projects.
  - **Open** existing diagrams.
  - **Save** and **Save As** functionality (supports SVG export).
  - **Close** current project.
<img width="1269" height="892" alt="image" src="https://github.com/user-attachments/assets/d0d3471d-02e5-4815-a184-2047e3f90649" />
## Prerequisites

To build and run this project, you need the following installed:

- **C++ Compiler** supporting C++17 (e.g., GCC, Clang, MSVC).
- **CMake** (version 3.16 or higher).
- **Qt 5** (specifically the `Widgets` module).

## Build Instructions

1.  **Clone the repository** (if you haven't already):

    ```bash
    git clone <repository-url>
    cd Micro-Vector-Graphics-Editor
    ```

    _(Note: Ensure you are in the directory containing `CMakeLists.txt`)_

2.  **Create a build directory**:

    ```bash
    mkdir build
    cd build
    ```

3.  **Configure the project with CMake**:

    ```bash
    cmake ..
    ```

4.  **Build the application**:

    ```bash
    make
    ```

    _(Or `cmake --build .` on Windows/other systems)_

5.  **Run the application**:
    ```bash
    ./program
    ```

## Helper Scripts

Two helper scripts are available at the project root:

- **`./start`**: Configures CMake, builds the project, and runs the application.
- **`./clean`**: Removes the `build/` directory.

Usage:

```bash
./start
./clean
```

## Project Structure

The source code is organized as follows:

- **`src/`**: Contains all source code.
  - **`main.cpp`**: Entry point of the application.
  - **`gui/`**: Handles the graphical user interface.
    - `mainwindow/`: Implementation of the main window logic (menus, toolbar connections).
    - `canvas/`: The drawing area implementation, handling mouse events and painting.
    - `headers/`: Header files for GUI components.
  - **`model/`**: Contains the data structures for vector objects.
    - `implementation/`: Logic for shapes (Circle, Line, Hexagon, etc.) and their SVG representation.
    - `headers/`: Class definitions for the shapes.
  - **`diagram/`**: Manages the collection of shapes (the document model).
  - **`resources/`**: Icons and Qt resource files (`.qrc`).

## Usage

- **Toolbar**: Select tools (Shapes, Freehand, Text) from the toolbar.
- **Color Selection**: Use the color swatches or entering color codes to change Fill/Stroke.
- **Canvas**: Click and drag on the white canvas area to draw shapes.
- **File Menu**: precise control over New, Open, Save, and Save As operations.

## Authors

- Manya Jain
