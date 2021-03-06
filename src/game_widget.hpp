#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QTime>
#include <array>

#include "textured_rect.hpp"
#include "game_window.hpp"
#include "gameclasses/space.hpp"

#include <chrono>

class GameWindow;

QT_FORWARD_DECLARE_CLASS(QOpenGLTexture)
QT_FORWARD_DECLARE_CLASS(QOpenGLShader)
QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)

class NoTextureException: public std::exception
{
public:
  const char * what() const noexcept;
};

class GameGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
  Q_OBJECT
public:
  GameGLWidget(GameWindow * mw);
  ~GameGLWidget();

  void ChangeSizeConstants(float w, float h);
  void NewGame(float w, float h);
  void NextLevel(int level);

  void DeleteSpace();
  void SetVolume();

  void SetKey(KeyTypes type, QKeySequence key);
  Space2D* GetSpace();

protected:
  void resizeGL(int w, int h) override;
  void initializeGL() override;

  void paintGLActiveGame();
  void paintGLNextLevel();
  void paintGLGameOver();
  void paintGL() override;

  void UpdateGun(float elapsedSeconds);
  void Update(float elapsedSeconds);

  void RenderStar();
  void RenderGun();
  void RenderAlien();
  void RenderShip();
  void RenderObstacle();
  void RenderBullet();
  void RenderInformationString();
  void RenderBonus();
  void RenderBoom();
  void Render();

  void keyPressEvent(QKeyEvent * e) override;
  void keyReleaseEvent(QKeyEvent * e) override;

private:
  GameWindow * m_gameWindow;

  unsigned int m_frames = 0;
  QTime m_time;
  QSize m_screenSize;

  // textures
  std::vector<QOpenGLTexture *> m_starTexture;
  std::vector<QOpenGLTexture *> m_bonusTexture;

  QOpenGLTexture * m_shipTexture = nullptr;
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
  QOpenGLTexture * m_boomTexture = nullptr;

  // key
  QKeySequence m_keyGunMoveLeft = Qt::Key_Left;
  QKeySequence m_keyGunMoveRight = Qt::Key_Right;
  QKeySequence m_keyGunShoot = Qt::Key_Up;
  QKeySequence m_keyGamePause = Qt::Key_Escape;

  // for pause
  bool m_nextLevel = false;
  bool m_gameOver = false;

  // main
  TexturedRect * m_texturedRect = nullptr;
  Space2D * m_space = nullptr;
  QVector2D m_position;
  int m_level = 0;
  bool m_directions[4] = { false, false, false, false };
};
