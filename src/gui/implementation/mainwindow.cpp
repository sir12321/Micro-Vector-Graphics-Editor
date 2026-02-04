#include "../headers/mainwindow.h"

#include <QColorDialog>
#include <QVBoxLayout>

#include "../headers/canvas.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui_(new Ui::MainWindow), active_tool_(Tool::None) {
  ui_->setupUi(this);

  // ---- Canvas ----
  canvas_ = new Canvas(diagram_, ui_->canvas_container);
  auto* layout = new QVBoxLayout(ui_->canvas_container);
  layout->setContentsMargins(0, 0, 0, 0);
  layout->addWidget(canvas_);

  setWindowTitle("Micro Vector Editor");
  MainWindow::connectSignals();
  MainWindow::initialise();
}

MainWindow::~MainWindow() { delete ui_; }
