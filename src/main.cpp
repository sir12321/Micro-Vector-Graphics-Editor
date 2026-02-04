// Entry point for the application.

#include <QApplication>

#include "gui/headers/mainwindow.h"

// Main function.
//
// Initializes the Qt application and shows the main window.
int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  MainWindow window;
  window.show();

  return app.exec();
}
