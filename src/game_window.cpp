#include "game_window.hpp"

#include "game_widget.hpp"
#include <QApplication>
#include <QPalette>

typedef void (QWidget::*QWidgetVoidSlot)();

GameWindow::GameWindow(QStackedWidget * w, MainWindow* wnd)
{
  m_mainWindow = wnd;
  m_stackedWidget = w;
  m_glWidget = new GameGLWidget(this);
  setCentralWidget(m_glWidget);
  m_timer = new QTimer(this);
  m_timer->setInterval(10);
  connect(m_timer, &QTimer::timeout, m_glWidget, static_cast<QWidgetVoidSlot>(&QWidget::update));
}

void GameWindow::NewGame()
{
  m_glWidget->NewGame(width(), height());
  m_timer->start();
}

void GameWindow::DeleteSpace()
{
  m_glWidget->DeleteSpace();
}

void GameWindow::SetVolume()
{
  m_glWidget->SetVolume();
}

void GameWindow::SetKey(KeyTypes type, QKeySequence key)
{
  m_glWidget->SetKey(type, key);
}
Space2D* GameWindow::GetSpace(){ return m_glWidget->GetSpace(); }
