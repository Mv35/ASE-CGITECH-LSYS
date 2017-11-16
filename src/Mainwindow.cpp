#include "MainWindow.h"
#include "ui_MainWindow.h"


MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent), m_ui(new Ui::MainWindow)
{
  m_ui->setupUi(this);
  // create an openGL format and pass to the new GLWidget
  QGLFormat format;
  format.setVersion(3,2);
  format.setProfile( QGLFormat::CoreProfile);

  m_gl = new NGLWidget(format,this);

  // Creating the main render window
  m_ui->gridLayout->addWidget(m_gl,0,0,4,1);
}

MainWindow::~MainWindow()
{
  //delete m_ui;
}
