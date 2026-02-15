#include "../../headers/mainwindow.h"

void MainWindow::initialise() {
  int defaultStrokeWidth = 2;

  ui_->pushButton_1->setStyleSheet(
      "background-color: #00000000;border: 1px solid black;");
  ui_->pushButton_2->setStyleSheet(
      "background-color: #00000000;border: 1px solid black;");
  ui_->pushButton_8->setStyleSheet(
      "background-color: #ffffff;border: 1px solid black;");
  ui_->pushButton_33->setStyleSheet(
      "background-color: #ffffff;border: 1px solid black;");
  ui_->pushButton_34->setStyleSheet(
      "background-color: #ff0000;border: 1px solid black;");
  ui_->pushButton_35->setStyleSheet(
      "background-color: #ffa500;border: 1px solid black;");
  ui_->pushButton_36->setStyleSheet(
      "background-color: #ffff00;border: 1px solid black;");
  ui_->pushButton_37->setStyleSheet(
      "background-color: #90ee90;border: 1px solid black;");
  ui_->pushButton_38->setStyleSheet(
      "background-color: #008000;border: 1px solid black;");
  ui_->pushButton_39->setStyleSheet(
      "background-color: #000000;border: 1px solid black;");
  ui_->pushButton_40->setStyleSheet(
      "background-color: #808080;border: 1px solid black;");
  ui_->pushButton_41->setStyleSheet(
      "background-color: #00008b;border: 1px solid black;");
  ui_->pushButton_42->setStyleSheet(
      "background-color: #87ceeb;border: 1px solid black;");
  ui_->pushButton_43->setStyleSheet(
      "background-color: #800080;border: 1px solid black;");
  ui_->pushButton_44->setStyleSheet(
      "background-color: #a52a2a;border: 1px solid black;");
  ui_->pushButton_57->setStyleSheet(
      "background-color: #ffffff;border: 1px solid black;");
  ui_->pushButton_58->setStyleSheet(
      "background-color: #ff0000;border: 1px solid black;");
  ui_->pushButton_59->setStyleSheet(
      "background-color: #ffa500;border: 1px solid black;");
  ui_->pushButton_60->setStyleSheet(
      "background-color: #ffff00;border: 1px solid black;");
  ui_->pushButton_61->setStyleSheet(
      "background-color: #90ee90;border: 1px solid black;");
  ui_->pushButton_62->setStyleSheet(
      "background-color: #008000;border: 1px solid black;");
  ui_->pushButton_45->setStyleSheet(
      "background-color: #000000;border: 1px solid black;");
  ui_->pushButton_46->setStyleSheet(
      "background-color: #808080;border: 1px solid black;");
  ui_->pushButton_47->setStyleSheet(
      "background-color: #00008b;border: 1px solid black;");
  ui_->pushButton_48->setStyleSheet(
      "background-color: #87ceeb;border: 1px solid black;");
  ui_->pushButton_49->setStyleSheet(
      "background-color: #800080;border: 1px solid black;");
  ui_->pushButton_50->setStyleSheet(
      "background-color: #a52a2a;border: 1px solid black;");
  ui_->pushButton_9->setStyleSheet("background-color: #000000;");
  ui_->lineEdit->setPlaceholderText("#ffffff");
  ui_->lineEdit_2->setPlaceholderText("#000000");
  ui_->label_4->setText(QString::number(defaultStrokeWidth));
  ui_->rrRadiusSpinBox->setValue(canvas_->GetRoundedRectRadius());
  ui_->fontSizeSpinBox->setValue(canvas_->GetTextFontSize());
  ui_->widget_4->setStyleSheet(
      "QWidget#widget_4 {  background-color: #f4f4f4;  border-top: 1px solid "
      "#cfcfcf}");
  ui_->widget_9->setStyleSheet(
      "QWidget#widget_9 {  background-color: #f5f5f5;  border-top: 1px solid "
      "#cfcfcf;}");
  ui_->widget_13->setStyleSheet(
      "QWidget#widget_13 {  background-color: #f5f5f5;  border-top: 1px solid "
      "#cfcfcf}");
  ui_->widget_15->setStyleSheet(
      "QWidget#widget_15 {  background-color: #f5f5f5;  border-top: 1px solid "
      "#cfcfcf;}");
  ui_->widget_16->setStyleSheet(
      "QWidget#widget_16 {  background-color: #f4f4f4;  border-top: 1px solid "
      "#cfcfcf;}");
  ui_->label_4->setStyleSheet(
      "QWidget#label_4 {  background-color: #ffffff;  border-top: 1px solid "
      "#cfcfcf;}");
  ui_->label_5->setStyleSheet(
      "QWidget#label_5 {  background-color: #f4f4f4;  border-top: 1px solid "
      "#cfcfcf;}");
  ui_->label_6->setStyleSheet(
      "QWidget#label_6 {  background-color: #f4f4f4;  border-top: 1px solid "
      "#cfcfcf;}");
  ui_->label_7->setStyleSheet(
      "QWidget#label_7 {  background-color: #f4f4f4;  border-top: 1px solid "
      "#cfcfcf;}");
  ui_->Properties->setStyleSheet(
      "QDockWidget {   background-color: #f4f4f4;   border-top: 5px solid "
      "#aaaaaa;}QDockWidget::close-button, QDockWidget::float-button "
      "{background-color: transparent;border: none;}");
  ui_->canvas_container->setStyleSheet(
      "QWidget#canvas_container {   border: 1px solid #cfcfcf;   "
      "background-color: white;}");
}