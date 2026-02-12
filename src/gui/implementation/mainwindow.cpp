#include "../headers/mainwindow.h"

// Initialize main window, setup UI components and canvas
MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui_(new Ui::MainWindow), active_tool_(Tool::None) {
  ui_->setupUi(this);

  // Set up the drawing canvas within its container
  canvas_ = new Canvas(diagram_, ui_->canvas_container);
  auto* layout = new QVBoxLayout(ui_->canvas_container);
  layout->setContentsMargins(0, 0, 0, 0);
  layout->addWidget(canvas_);

  setWindowTitle("Micro Vector Editor");
  MainWindow::connectSignals();
  MainWindow::initialise();
}

// Clean up UI resources
MainWindow::~MainWindow() { delete ui_; }
