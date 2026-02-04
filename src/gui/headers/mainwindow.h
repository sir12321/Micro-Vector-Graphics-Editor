#ifndef SRC_GUI_MAINWINDOW_H
#define SRC_GUI_MAINWINDOW_H

#include <QFontComboBox>
#include <QMainWindow>

#include "../../diagram/diagram.h"
#include "canvas.h"
#include "tools.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void initialise();
  void ToggleTool(Tool tool, QAction *action);
  void connectSignals();
  void ApplyFillColorFromLineEdit();
  void ApplyStrokeColorFromLineEdit();
  void ChooseFillColor();
  void setcolor_8_appearance();
  void ChooseStrokeColor();
  void setcolor_9_appearance();
  void setfillcolortransparent();
  void setfillcolorwhite();
  void setfillcolorred();
  void setfillcolororange();
  void setfillcoloryellow();
  void setfillcolorlightgreen();
  void setfillcolorgreen();
  void setfillcolorblack();
  void setfillcolorgrey();
  void setfillcolordarkblue();
  void setfillcolorskyblue();
  void setfillcolorpurple();
  void setfillcolorbrown();
  void setstrokecolortransparent();
  void setstrokecolorwhite();
  void setstrokecolorred();
  void setstrokecolororange();
  void setstrokecoloryellow();
  void setstrokecolorlightgreen();
  void setstrokecolorgreen();
  void setstrokecolorblack();
  void setstrokecolorgrey();
  void setstrokecolordarkblue();
  void setstrokecolorskyblue();
  void setstrokecolorpurple();
  void setstrokecolorbrown();
  void StrokeWidthChanged(int value);
  void ApplyFontFromComboBox();
  void Open();
  bool Save();
  bool SaveAs();
  void Close();
  void New();

 private:
  bool MaybeSave();

  Ui::MainWindow *ui_;
  Diagram diagram_;  // MODEL
  Canvas *canvas_;   // VIEW
  QString current_file_;

  Tool active_tool_;
};

#endif  // SRC_GUI_MAINWINDOW_H
