#include <iostream>
#include <string>
#include <QApplication>
#include "MainWindow.h"
#include "LSys.h"
#include "LSys0L.h"
#include "LSysExtFactory.h"
#include "LSysParser.h"
#include "LSysStructForFile.h"
#include "Turtle.h"
#include <QSurfaceFormat>

int main(int argc, char **argv)
{
  QApplication app(argc, argv);
  QSurfaceFormat format;
  format.setMajorVersion(4);
  format.setMinorVersion(1);
  format.setProfile(QSurfaceFormat::OpenGLContextProfile::CoreProfile);
  QSurfaceFormat::setDefaultFormat(format);

  MainWindow w;
  w.show();
  return app.exec();
}



