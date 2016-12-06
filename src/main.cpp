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

    QFontDatabase::addApplicationFont("data/fonts/DS Hiline.ttf");
    QFontDatabase::addApplicationFont("data/fonts/Epson1.ttf");

    MainWindow mw;
    mw.show();

    return app.exec();
  }
  catch (NoTextureException const & exc)
  {
    QApplication app(argc, argv);

    QPushButton * errorButton = new QPushButton(exc.what());
    QObject::connect(errorButton, &QAbstractButton::clicked, [errorButton]()
    {
      errorButton->close();
    });
    errorButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    errorButton->resize(400,300);
    // move to center
    QRect frect = errorButton->frameGeometry();
    frect.moveCenter(QDesktopWidget().availableGeometry().center());
    errorButton->move(frect.topLeft());
    errorButton->show();

    logger << exc.what() <<  std::endl;

    return app.exec();
  }
  catch (...)
  {
    logger << "Unknown error!";
  }
  return 0;
}
