#include "../../headers/mainwindow.h"

// Stroke Color Setters
void MainWindow::setstrokecolorwhite() {
  canvas_->SetActiveStrokeColor("#FFFFFF");
  setcolor_9_appearance();
}
void MainWindow::setstrokecolorred() {
  canvas_->SetActiveStrokeColor("#FF0000");
  setcolor_9_appearance();
}
void MainWindow::setstrokecolororange() {
  canvas_->SetActiveStrokeColor("#FFA500");
  setcolor_9_appearance();
}
void MainWindow::setstrokecoloryellow() {
  canvas_->SetActiveStrokeColor("#FFFF00");
  setcolor_9_appearance();
}
void MainWindow::setstrokecolorlightgreen() {
  canvas_->SetActiveStrokeColor("#90EE90");
  setcolor_9_appearance();
}
void MainWindow::setstrokecolorgreen() {
  canvas_->SetActiveStrokeColor("#008000");
  setcolor_9_appearance();
}
void MainWindow::setstrokecolorblack() {
  canvas_->SetActiveStrokeColor("#000000");
  setcolor_9_appearance();
}
void MainWindow::setstrokecolorgrey() {
  canvas_->SetActiveStrokeColor("#808080");
  setcolor_9_appearance();
}
void MainWindow::setstrokecolordarkblue() {
  canvas_->SetActiveStrokeColor("#00008B");
  setcolor_9_appearance();
}
void MainWindow::setstrokecolorskyblue() {
  canvas_->SetActiveStrokeColor("#87CEEB");
  setcolor_9_appearance();
}
void MainWindow::setstrokecolorpurple() {
  canvas_->SetActiveStrokeColor("#800080");
  setcolor_9_appearance();
}
void MainWindow::setstrokecolorbrown() {
  canvas_->SetActiveStrokeColor("#A52A2A");
  setcolor_9_appearance();
}

void MainWindow::StrokeWidthChanged(int value) {
  canvas_->SetActiveStrokeWidth(value);
}

void MainWindow::setstrokecolortransparent() {
  canvas_->SetActiveStrokeColor("#00000000");
  setcolor_9_appearance();
}
void MainWindow::ApplyFontFromComboBox() {
  QFont currentFont = ui_->fontComboBox->currentFont();
  canvas_->SetActiveFontFamily(currentFont);
}