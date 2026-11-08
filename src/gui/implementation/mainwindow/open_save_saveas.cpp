#include <QCloseEvent>

#include "../../headers/mainwindow.h"

// Window close (X) button: close only if saved or discarded, else stay open
void MainWindow::closeEvent(QCloseEvent *event) {
  if (MaybeSave()) {
    event->accept();
  } else {
    event->ignore();
  }
}

// Returns true if safe to proceed (saved or discarded), false to cancel
bool MainWindow::MaybeSave() {
  // No prompt if nothing changed since the last save/open/new
  if (canvas_->ExportSvg() == saved_svg_) return true;

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
  return true;
}

// Saves to a new file
bool MainWindow::SaveAs() {
  QString file =
      QFileDialog::getSaveFileName(this, "Save As", "", "SVG Files (*.svg)");

  if (file.isEmpty()) return false;

  std::ofstream out(file.toStdString());
  out << canvas_->ExportSvg(true);  // File gets a viewBox fitting all objects
  out.close();
  if (!out) {  // Could not open or write (permissions, disk full, ...)
    QMessageBox::warning(this, "Save failed", "Could not write to " + file);
    return false;
  }
  saved_svg_ = canvas_->ExportSvg();
  current_file_ = file;
  return true;
}

// Saves the diagram
bool MainWindow::Save() {
  if (current_file_.isEmpty()) {
    return SaveAs();
  }

  std::ofstream out(current_file_.toStdString());
  out << canvas_->ExportSvg(true);  // File gets a viewBox fitting all objects
  out.close();
  if (!out) {  // Could not open or write (permissions, disk full, ...)
    QMessageBox::warning(this, "Save failed",
                         "Could not write to " + current_file_);
    return false;
  }
  saved_svg_ = canvas_->ExportSvg();
  return true;
}

// Opens an SVG file
void MainWindow::Open() {
  if (MaybeSave()) {
    QString file =
        QFileDialog::getOpenFileName(this, "Open", "", "SVG Files (*.svg)");

    if (!file.isEmpty()) {
      std::ifstream in(file.toStdString());
      if (!in) {  // Keep the current drawing if the file can't be read
        QMessageBox::warning(this, "Open failed", "Could not read " + file);
        return;
      }
      std::stringstream buffer;
      buffer << in.rdbuf();

      diagram_.Clear();
      canvas_->ImportSvg(buffer.str());
      canvas_->UndoRedoReset();
      current_file_ = file;
      saved_svg_ = canvas_->ExportSvg();
      canvas_->FitToContent();  // Drawing may be anywhere on the canvas
      canvas_->update();
    }
  }
}

// Closes the document
void MainWindow::Close() {
  if (MaybeSave()) {
    diagram_.Clear();
    canvas_->ResetInteraction();  // Selection pointed into the cleared diagram
    canvas_->UndoRedoReset();
    canvas_->update();
    current_file_.clear();
    saved_svg_ = canvas_->ExportSvg();
    canvas_->ResetView();  // Start at 100% zoom at the origin
  }
}

// Creates a new document
void MainWindow::New() {
  if (MaybeSave()) {
    diagram_.Clear();
    canvas_->ResetInteraction();  // Selection pointed into the cleared diagram
    canvas_->UndoRedoReset();
    canvas_->update();
    current_file_.clear();
    saved_svg_ = canvas_->ExportSvg();
    canvas_->ResetView();  // Start at 100% zoom at the origin
  }
}
