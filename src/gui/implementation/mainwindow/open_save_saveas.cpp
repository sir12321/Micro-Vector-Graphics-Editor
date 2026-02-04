#include <QFileDialog>
#include <QMessageBox>
#include <fstream>
#include <sstream>

#include "../../headers/canvas.h"
#include "../../headers/mainwindow.h"
#include "../ui_mainwindow.h"

// Returns true if safe to proceed (saved or discarded), false to cancel.
bool MainWindow::MaybeSave() {
  QMessageBox::StandardButton ret;
  ret = QMessageBox::warning(
      this, "Application",
      "The document may have unsaved changes.\n"
      "Do you want to save your changes?",
      QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);

  if (ret == QMessageBox::Save) {
    return Save();
  } else if (ret == QMessageBox::Cancel) {
    return false;
  }
  return true;  // Discard
}

// Saves to a new file.
bool MainWindow::SaveAs() {
  QString file =
      QFileDialog::getSaveFileName(this, "Save As", "", "SVG Files (*.svg)");

  if (file.isEmpty()) return false;

  std::ofstream out(file.toStdString());
  out << canvas_->ExportSvg();
  current_file_ = file;
  return true;
}

// Saves the diagram.
bool MainWindow::Save() {
  if (current_file_.isEmpty()) {
    return SaveAs();
  }

  std::ofstream out(current_file_.toStdString());
  out << canvas_->ExportSvg();
  return true;
}

// Opens an SVG file.
void MainWindow::Open() {
  if (MaybeSave()) {
    QString file =
        QFileDialog::getOpenFileName(this, "Open", "", "SVG Files (*.svg)");

    if (!file.isEmpty()) {
      std::ifstream in(file.toStdString());
      std::stringstream buffer;
      buffer << in.rdbuf();

      diagram_.Clear();
      canvas_->ImportSvg(buffer.str());
      canvas_->UndoRedoReset();
      current_file_ = file;
      canvas_->update();
    }
  }
}

// Closes the document.
void MainWindow::Close() {
  if (MaybeSave()) {
    diagram_.Clear();
    canvas_->UndoRedoReset();
    canvas_->update();
    current_file_.clear();
  }
}

// Creates a new document.
void MainWindow::New() {
  if (MaybeSave()) {
    diagram_.Clear();
    canvas_->UndoRedoReset();
    canvas_->update();
    current_file_.clear();
  }
}
