// Implementation of file operations (Open, Save, Save As) for the
// application.

#include <QFileDialog>
#include <QMessageBox>
#include <fstream>
#include <sstream>

#include "../../headers/canvas.h"
#include "../../headers/mainwindow.h"
#include "../ui_mainwindow.h"

// Helper to ask the user if they want to save changes.
// Returns true if the user chooses Save (and save succeeds), Discard, or if
// there are no changes. false if the user chooses Cancel or if the save fails.
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

// Prompts the user to choose a file path and saves the diagram as SVG.
//
// Updates the current file path upon success.
// Returns True if saved successfully, False otherwise or cancelled.
bool MainWindow::SaveAs() {
  QString file =
      QFileDialog::getSaveFileName(this, "Save As", "", "SVG Files (*.svg)");

  if (file.isEmpty()) return false;

  std::ofstream out(file.toStdString());
  out << canvas_->ExportSvg();
  current_file_ = file;
  return true;
}

// Saves the current diagram to the active file path.
//
// If no file path is set (i.e., new file), it triggers SaveAs().
// Returns True if saved successfully, False if cancelled.
bool MainWindow::Save() {
  if (current_file_.isEmpty()) {
    return SaveAs();
  }

  std::ofstream out(current_file_.toStdString());
  out << canvas_->ExportSvg();
  return true;
}

// Opens an existing SVG file and loads it into the canvas.
//
// Prompts the user to select a file. Replaces the current canvas content.
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

// Closes the current document.
//
// Checks for unsaved changes before clearing.
void MainWindow::Close() {
  if (MaybeSave()) {
    diagram_.Clear();
    canvas_->UndoRedoReset();
    canvas_->update();
    current_file_.clear();
  }
}

// Creates a new document.
//
// Checks for unsaved changes before clearing.
void MainWindow::New() {
  if (MaybeSave()) {
    diagram_.Clear();
    canvas_->UndoRedoReset();
    canvas_->update();
    current_file_.clear();
  }
}
