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
#include <sstream>

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

  m_backgroundPicture = new QOpenGLTexture(QImage("data/images/background3.png"));

  m_starTexture.push_back(new QOpenGLTexture(QImage("data/images/stars/star11.png")));
  m_starTexture.push_back(new QOpenGLTexture(QImage("data/images/stars/star22.png")));
  m_starTexture.push_back(new QOpenGLTexture(QImage("data/images/stars/star33.png")));
  m_starTexture.push_back(new QOpenGLTexture(QImage("data/images/stars/star44.png")));
  m_starTexture.push_back(new QOpenGLTexture(QImage("data/images/stars/star55.png")));
  m_starTexture.push_back(new QOpenGLTexture(QImage("data/images/stars/star66.png")));

  m_shipTexture = new QOpenGLTexture(QImage("data/images/aliens/alienShip.png"));

  m_gunTexture = new QOpenGLTexture(QImage("data/images/gunArmored.png"));

  m_alienPirateTexture = new QOpenGLTexture(QImage("data/images/aliens/alienPirate.png"));
  m_alienRaiderTexture = new QOpenGLTexture(QImage("data/images/aliens/alienRaider.png"));
  m_alienBombardierTexture = new QOpenGLTexture(QImage("data/images/aliens/alienBombardier.png"));

  m_partObstacleTexture = new QOpenGLTexture(QImage("data/images/obstaclePart.png"));

  m_bulletFromGunTexture = new QOpenGLTexture(QImage("data/images/greenRectangle.jpg"));
  m_bulletFromAlienTexture = new QOpenGLTexture(QImage("data/images/greenRectangle.jpg"));

  m_heartTexture = new QOpenGLTexture(QImage("data/images/heart.png"));

  // check textures
  if (m_backgroundPicture == nullptr || m_gunTexture == nullptr || m_alienPirateTexture == nullptr ||
      m_alienRaiderTexture == nullptr || m_alienBombardierTexture == nullptr || m_partObstacleTexture == nullptr ||
      m_bulletFromGunTexture == nullptr || m_bulletFromAlienTexture == nullptr || m_heartTexture == nullptr)
  {
    // stop game... textures not found
  }
}

void GameGLWidget::ChangeSizeConstants(float w, float h)
{
  float alien_w = (w - GAME_PADDING_LEFT - GAME_PADDING_RIGHT) * 0.8 / (ALIEN_COUNT / 5);
  if (alien_w < ALIEN_WIDTH)
    ALIEN_WIDTH = alien_w;

  float alien_h = (h - GAME_PADDING_TOP - GAME_PADDING_BOTTOM) * 0.4 / 5;
  if (alien_h < ALIEN_HEIGHT)
    ALIEN_WIDTH = alien_h;

  OBSTACLE_DISTANCE = ((w - GAME_PADDING_LEFT - GAME_PADDING_RIGHT) - (OBSTACLE_WIDTH * OBSTACLE_COUNT)) / (OBSTACLE_COUNT + 1) ;
  OBSTACLE_BOX_LEFT = GAME_PADDING_LEFT;
}

void GameGLWidget::OffBonuses()
{
  GUN_SHOOT_SPEED = GUN_SHOOT_SPEED_DEFAULT;
  BONUS_GOD = false;

  // and set start level param
  SHIP_STARTED = false;
}

void GameGLWidget::NewGame(float w, float h)
{
  // Set false ALL BONUSES
  OffBonuses();

  // change size onstants
  ChangeSizeConstants(w, h);
  ChangeConstants(w,h);

  // init space2D
  m_space = new Space2D(Point2D(0, 0), Point2D(w, h));
  // gun start position
  m_position = QVector2D
  (
    m_space->GetGun().GetBox().GetCenter().x(),
    m_space->GetGun().GetBox().GetCenter().y()
  );
  m_time.start();
}

void GameGLWidget::NextLevel(int level)
{
  // Set False ALL BONUSES
  OffBonuses();

  // because we can change count of aliens and obstacles we need to correct its sizes
  ChangeSizeConstants(width(), height());

  // new level
  m_space->NewLvlPrepare(level);
  m_time.restart();
}

