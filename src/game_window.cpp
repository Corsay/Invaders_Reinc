#include "game_window.hpp"

#include <QApplication>
#include "game_widget.hpp"
#include <QPalette>

typedef void (QWidget::*QWidgetVoidSlot)();

GameWindow::GameWindow(QStackedWidget *w)
{
  m_stackedWidget = w;
  m_glWidget = new GameGLWidget(this);
  m_timer = new QTimer(this);
  m_timer->setInterval(10);
  setCentralWidget(m_glWidget);
  connect(m_timer, &QTimer::timeout, m_glWidget, static_cast<QWidgetVoidSlot>(&QWidget::update));
  m_timer->start();

  //setFocusPolicy(Qt::StrongFocus);
}
