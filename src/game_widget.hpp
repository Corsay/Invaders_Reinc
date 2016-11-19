#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QTime>
#include "textured_rect.hpp"
#include "game_window.hpp"

#include <array>

class MainWindow;

QT_FORWARD_DECLARE_CLASS(QOpenGLTexture)
QT_FORWARD_DECLARE_CLASS(QOpenGLShader)
QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)

class GameGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
  Q_OBJECT
public:
  GameGLWidget(GameWindow *mw);
  ~GameGLWidget();

protected:
  void resizeGL(int w, int h) override;
  void paintGL() override;
  void initializeGL() override;

  void Update(float elapsedSeconds);
  void Render();

private:
  GameWindow * m_gameWindow;

  unsigned int m_frames = 0;
  QTime m_time;
  QSize m_screenSize;

  std::vector<QOpenGLTexture*> m_starTexture;
  QOpenGLTexture * m_backgroundPicture = nullptr;
  TexturedRect * m_texturedRect = nullptr;

  QVector2D m_position = QVector2D(200, 200);
  bool m_directions[4] = { false, false, false, false };
};
