#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <memory>
#include <QMainWindow>
#include "NGLWidget.h"
#include <QKeyEvent>
///@file MainWindow.h
/// @brief My program's main window


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();



private:
  //Ui::MainWindow *m_ui;
  std::unique_ptr<Ui::MainWindow> m_ui;
  NGLWidget *m_gl;
  void keyPressEvent(QKeyEvent *_event);

public slots :
  //void toggleWireframe();
  void getLParametersFromSystem();
  void saveParametersToFile();
};

#endif // MAINWINDOW_H
