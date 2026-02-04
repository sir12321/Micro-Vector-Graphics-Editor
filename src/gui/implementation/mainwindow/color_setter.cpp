#include <QColorDialog>

#include "../../headers/canvas.h"
#include "../../headers/mainwindow.h"
#include "../ui_mainwindow.h"

void MainWindow::setcolor_9_appearance() {
  ui_->pushButton_9->setStyleSheet(
      "background-color: " +
      QString::fromStdString(canvas_->GetActiveStrokeColor()) + ";");
  ui_->lineEdit_2->setText(
      QString::fromStdString(canvas_->GetActiveStrokeColor()));
}
void MainWindow::setcolor_8_appearance() {
  ui_->pushButton_8->setStyleSheet(
      "background-color: " +
      QString::fromStdString(canvas_->GetActiveFillColor()) + ";");
  ui_->lineEdit->setText(QString::fromStdString(canvas_->GetActiveFillColor()));
}
void MainWindow::ApplyFillColorFromLineEdit() {
  QString text = ui_->lineEdit->text().trimmed();

  // Allow user to omit '#'
  if (!text.startsWith("#")) {
    text = "#" + text;
  }
  QColor color(text);

  // Validate color
  if (!color.isValid()) {
    ui_->lineEdit->setStyleSheet("border: 2px solid red;");
    return;
  }

  // Reset error state
  ui_->lineEdit->setStyleSheet("");

  // Update Canvas state
  canvas_->SetActiveFillColor(color.name().toStdString());
  setcolor_8_appearance();

  // Update button appearance
  ui_->pushButton_8->setStyleSheet("background-color: " + color.name() +
                                  "; border: 1px solid black;");
}
void MainWindow::ApplyStrokeColorFromLineEdit() {
  QString text = ui_->lineEdit_2->text().trimmed();

  // Allow user to omit '#'
  if (!text.startsWith("#")) {
    text = "#" + text;
  }
  QColor color(text);

  // Validate color
  if (!color.isValid()) {
    ui_->lineEdit_2->setStyleSheet("border: 2px solid red;");
    return;
  }

  // Reset error state
  ui_->lineEdit_2->setStyleSheet("");

  // Update Canvas state
  canvas_->SetActiveStrokeColor(color.name().toStdString());

  // Update button appearance
  ui_->pushButton_9->setStyleSheet("background-color: " + color.name() +
                                  "; border: 1px solid black;");
  setcolor_9_appearance();
}
void MainWindow::ChooseFillColor() {
  QColor color = QColorDialog::getColor(Qt::white, this, "Choose Fill Color");

  if (!color.isValid()) return;

  // Update Canvas state
  canvas_->SetActiveFillColor(color.name().toStdString());

  setcolor_8_appearance();
}
void MainWindow::ChooseStrokeColor() {
  QColor color = QColorDialog::getColor(Qt::black, this, "Choose Stroke Color");

  if (!color.isValid()) return;

  // Update Canvas state
  canvas_->SetActiveStrokeColor(color.name().toStdString());

  // Update button appearance
  setcolor_9_appearance();
}
void MainWindow::setfillcolortransparent() {
  canvas_->SetActiveFillColor("#00000000");
  setcolor_8_appearance();
}
void MainWindow::setfillcolorwhite() {
  canvas_->SetActiveFillColor("#FFFFFF");
  setcolor_8_appearance();
}
void MainWindow::setfillcolorred() {
  canvas_->SetActiveFillColor("#FF0000");
  setcolor_8_appearance();
}
void MainWindow::setfillcolororange() {
  canvas_->SetActiveFillColor("#FFA500");
  setcolor_8_appearance();
}
void MainWindow::setfillcoloryellow() {
  canvas_->SetActiveFillColor("#FFFF00");
  setcolor_8_appearance();
}
void MainWindow::setfillcolorlightgreen() {
  canvas_->SetActiveFillColor("#90EE90");
  setcolor_8_appearance();
}
void MainWindow::setfillcolorgreen() {
  canvas_->SetActiveFillColor("#008000");
  setcolor_8_appearance();
}
void MainWindow::setfillcolorblack() {
  canvas_->SetActiveFillColor("#000000");
  setcolor_8_appearance();
}
void MainWindow::setfillcolorgrey() {
  canvas_->SetActiveFillColor("#808080");
  setcolor_8_appearance();
}
void MainWindow::setfillcolordarkblue() {
  canvas_->SetActiveFillColor("#00008B");
  setcolor_8_appearance();
}
void MainWindow::setfillcolorskyblue() {
  canvas_->SetActiveFillColor("#87CEEB");
  setcolor_8_appearance();
}
void MainWindow::setfillcolorpurple() {
  canvas_->SetActiveFillColor("#800080");
  setcolor_8_appearance();
}
void MainWindow::setfillcolorbrown() {
  canvas_->SetActiveFillColor("#A52A2A");
  setcolor_8_appearance();
}
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
  // Update Canvas state
  canvas_->SetActiveStrokeWidth(value);
}
void MainWindow::setstrokecolortransparent() {
  canvas_->SetActiveStrokeColor("#00000000");
  setcolor_9_appearance();
}