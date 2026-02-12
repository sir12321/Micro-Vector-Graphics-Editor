#include "../../headers/mainwindow.h"

// Updates the active stroke color UI (button and text)
void MainWindow::setcolor_9_appearance() {
  ui_->pushButton_9->setStyleSheet(
      "background-color: " +
      QString::fromStdString(canvas_->GetActiveStrokeColor()) + ";");
  ui_->lineEdit_2->setText(
      QString::fromStdString(canvas_->GetActiveStrokeColor()));
}

// Updates the active fill color UI (button and text)
void MainWindow::setcolor_8_appearance() {
  ui_->pushButton_8->setStyleSheet(
      "background-color: " +
      QString::fromStdString(canvas_->GetActiveFillColor()) + ";");
  ui_->lineEdit->setText(QString::fromStdString(canvas_->GetActiveFillColor()));
}

// Parses hex color from the input field and applies it to Fill
void MainWindow::ApplyFillColorFromLineEdit() {
  QString text = ui_->lineEdit->text().trimmed();
  if (!text.startsWith("#")) {
    text = "#" + text;
  }
  QColor color(text);
  if (!color.isValid()) {
    ui_->lineEdit->setStyleSheet("border: 2px solid red;");
    return;
  }
  ui_->lineEdit->setStyleSheet("");
  canvas_->SetActiveFillColor(color.name().toStdString());
  setcolor_8_appearance();
  ui_->pushButton_8->setStyleSheet("background-color: " + color.name() +
                                   "; border: 1px solid black;");
}

// Parses hex color from the input field and applies it to Stroke
void MainWindow::ApplyStrokeColorFromLineEdit() {
  QString text = ui_->lineEdit_2->text().trimmed();
  if (!text.startsWith("#")) {
    text = "#" + text;
  }
  QColor color(text);
  if (!color.isValid()) {
    ui_->lineEdit_2->setStyleSheet("border: 2px solid red;");
    return;
  }
  ui_->lineEdit_2->setStyleSheet("");
  canvas_->SetActiveStrokeColor(color.name().toStdString());
  ui_->pushButton_9->setStyleSheet("background-color: " + color.name() +
                                   "; border: 1px solid black;");
  setcolor_9_appearance();
}

// Opens a dialog to pick a custom Fill color
void MainWindow::ChooseFillColor() {
  QColor color = QColorDialog::getColor(Qt::white, this, "Choose Fill Color");

  if (!color.isValid()) return;
  canvas_->SetActiveFillColor(color.name().toStdString());
  setcolor_8_appearance();
}

// Opens a dialog to pick a custom Stroke color
void MainWindow::ChooseStrokeColor() {
  QColor color = QColorDialog::getColor(Qt::black, this, "Choose Stroke Color");

  if (!color.isValid()) return;
  canvas_->SetActiveStrokeColor(color.name().toStdString());
  setcolor_9_appearance();
}