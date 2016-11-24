#include "game_widget.hpp"

#include "gameclasses/constants.hpp"
#include <QPainter>
#include <QPaintEngine>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QCoreApplication>
#include <QtGui/QMouseEvent>
#include <QtGui/QGuiApplication>
#include <deque>
#include <cstdlib>

#include <iostream>

namespace
{
  int constexpr kLeftDirection = 0;
  int constexpr kRightDirection = 1;
  int constexpr kUpDirection = 2;
  int constexpr kDownDirection = 3;
} // namespace

GameGLWidget::GameGLWidget(GameWindow * mw)
  : m_gameWindow(mw)
{
  setMinimumSize(mw->width(), mw->height());
  setFocusPolicy(Qt::StrongFocus);
  qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
}

GameGLWidget::~GameGLWidget()
{
  makeCurrent();
  for(unsigned int i = 0; i < m_starTexture.size(); i++)
    delete m_starTexture[i];
  delete m_texturedRect;
  doneCurrent();
}

void GameGLWidget::initializeGL()
{
  initializeOpenGLFunctions();

  m_texturedRect = new TexturedRect();
  m_texturedRect->Initialize(this);

  m_starTexture.push_back(new QOpenGLTexture(QImage("data/images/stars/star44.png")));
  m_starTexture.push_back(new QOpenGLTexture(QImage("data/images/stars/star55.png")));
  m_starTexture.push_back(new QOpenGLTexture(QImage("data/images/stars/star66.png")));

  m_gunTexture = new QOpenGLTexture(QImage("data/images/gun.jpg"));
  m_backgroundPicture = new QOpenGLTexture(QImage("data/images/background.jpg"));
  m_alienTexture = new QOpenGLTexture(QImage("data/images/alien.png"));
  m_partObstacleTexture = new QOpenGLTexture(QImage("data/images/greenRectangle.jpg"));
  m_bulletFromGunTexture = new QOpenGLTexture(QImage("data/images/greenRectangle.jpg"));
  m_bulletFromAlienTexture = new QOpenGLTexture(QImage("data/images/greenRectangle.jpg"));
}

void GameGLWidget::NewGame(float w, float h, int gunLives, int countOfAliens, int countOfObstacles)
{
  float alien_w = (w - GAME_PADDING_LEFT - GAME_PADDING_RIGHT) * 0.8 / ( countOfAliens/5 );
  if( alien_w < AlIEN_WIDTH )
    AlIEN_WIDTH = alien_w;

  float alien_h = (h - GAME_PADDING_TOP - GAME_PADDING_BOTTOM) * 0.4 / 5;
  if( alien_h < ALIEN_HEIGHT )
    AlIEN_WIDTH = alien_h;
  changeConstants(w,h);

  // init space2D
  m_space = new Space2D(Point2D(0, 0), Point2D(w, h), gunLives, countOfAliens, countOfObstacles);
  // gun start position
  m_position = QVector2D
    (
      m_space->GetGun().GetBox().GetCenter().x(),
      m_space->GetGun().GetBox().GetCenter().y()
    );
  m_time.start();
}

void GameGLWidget::NextLevel()
{
  std::cout << "Not released" << std::endl;
}

void GameGLWidget::paintGL()
{
  int const elapsed = m_time.elapsed();
  Update(elapsed / 1000.0f);

  QPainter painter;
  painter.begin(this);
  painter.beginNativePainting();

  glFrontFace(GL_CW);
  glCullFace(GL_BACK);
  glEnable(GL_CULL_FACE);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  Render();

  glDisable(GL_CULL_FACE);
  glDisable(GL_BLEND);

  painter.endNativePainting();

  if (elapsed != 0)
   {
     QString framesPerSecond;
     framesPerSecond.setNum(m_frames / (elapsed / 1000.0), 'f', 2);
     painter.setPen(Qt::white);
     painter.drawText(20, 40, framesPerSecond + " fps");
   }
   painter.end();

   if (!(m_frames % 100))
   {
     m_time.start();
     m_frames = 0;
   }
   ++m_frames;
   update();
}