void GameGLWidget::paintGL()
{
  int GameState = m_space->CheckGameState();
  if (!GameState)
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

    QString rate;
    rate.setNum(m_space->GetGun().GetRate());
    painter.drawText(LAST_WINDOW_HORIZONTAL_SIZE - 120 , LAST_WINDOW_VERTICAL_SIZE - GAME_PADDING_BOTTOM / 2, "You rezult: " + rate);

    QPen pen = QPen(Qt::red);
    pen.setWidth(3);
    painter.setPen(pen);
    painter.drawLine(0, LAST_WINDOW_VERTICAL_SIZE - GAME_PADDING_BOTTOM + 5,  LAST_WINDOW_HORIZONTAL_SIZE, LAST_WINDOW_VERTICAL_SIZE - GAME_PADDING_BOTTOM + 5);

    painter.end();

    if (!(m_frames % 100))
    {
      m_time.start();
      m_frames = 0;
    }
    ++m_frames;
    update();
  }
  else if (GameState == 1)  // next level
  {
    NextLevel(++m_level);
    paintGL();
  }
  else if (GameState == 2)  // game over gun died
  {
    QPainter painter;
    painter.begin(this);

    painter.setPen(Qt::white);
    painter.drawText(LAST_WINDOW_HORIZONTAL_SIZE / 2 - 25, (LAST_WINDOW_VERTICAL_SIZE - GAME_PADDING_BOTTOM) / 2 - 25, "Game over.");

    QString rate;
    rate.setNum(m_space->GetGun().GetRate());
    painter.drawText(LAST_WINDOW_HORIZONTAL_SIZE / 2 - 25, (LAST_WINDOW_VERTICAL_SIZE - GAME_PADDING_BOTTOM) / 2, "You rezult: " + rate);

    painter.end();
    GAME_STARTED = false;
  }
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

void GameGLWidget::Update(float elapsedSeconds)
{
  // updates
  UpdateGun(elapsedSeconds);
  m_space->GameStep(m_frames);
}


// delete current m_space
void GameGLWidget::DeleteSpace()
{
  if (m_space != nullptr)
  {
    m_space->clear();
    delete m_space;
  }
  m_space = nullptr;
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
    if (GUN_CAN_SHOOT)
    {
      GUN_CAN_SHOOT = false;
      m_space->GunShoot();
    }
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
void GameGLWidget::RenderStar()
{
  static std::deque<int> starsX;
  static std::deque<int> starsY;
  static std::deque<int> starsT;
  static std::deque<int> starsP;
  m_texturedRect->Render(m_backgroundPicture, QVector2D(m_screenSize.width() / 2, m_screenSize.height() / 2), QSize(m_screenSize.width(), m_screenSize.height()), m_screenSize);

  static float t = 1000.0f;
  // random star
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

void GameGLWidget::RenderGun()
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

void GameGLWidget::RenderAlien()
{
  AlienMatrix const & alMat = m_space->GetAlienMatrix();
  for (size_t i = 0; i < alMat.size(); ++i)
  {
    for(size_t j = 0; j < alMat[i].size(); ++j)
    {
      if (alMat[i][j] != nullptr)
      {
        QOpenGLTexture * alienTexture = nullptr;
        if (alMat[i][j]->GetType() == AlienTypes::Pirate) alienTexture = m_alienPirateTexture;
        else if (alMat[i][j]->GetType() == AlienTypes::Raider) alienTexture = m_alienRaiderTexture;
        else alienTexture = m_alienBombardierTexture;

        m_texturedRect->Render
        (
          alienTexture,
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
}

void GameGLWidget::RenderShip()
{
  Ship2D * ship = m_space->GetShip();
  if (ship != nullptr)
  {
    m_texturedRect->Render
    (
      m_shipTexture,
      QVector2D
      (
        ship->GetBox().GetCenter().x(),
        ship->GetBox().GetCenter().y()
      ),
      QSize
      (
        ship->GetBox().GetWidth(),
        ship->GetBox().GetHeight()
      ),
      m_screenSize
    );
  }
}

void GameGLWidget::RenderObstacle()
{
  ObstacleVector const & ObVec = m_space->GetObstacleVector();
  for (size_t k = 0; k < ObVec.size(); ++k)
  {
    BoxMatrix obsMatr = ObVec[k]->GetBoxMatrix();
    for(size_t i = 0; i < obsMatr.size(); ++i)
    {
      for(size_t j = 0; j < obsMatr[i].size(); ++j)
      {
        if (obsMatr[i][j] != nullptr)
        {
          m_texturedRect->Render
          (
            m_partObstacleTexture,
            QVector2D
            (
              obsMatr[i][j]->GetBox().GetCenter().x(),
              obsMatr[i][j]->GetBox().GetCenter().y()
            ),
            QSize
            (
              obsMatr[i][j]->GetBox().GetWidth(),
              obsMatr[i][j]->GetBox().GetHeight()
            ),
            m_screenSize
          );
        }
      }
    }
  }
}

void GameGLWidget::RenderBullet()
{
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

void GameGLWidget::RenderInformationString()
{
  for(int i = 0; i < m_space->GetGun().GetLives(); i++)
  {
    m_texturedRect->Render
    (
      m_heartTexture,
      QVector2D(50 + GAME_PADDING_BOTTOM * ( i + 0.5 ), GAME_PADDING_BOTTOM/2),
      QSize(GAME_PADDING_BOTTOM * 0.5, GAME_PADDING_BOTTOM * 0.5),
      m_screenSize
    );
  }
}

void GameGLWidget::Render()
{
  this->RenderStar();
  this->RenderGun();
  this->RenderAlien();
  this->RenderShip();
  this->RenderObstacle();
  this->RenderBullet();
  this->RenderInformationString();
}
