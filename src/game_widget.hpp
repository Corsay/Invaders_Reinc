#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QTime>
#include <array>

#include "textured_rect.hpp"
#include "game_window.hpp"
#include "gameclasses/space.hpp"

class GameWindow;

QT_FORWARD_DECLARE_CLASS(QOpenGLTexture)
QT_FORWARD_DECLARE_CLASS(QOpenGLShader)
QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)

class GameGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
  Q_OBJECT
public:
  GameGLWidget(GameWindow * mw);
  ~GameGLWidget();

  void ChangeSizeConstants(float w, float h);
  void OffBonuses();
  void NewGame(float w, float h);
  void NextLevel(int level);

  void DeleteSpace();

  void SetKey(KeyTypes type, QKeySequence key);

protected:
  void resizeGL(int w, int h) override;
  void paintGL() override;
  void initializeGL() override;

  void UpdateGun(float elapsedSeconds);
  void UpdateAliens();
  void UpdateBullets(float elapsedSeconds);
  void UpdateBonus(float elapsedSeconds);
  void Update(float elapsedSeconds);

  void RenderStar();
  void RenderGun();
  void RenderAlien();
  void RenderObstacle();
  void RenderBullet();
  void RenderInformationString();
  void Render();

  void keyPressEvent(QKeyEvent * e) override;
  void keyReleaseEvent(QKeyEvent * e) override;

private:
  GameWindow * m_gameWindow;

  unsigned int m_frames = 0;
  QTime m_time;
  QSize m_screenSize;

  std::vector<QOpenGLTexture *> m_starTexture;

  QOpenGLTexture * m_gunTexture = nullptr;
  QOpenGLTexture * m_alienPirateTexture = nullptr;
  QOpenGLTexture * m_alienRaiderTexture = nullptr;
  QOpenGLTexture * m_alienBombardierTexture = nullptr;
  QOpenGLTexture * m_obstacleTexture = nullptr;
  QOpenGLTexture * m_backgroundPicture = nullptr;
  QOpenGLTexture * m_partObstacleTexture = nullptr;
  QOpenGLTexture * m_bulletFromGunTexture = nullptr;
  QOpenGLTexture * m_bulletFromAlienTexture = nullptr;
  QOpenGLTexture * m_heartTexture = nullptr;

  TexturedRect * m_texturedRect = nullptr;
  Space2D * m_space = nullptr;

  QKeySequence m_keyGunMoveLeft = Qt::Key_Left;
  QKeySequence m_keyGunMoveRight = Qt::Key_Right;
  QKeySequence m_keyGunShoot = Qt::Key_Up;
  QKeySequence m_keyGamePause = Qt::Key_Escape;

  QVector2D m_position;
  int m_level = 1;
  bool m_directions[4] = { false, false, false, false };
};
