#include <QColorDialog>
#include <QVBoxLayout>

#include "../../headers/canvas.h"
#include "../../headers/mainwindow.h"
#include "../ui_mainwindow.h"

// Sets up the initial UI state.
void MainWindow::initialise() {
  QString defaultFill_1 = "#00000000";  // transparent
  QString defaultFill_2 = "#00000000";  // transparent
  QString defaultFill_8 = "#ffffff";    // white
  QString defaultFill_9 = "#000000";    // black

  QString defaultFill_33 = "#ffffff";  // white
  QString defaultFill_34 = "#ff0000";  // red
  QString defaultFill_35 = "#ffa500";  // orange
  QString defaultFill_36 = "#ffff00";  // yellow
  QString defaultFill_37 = "#90ee90";  // light-green
  QString defaultFill_38 = "#008000";  // green
  QString defaultFill_39 = "#000000";  // black
  QString defaultFill_40 = "#808080";  // grey
  QString defaultFill_41 = "#00008b";  // dark-blue
  QString defaultFill_42 = "#87ceeb";  // sky-blue
  QString defaultFill_43 = "#800080";  // purple
  QString defaultFill_44 = "#a52a2a";  // brown

  QString defaultFill_57 = "#ffffff";  // white
  QString defaultFill_58 = "#ff0000";  // red
  QString defaultFill_59 = "#ffa500";  // orange
  QString defaultFill_60 = "#ffff00";  // yellow
  QString defaultFill_61 = "#90ee90";  // lightgreen
  QString defaultFill_62 = "#008000";  // green
  QString defaultFill_45 = "#000000";  // black
  QString defaultFill_46 = "#808080";  // grey
  QString defaultFill_47 = "#00008b";  // dark-blue
  QString defaultFill_48 = "#87ceeb";  // sky-blue
  QString defaultFill_49 = "#800080";  // purple
  QString defaultFill_50 = "#a52a2a";  // brown

  int defaultStrokeWidth = 2;

  ui_->pushButton_1->setStyleSheet("background-color: " + defaultFill_1 + ";" +
                                   "border: 1px solid black;");
  ui_->pushButton_2->setStyleSheet("background-color: " + defaultFill_2 + ";" +
                                   "border: 1px solid black;");
  ui_->pushButton_8->setStyleSheet("background-color: " + defaultFill_8 + ";" +
                                   "border: 1px solid black;");
  ui_->pushButton_33->setStyleSheet("background-color: " + defaultFill_33 +
                                    ";" + "border: 1px solid black;");
  ui_->pushButton_34->setStyleSheet("background-color: " + defaultFill_34 +
                                    ";" + "border: 1px solid black;");
  ui_->pushButton_35->setStyleSheet("background-color: " + defaultFill_35 +
                                    ";" + "border: 1px solid black;");
  ui_->pushButton_36->setStyleSheet("background-color: " + defaultFill_36 +
                                    ";" + "border: 1px solid black;");
  ui_->pushButton_37->setStyleSheet("background-color: " + defaultFill_37 +
                                    ";" + "border: 1px solid black;");
  ui_->pushButton_38->setStyleSheet("background-color: " + defaultFill_38 +
                                    ";" + "border: 1px solid black;");
  ui_->pushButton_39->setStyleSheet("background-color: " + defaultFill_39 +
                                    ";" + "border: 1px solid black;");
  ui_->pushButton_40->setStyleSheet("background-color: " + defaultFill_40 +
                                    ";" + "border: 1px solid black;");
  ui_->pushButton_41->setStyleSheet("background-color: " + defaultFill_41 +
                                    ";" + "border: 1px solid black;");
  ui_->pushButton_42->setStyleSheet("background-color: " + defaultFill_42 +
                                    ";" + "border: 1px solid black;");
  ui_->pushButton_43->setStyleSheet("background-color: " + defaultFill_43 +
                                    ";" + "border: 1px solid black;");
  ui_->pushButton_44->setStyleSheet("background-color: " + defaultFill_44 +
                                    ";" + "border: 1px solid black;");
  ui_->pushButton_57->setStyleSheet("background-color: " + defaultFill_57 +
                                    ";" + "border: 1px solid black;");
  ui_->pushButton_58->setStyleSheet("background-color: " + defaultFill_58 +
                                    ";" + "border: 1px solid black;");
  ui_->pushButton_59->setStyleSheet("background-color: " + defaultFill_59 +
                                    ";" + "border: 1px solid black;");
  ui_->pushButton_60->setStyleSheet("background-color: " + defaultFill_60 +
                                    ";" + "border: 1px solid black;");
  ui_->pushButton_61->setStyleSheet("background-color: " + defaultFill_61 +
                                    ";" + "border: 1px solid black;");
  ui_->pushButton_62->setStyleSheet("background-color: " + defaultFill_62 +
                                    ";" + "border: 1px solid black;");
  ui_->pushButton_45->setStyleSheet("background-color: " + defaultFill_45 +
                                    ";" + "border: 1px solid black;");
  ui_->pushButton_46->setStyleSheet("background-color: " + defaultFill_46 +
                                    ";" + "border: 1px solid black;");
  ui_->pushButton_47->setStyleSheet("background-color: " + defaultFill_47 +
                                    ";" + "border: 1px solid black;");
  ui_->pushButton_48->setStyleSheet("background-color: " + defaultFill_48 +
                                    ";" + "border: 1px solid black;");
  ui_->pushButton_49->setStyleSheet("background-color: " + defaultFill_49 +
                                    ";" + "border: 1px solid black;");
  ui_->pushButton_50->setStyleSheet("background-color: " + defaultFill_50 +
                                    ";" + "border: 1px solid black;");
  ui_->pushButton_9->setStyleSheet("background-color: " + defaultFill_9 + ";");
  ui_->lineEdit->setPlaceholderText("#ffffff");
  ui_->lineEdit_2->setPlaceholderText("#000000");
  ui_->label_4->setText(QString::number(defaultStrokeWidth));
  ui_->rrRadiusSpinBox->setValue(canvas_->GetRoundedRectRadius());
  ui_->fontSizeSpinBox->setValue(canvas_->GetTextFontSize());
  ui_->widget_4->setStyleSheet(
      "QWidget#widget_4 {"
      "  background-color: #f4f4f4;"
      "  border-top: 1px solid #cfcfcf;"
      "}");
  ui_->widget_9->setStyleSheet(
      "QWidget#widget_9 {"
      "  background-color: #f5f5f5;"
      "  border-top: 1px solid #cfcfcf;"
      "}");
  ui_->widget_13->setStyleSheet(
      "QWidget#widget_13 {"
      "  background-color: #f5f5f5;"
      "  border-top: 1px solid #cfcfcf;"
      "}");
  ui_->widget_15->setStyleSheet(
      "QWidget#widget_15 {"
      "  background-color: #f5f5f5;"
      "  border-top: 1px solid #cfcfcf;"
      "}");
  ui_->widget_16->setStyleSheet(
      "QWidget#widget_16 {"
      "  background-color: #f4f4f4;"
      "  border-top: 1px solid #cfcfcf;"
      "}");
  ui_->label_4->setStyleSheet(
      "QWidget#label_4 {"
      "  background-color: #ffffff;"
      "  border-top: 1px solid #cfcfcf;"
      "}");
  ui_->label_5->setStyleSheet(
      "QWidget#label_5 {"
      "  background-color: #f4f4f4;"
      "  border-top: 1px solid #cfcfcf;"
      "}");
  ui_->label_6->setStyleSheet(
      "QWidget#label_6 {"
      "  background-color: #f4f4f4;"
      "  border-top: 1px solid #cfcfcf;"
      "}");
  ui_->label_7->setStyleSheet(
      "QWidget#label_7 {"
      "  background-color: #f4f4f4;"
      "  border-top: 1px solid #cfcfcf;"
      "}");
  ui_->Properties->setStyleSheet(
      "QDockWidget {"
      "   background-color: #f4f4f4;"
      "   border-top: 5px solid #aaaaaa;"
      "}"
      "QDockWidget::close-button, QDockWidget::float-button {"
      "   background-color: transparent;"
      "   border: none;"
      "}");
  ui_->canvas_container->setStyleSheet(
      "QWidget#canvas_container {"
      "   border: 1px solid #cfcfcf;"
      "   background-color: white;"
      "}");
}
