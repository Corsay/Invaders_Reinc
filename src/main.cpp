#include <iostream>
#include <QApplication>
#include <QMainWindow>
#include <QSurfaceFormat>
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
    QStackedWidget * w = new QStackedWidget;
    GameWindow mw(w);
    mw.show();

    return app.exec();
  }
  catch (...)
  {
    std::cerr << "Unknown error!";
  }
  return 0;
}