void GameGLWidget::resizeGL(int w, int h)
{
  m_screenSize.setWidth(w);
  m_screenSize.setHeight(h);

}

// UPDATE FUNCTIONS
void GameGLWidget::UpdateGun(float elapsedSeconds)
{
  // gun speed
  float const kSpeed = 10.0f; // pixels per second.
  // move gun left
  if (m_directions[kLeftDirection])
  {
    if (m_position.x() > GUN_WIDTH + GAME_PADDING_LEFT)
    {
      if (m_position.x() - kSpeed * elapsedSeconds > GUN_WIDTH + GAME_PADDING_LEFT)
        m_position.setX(m_position.x() - kSpeed * elapsedSeconds);
      else
        m_position.setX(GUN_WIDTH / 2 + GAME_PADDING_LEFT);
    }
  }
  // move gun right
  if (m_directions[kRightDirection])
  {
    if (m_position.x() < width() - GUN_WIDTH - GAME_PADDING_RIGHT)
    {
      if (m_position.x() + kSpeed * elapsedSeconds < width() - GUN_WIDTH - GAME_PADDING_RIGHT)
        m_position.setX(m_position.x() + kSpeed * elapsedSeconds);
      else
        m_position.setX(width() - GUN_WIDTH / 2 - GAME_PADDING_RIGHT);
    }
  }
  // send new position of gun to space2d
  m_space->SetGunPozition(m_position.x(), m_position.y());
}

void GameGLWidget::UpdateAliens()
{
  if(qrand() % 20 ==0)
   m_space->AlienShoot();
  static int int_timer;
  if(int_timer)
    int_timer--;
  else
  {
    m_space->AliensMove();
    int_timer = 30;
  }
}

void GameGLWidget::UpdateBullets(float elapsedSeconds)
{
  m_space->BulletsMove(height());
}

void GameGLWidget::Update(float elapsedSeconds)
{
  UpdateGun(elapsedSeconds);
  UpdateBullets(elapsedSeconds);
  UpdateAliens();
}

// KEY EVENTS
// Set new key bind
void GameGLWidget::SetKey(KeyTypes type, QKeySequence key)
{
  switch (type)
  {
    case KeyTypes::KeyMoveLeft:
    {
      m_keyGunMoveLeft = key;
      break;
    }
    case KeyTypes::KeyMoveRight:
    {
      m_keyGunMoveRight = key;
      break;
    }
    case KeyTypes::KeyShoot:
    {
      m_keyGunShoot = key;
      break;
    }
    case KeyTypes::KeyPause:
    {
      m_keyGamePause = key;
      break;
    }
  }
}

void GameGLWidget::keyPressEvent(QKeyEvent * e)
{
  if (QKeySequence(e->key()) == m_keyGunMoveLeft)
    m_directions[kLeftDirection] = true;

  else if (QKeySequence(e->key()) == m_keyGunMoveRight)
    m_directions[kRightDirection] = true;

  else if (QKeySequence(e->key()) == m_keyGunShoot)
  {
    m_space->GunShoot();
  }

  else if (QKeySequence(e->key()) == m_keyGamePause)
  {
    //
  }
}

void GameGLWidget::keyReleaseEvent(QKeyEvent * e)
{
  if (QKeySequence(e->key()) == m_keyGunMoveLeft)
    m_directions[kLeftDirection] = false;

  else if (QKeySequence(e->key()) == m_keyGunMoveRight)
    m_directions[kRightDirection] = false;
}

