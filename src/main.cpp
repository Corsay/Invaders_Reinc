#include <iostream>
#include "gameclasses/space.hpp"

#include <QApplication>
#include <QMainWindow>
#include <QSurfaceFormat>
#include "main_window.hpp"
#include "game_window.hpp"

using namespace std;

int main(int argc, char ** argv)
{
  try
  {
    QApplication app(argc, argv);

    QStackedWidget * w = new QStackedWidget;
    MainWindow *wnd = new MainWindow(w);
    GameWindow *gwnd = new GameWindow(w);
    w->addWidget(wnd);
    w->addWidget(gwnd);
    w->setCurrentWidget(wnd);
    w->show();


    return app.exec();
  }
  catch (...)
  {
    std:cerr << "Unknown error!";
  }
  return 0;
}
