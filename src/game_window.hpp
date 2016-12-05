#pragma once

#include <QMainWindow>
#include <QTimer>
#include <QGridLayout>
#include <QOpenGLWidget>
#include <QStackedWidget>

#include "window_constants.hpp"
#include "game_widget.hpp"
#include "main_window.hpp"
#include "gameclasses/space.hpp"

class GameGLWidget;
class MainWindow;

class GameWindow : public QMainWindow
{
  Q_OBJECT

public:
  GameWindow(QStackedWidget * w, MainWindow* wnd);

  void NewGame();

  void DeleteSpace();
  void SetVolume();

  void SetKey(KeyTypes type, QKeySequence key);

  Space2D* GetSpace();
  QStackedWidget * m_stackedWidget = nullptr;
  MainWindow * m_mainWindow = nullptr;
private:
  QTimer * m_timer = nullptr;
  QGridLayout * m_layout = nullptr;
  GameGLWidget * m_glWidget = nullptr;
};
