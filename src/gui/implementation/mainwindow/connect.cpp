// Wiring of UI signals to slots in the MainWindow.

#include "../../headers/canvas.h"
#include "../../headers/mainwindow.h"
#include "../ui_mainwindow.h"

// Connects all Qt signals from the UI elements to their respective
// slots.
void MainWindow::connectSignals() {
  // ---- Connect all tools ----
  connect(ui_->pushButton_8, &QPushButton::clicked, this,
          &MainWindow::ChooseFillColor);
  connect(ui_->pushButton_9, &QPushButton::clicked, this,
          &MainWindow::ChooseStrokeColor);
  connect(ui_->lineEdit, &QLineEdit::returnPressed, this,
          &MainWindow::ApplyFillColorFromLineEdit);
  connect(ui_->lineEdit_2, &QLineEdit::returnPressed, this,
          &MainWindow::ApplyStrokeColorFromLineEdit);
  connect(ui_->pushButton_1, &QPushButton::clicked, this,
          &MainWindow::setfillcolortransparent);
  connect(ui_->pushButton_2, &QPushButton::clicked, this,
          &MainWindow::setstrokecolortransparent);
  connect(ui_->pushButton_33, &QPushButton::clicked, this,
          &MainWindow::setfillcolorwhite);
  connect(ui_->pushButton_34, &QPushButton::clicked, this,
          &MainWindow::setfillcolorred);
  connect(ui_->pushButton_35, &QPushButton::clicked, this,
          &MainWindow::setfillcolororange);
  connect(ui_->pushButton_36, &QPushButton::clicked, this,
          &MainWindow::setfillcoloryellow);
  connect(ui_->pushButton_37, &QPushButton::clicked, this,
          &MainWindow::setfillcolorlightgreen);
  connect(ui_->pushButton_38, &QPushButton::clicked, this,
          &MainWindow::setfillcolorgreen);
  connect(ui_->pushButton_39, &QPushButton::clicked, this,
          &MainWindow::setfillcolorblack);
  connect(ui_->pushButton_40, &QPushButton::clicked, this,
          &MainWindow::setfillcolorgrey);
  connect(ui_->pushButton_41, &QPushButton::clicked, this,
          &MainWindow::setfillcolordarkblue);
  connect(ui_->pushButton_42, &QPushButton::clicked, this,
          &MainWindow::setfillcolorskyblue);
  connect(ui_->pushButton_43, &QPushButton::clicked, this,
          &MainWindow::setfillcolorpurple);
  connect(ui_->pushButton_44, &QPushButton::clicked, this,
          &MainWindow::setfillcolorbrown);
  connect(ui_->pushButton_57, &QPushButton::clicked, this,
          &MainWindow::setstrokecolorwhite);
  connect(ui_->pushButton_58, &QPushButton::clicked, this,
          &MainWindow::setstrokecolorred);
  connect(ui_->pushButton_59, &QPushButton::clicked, this,
          &MainWindow::setstrokecolororange);
  connect(ui_->pushButton_60, &QPushButton::clicked, this,
          &MainWindow::setstrokecoloryellow);
  connect(ui_->pushButton_61, &QPushButton::clicked, this,
          &MainWindow::setstrokecolorlightgreen);
  connect(ui_->pushButton_62, &QPushButton::clicked, this,
          &MainWindow::setstrokecolorgreen);
  connect(ui_->pushButton_45, &QPushButton::clicked, this,
          &MainWindow::setstrokecolorblack);
  connect(ui_->pushButton_46, &QPushButton::clicked, this,
          &MainWindow::setstrokecolorgrey);
  connect(ui_->pushButton_47, &QPushButton::clicked, this,
          &MainWindow::setstrokecolordarkblue);
  connect(ui_->pushButton_48, &QPushButton::clicked, this,
          &MainWindow::setstrokecolorskyblue);
  connect(ui_->pushButton_49, &QPushButton::clicked, this,
          &MainWindow::setstrokecolorpurple);
  connect(ui_->pushButton_50, &QPushButton::clicked, this,
          &MainWindow::setstrokecolorbrown);
  connect(ui_->horizontalSlider, &QSlider::valueChanged, this,
          [this](int value) {
            canvas_->SetActiveStrokeWidth(value);
            ui_->label_4->setText(QString::number(value));
          });
  connect(ui_->fontComboBox, &QFontComboBox::currentFontChanged, this,
          &MainWindow::ApplyFontFromComboBox);
  connect(ui_->actionRectangle, &QAction::triggered, this,
          [this]() { ToggleTool(Tool::Rectangle, ui_->actionRectangle); });
  connect(ui_->actionRoundedRectangle, &QAction::triggered, this, [this]() {
    ToggleTool(Tool::RoundedRectangle, ui_->actionRoundedRectangle);
  });
  connect(ui_->actionCircle, &QAction::triggered, this,
          [this]() { ToggleTool(Tool::Circle, ui_->actionCircle); });
  connect(ui_->actionLine, &QAction::triggered, this,
          [this]() { ToggleTool(Tool::Line, ui_->actionLine); });
  connect(ui_->actionHexagon, &QAction::triggered, this,
          [this]() { ToggleTool(Tool::Hexagon, ui_->actionHexagon); });
  connect(ui_->actionFreehand, &QAction::triggered, this,
          [this]() { ToggleTool(Tool::Freehand, ui_->actionFreehand); });
  connect(ui_->actionText, &QAction::triggered, this,
          [this]() { ToggleTool(Tool::Text, ui_->actionText); });
  connect(ui_->rrRadiusSpinBox,
          QOverload<double>::of(&QDoubleSpinBox::valueChanged), this,
          [this](double value) { canvas_->SetRoundedRectRadius(value); });
  connect(ui_->fontSizeSpinBox, QOverload<int>::of(&QSpinBox::valueChanged),
          this, [this](int value) { canvas_->SetTextFontSize(value); });
  connect(ui_->actionFill, &QAction::triggered, this,
          [this]() { ToggleTool(Tool::Fill, ui_->actionFill); });
  connect(ui_->actionStrokeFill, &QAction::triggered, this,
          [this]() { ToggleTool(Tool::StrokeFill, ui_->actionStrokeFill); });
  connect(ui_->checkBox, &QCheckBox::stateChanged, this, [this](int state) {
    if (state == Qt::Checked) {
      canvas_->edit_font_ = true;
    } else {
      canvas_->edit_font_ = false;
    }
  });

  connect(ui_->actionCopy, &QAction::triggered, canvas_, &Canvas::CopySelected);
  connect(ui_->actionCut, &QAction::triggered, canvas_, &Canvas::CutSelected);
  connect(ui_->actionPaste, &QAction::triggered, canvas_, &Canvas::Paste);
  connect(ui_->actionNew, &QAction::triggered, this, &MainWindow::New);
  connect(ui_->actionOpen, &QAction::triggered, this, &MainWindow::Open);
  connect(ui_->actionSave, &QAction::triggered, this, &MainWindow::Save);
  connect(ui_->actionSave_As, &QAction::triggered, this, &MainWindow::SaveAs);
  connect(ui_->actionClose, &QAction::triggered, this, &MainWindow::Close);
  connect(ui_->actionUndo, &QAction::triggered, canvas_, &Canvas::Undo);
  connect(ui_->actionRedo, &QAction::triggered, canvas_, &Canvas::Redo);
}