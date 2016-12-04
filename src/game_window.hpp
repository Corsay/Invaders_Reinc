#pragma once

#include <QMainWindow>
#include <QTimer>
#include <QGridLayout>
#include <QOpenGLWidget>
#include <QStackedWidget>

#include "window_constants.hpp"
#include "game_widget.hpp"

class GameGLWidget;

class GameWindow : public QMainWindow
{
  Q_OBJECT

public:
  GameWindow(QStackedWidget * w);

  void NewGame();

  void DeleteSpace();
  void SetVolume();

  void SetKey(KeyTypes type, QKeySequence key);

  QStackedWidget * m_stackedWidget = nullptr;
private:
  QTimer * m_timer = nullptr;
  QGridLayout * m_layout = nullptr;
  GameGLWidget * m_glWidget = nullptr;
};
