#include "game_window.hpp"

#include "game_widget.hpp"
#include <QApplication>
#include <QPalette>

typedef void (QWidget::*QWidgetVoidSlot)();

GameWindow::GameWindow(QStackedWidget * w)
{
  m_stackedWidget = w;
  m_glWidget = new GameGLWidget(this);
  setCentralWidget(m_glWidget);
  m_timer = new QTimer(this);
  m_timer->setInterval(10);
  connect(m_timer, &QTimer::timeout, m_glWidget, static_cast<QWidgetVoidSlot>(&QWidget::update));
}

void GameWindow::NewGame(int gunLives, int countOfAliens, int countOfObstacles)
{
  m_glWidget->NewGame(width(), height(), gunLives, countOfAliens, countOfObstacles);
  m_timer->start();
}

void GameWindow::SetKey(KeyTypes type, QKeySequence key)
{
  m_glWidget->SetKey(type, key);
}
