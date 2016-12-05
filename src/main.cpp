#include <iostream>
#include <QApplication>
#include <QMainWindow>
#include <QSurfaceFormat>
#include <QFontDatabase>
#include "main_window.hpp"

int main(int argc, char ** argv)
{
  try
  {
    QApplication app(argc, argv);

    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);
    QSurfaceFormat::setDefaultFormat(format);

    QFontDatabase::addApplicationFont("data/fonts/Epson1.ttf");

    MainWindow mw;
    mw.show();

    return app.exec();
  }
  catch (...)
  {
    logger << "Unknown error!";
  }
  return 0;
}