// RENDER GAME OBJECTS
void GameGLWidget::StarRender()
{
  static std::deque<int> starsX;
  static std::deque<int> starsY;
  static std::deque<int> starsT;
  static std::deque<int> starsP;
  m_texturedRect->Render(m_backgroundPicture, QVector2D(m_screenSize.width() / 2, m_screenSize.height() / 2), QSize(m_screenSize.width(), m_screenSize.height()), m_screenSize);

  static float t = 1000.0f;
  //случайная звезда
  if(qrand() % 5 == 0)
  {
    starsX.push_back(qrand() % m_screenSize.width());
    starsY.push_back(qrand() % m_screenSize.height());
    starsT.push_back(m_time.elapsed());
    starsP.push_back(qrand() % m_starTexture.size());
  }
  for(int i = 0; i < starsX.size(); i++)
  {
    if(starsT[i] <= m_time.elapsed() - t)
    {
      starsX.pop_front();
      starsY.pop_front();
      starsT.pop_front();
      starsP.pop_front();
    }
    else
    {
      int s = 10 * sin((starsT[i] - m_time.elapsed()) / t * M_PI);
      m_texturedRect->Render(m_starTexture[starsP[i]], QVector2D(starsX[i], starsY[i]), QSize(s, s), m_screenSize);
    }
  }
}

void GameGLWidget::GunRender()
{
  m_texturedRect->Render
  (
    m_gunTexture,
    m_position,
    QSize
    (
      m_space->GetGun().GetBox().GetWidth(),
      m_space->GetGun().GetBox().GetHeight()
    ),
    m_screenSize
  );
}

void GameGLWidget::AlienRender()
{
  AlienMatrix const & alMat = m_space->GetAlienMatrix();
  for (size_t i = 0; i < alMat.size(); ++i)
  {
    for(size_t j = 0; j < alMat[0].size(); ++j)
    {
      if( alMat[i][j] != nullptr )
        m_texturedRect->Render
        (
          m_alienTexture,
          QVector2D
          (
            alMat[i][j]->GetBox().GetCenter().x(),
            alMat[i][j]->GetBox().GetCenter().y()
          ),
          QSize
          (
            alMat[i][j]->GetBox().GetWidth(),
            alMat[i][j]->GetBox().GetHeight()
          ),
          m_screenSize
        );
    }
  }
}

void GameGLWidget::ObstacleRender()
{
  ObstacleVector const & ObVec = m_space->GetObstacleVector();
  for (size_t k = 0; k < ObVec.size(); ++k)
  {
    for(size_t i = 0; i < ObVec[k]->GetBoxMatrix().size(); ++i)
    {
      for(size_t j = 0; j < ObVec[k]->GetBoxMatrix()[0].size(); ++j)
      {
        m_texturedRect->Render
        (
          m_partObstacleTexture,
          QVector2D
          (
            ObVec[k]->GetBox().GetCenter().x(),
            ObVec[k]->GetBox().GetCenter().y()
          ),
          QSize
          (
            ObVec[k]->GetBox().GetWidth(),
            ObVec[k]->GetBox().GetHeight()
          ),
          m_screenSize
        );
      }
    }
  }
}

void GameGLWidget::BulletRender(){
  BulletList const & bulListGun = m_space->GetBulletFromGun();
  BulletList const & bulListAlien = m_space->GetBulletFromAlien();
  for(auto it = bulListGun.begin(); it != bulListGun.end(); ++it)
  {
    m_texturedRect->Render
    (
      m_bulletFromGunTexture,
      QVector2D
      (
        it->GetBox().GetCenter().x(),
        it->GetBox().GetCenter().y()
      ),
      QSize
      (
        it->GetBox().GetWidth(),
        it->GetBox().GetHeight()
      ),
      m_screenSize
    );
  }
  for(auto it = bulListAlien.begin(); it != bulListAlien.end(); ++it)
  {
    m_texturedRect->Render
    (
      m_bulletFromAlienTexture,
      QVector2D
      (
        it->GetBox().GetCenter().x(),
        it->GetBox().GetCenter().y()
      ),
      QSize
      (
        it->GetBox().GetWidth(),
        it->GetBox().GetHeight()
      ),
      m_screenSize
    );
  }
}

void GameGLWidget::Render()
{
  this->StarRender();
  this->GunRender();
  this->AlienRender();
  this->ObstacleRender();
  this->BulletRender();
}
