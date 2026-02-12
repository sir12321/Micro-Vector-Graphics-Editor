#include "../../headers/mainwindow.h"

void MainWindow::ToggleTool(Tool tool, QAction* action) {
  if (active_tool_ == tool) {
    // Deactivate
    active_tool_ = Tool::None;
    action->setChecked(false);
  } else {
    // Activate new tool
    active_tool_ = tool;

    // Uncheck all tools
    ui_->actionRectangle->setChecked(false);
    ui_->actionCircle->setChecked(false);
    ui_->actionLine->setChecked(false);
    ui_->actionHexagon->setChecked(false);
    ui_->actionRoundedRectangle->setChecked(false);
    ui_->actionFreehand->setChecked(false);
    ui_->actionText->setChecked(false);
    ui_->actionFill->setChecked(false);
    ui_->actionStrokeFill->setChecked(false);

    // Check selected tool
    action->setChecked(true);
  }

  canvas_->SetActiveTool(active_tool_);
}