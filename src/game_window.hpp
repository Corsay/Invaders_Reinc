#pragma once

#include <QMainWindow>
#include <QTimer>
#include <QGridLayout>
#include <QOpenGLWidget>
#include <QStackedWidget>

class GameWindow : public QMainWindow
{
  Q_OBJECT

public:
  GameWindow(QStackedWidget * w);

  QStackedWidget * m_stackedWidget = nullptr;

private:
  QTimer * m_timer = nullptr;
  QGridLayout * m_layout = nullptr;
  QOpenGLWidget * m_glWidget = nullptr;
};
