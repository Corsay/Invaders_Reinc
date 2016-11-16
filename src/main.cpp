#include <iostream>
#include "gameclasses/space.hpp"

#include <QApplication>
#include <QMainWindow>
#include <QSurfaceFormat>
#include "main_window.hpp"

#include <QTranslator>

using namespace std;

int main(int argc, char ** argv)
{
  try
  {
    QApplication a(argc, argv);

    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);
    QSurfaceFormat::setDefaultFormat(format);

    //QTranslator myTranslator;
    //myTranslator.load("data/localization/" + QLocale::system().name());
    //a.installTranslator(&myTranslator);

    MainWindow mw;
    mw.show();
    return a.exec();
  }
  catch (...)
  {
    std:cerr << "Unknown error!";
  }
  return 0;
}
