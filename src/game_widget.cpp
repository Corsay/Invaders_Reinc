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

// exceptions
const char * NoTextureException::what() const noexcept
{
  return "Not all game textures found! \n Не все игровые текстуры найдены!";
}


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
  // textures
  for(unsigned int i = 0; i < m_starTexture.size(); i++)
    delete m_starTexture[i];
  for(unsigned int i = 0; i < m_bonusTexture.size(); i++)
    delete m_bonusTexture[i];
  delete m_shipTexture;
  delete m_gunTexture;
  delete m_alienPirateTexture;
  delete m_alienRaiderTexture;
  delete m_alienBombardierTexture;
  delete m_obstacleTexture;
  delete m_backgroundPicture;
  delete m_partObstacleTexture;
  delete m_bulletFromGunTexture;
  delete m_bulletFromAlienTexture;
  delete m_heartTexture;
  delete m_boomTexture;
  // main
  delete m_texturedRect;
  DeleteSpace();
  doneCurrent();
}

void GameGLWidget::initializeGL()
{
  initializeOpenGLFunctions();

  m_texturedRect = new TexturedRect();
  m_texturedRect->Initialize(this);

  // TEXTURES
  m_backgroundPicture = new QOpenGLTexture(QImage("data/images/background.png"));

  m_starTexture.push_back(new QOpenGLTexture(QImage("data/images/stars/star11.png")));
  m_starTexture.push_back(new QOpenGLTexture(QImage("data/images/stars/star22.png")));
  m_starTexture.push_back(new QOpenGLTexture(QImage("data/images/stars/star33.png")));
  m_starTexture.push_back(new QOpenGLTexture(QImage("data/images/stars/star44.png")));
  m_starTexture.push_back(new QOpenGLTexture(QImage("data/images/stars/star55.png")));
  m_starTexture.push_back(new QOpenGLTexture(QImage("data/images/stars/star66.png")));

  // +
  m_bonusTexture.push_back(new QOpenGLTexture(QImage("data/images/bonuses/X2.png")));             // x2
  m_bonusTexture.push_back(new QOpenGLTexture(QImage("data/images/bonuses/Add_heart.png")));      // add life
  m_bonusTexture.push_back(new QOpenGLTexture(QImage("data/images/bonuses/Gun_fast_shoot.png"))); // gun fast shoot
  m_bonusTexture.push_back(new QOpenGLTexture(QImage("data/images/bonuses/Gun_lazer.png")));      // gun laser
  m_bonusTexture.push_back(new QOpenGLTexture(QImage("data/images/bonuses/Heal_obstacles.png"))); // heal obstacles
  m_bonusTexture.push_back(new QOpenGLTexture(QImage("data/images/bonuses/Hit_aliens.png")));     // hit aliens
  m_bonusTexture.push_back(new QOpenGLTexture(QImage("data/images/bonuses/God.png")));            // god
  // -
  m_bonusTexture.push_back(new QOpenGLTexture(QImage("data/images/bonuses/X05.png")));             // X0.5
  m_bonusTexture.push_back(new QOpenGLTexture(QImage("data/images/bonuses/Alien_fast_shoot.png")));// alien fast shoot
  m_bonusTexture.push_back(new QOpenGLTexture(QImage("data/images/bonuses/Hit_obstacles.png")));   // Hit obstacles
  m_bonusTexture.push_back(new QOpenGLTexture(QImage("data/images/bonuses/Nothing.png")));         // have not a bonus

  m_shipTexture = new QOpenGLTexture(QImage("data/images/aliens/alienShip.png"));

  m_gunTexture = new QOpenGLTexture(QImage("data/images/gunMilitary.png"));

  m_alienPirateTexture = new QOpenGLTexture(QImage("data/images/aliens/alienPirate.png"));
  m_alienRaiderTexture = new QOpenGLTexture(QImage("data/images/aliens/alienRaider.png"));
  m_alienBombardierTexture = new QOpenGLTexture(QImage("data/images/aliens/alienBombardier.png"));

  m_partObstacleTexture = new QOpenGLTexture(QImage("data/images/obstaclePart.png"));

  m_bulletFromGunTexture = new QOpenGLTexture(QImage("data/images/rectangle.png"));
  m_bulletFromAlienTexture = new QOpenGLTexture(QImage("data/images/rectangle2.png"));

  m_heartTexture = new QOpenGLTexture(QImage("data/images/heart.png"));
  m_boomTexture = new  QOpenGLTexture(QImage("data/images/boom.png"));

  // check textures
  for (int i = 0; i < m_bonusTexture.size(); ++i)
  {
    if (!m_bonusTexture[i]->isCreated())
    {
      throw NoTextureException();
    }
  }

  for (int i = 0; i < m_starTexture.size(); ++i)
  {
    if (!m_starTexture[i]->isCreated())
    {
      throw NoTextureException();
    }
  }

  if (!m_boomTexture->isCreated() || !m_heartTexture->isCreated() || !m_bulletFromAlienTexture->isCreated() ||
      !m_bulletFromGunTexture->isCreated() || !m_partObstacleTexture->isCreated() || !m_alienBombardierTexture->isCreated() ||
      !m_alienRaiderTexture->isCreated() || !m_alienPirateTexture->isCreated() || !m_gunTexture->isCreated() ||
      !m_shipTexture->isCreated() || !m_backgroundPicture->isCreated())
  {
    throw NoTextureException();
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

  if((LAST_WINDOW_HORIZONTAL_SIZE - (GAME_PADDING_LEFT + GAME_PADDING_RIGHT) - 100) / (ALIEN_WIDTH + 12.0) < ALIEN_COUNT / 5)
  {
    ALIEN_HORIZONTAL_DISTANCE = 0;
    if ((LAST_WINDOW_HORIZONTAL_SIZE - (GAME_PADDING_LEFT + GAME_PADDING_RIGHT) - 100) / ALIEN_WIDTH < ALIEN_COUNT / 5)
    {
      ALIEN_WIDTH = (LAST_WINDOW_HORIZONTAL_SIZE - (GAME_PADDING_LEFT + GAME_PADDING_RIGHT) - 100) / (ALIEN_COUNT / 5);
    }
  }
  else
  {
    ALIEN_HORIZONTAL_DISTANCE = 12.0f;
  }

  OBSTACLE_DISTANCE = ((w - GAME_PADDING_LEFT - GAME_PADDING_RIGHT) - (OBSTACLE_WIDTH * OBSTACLE_COUNT)) / (OBSTACLE_COUNT + 1) ;
  OBSTACLE_BOX_LEFT = GAME_PADDING_LEFT;
  ChangeConstants(w,h);
}

void GameGLWidget::NewGame(float w, float h)
{
  // reset flag
  m_gameOver = false;
  m_nextLevel = false;
  m_level = 0;

  // change size onstants
  ChangeSizeConstants(w, h);

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
  // reset flag
  m_nextLevel = false;

  // because we can change count of aliens and obstacles we need to correct its sizes
  ChangeSizeConstants(width(), height());

  // new level
  m_space->NewLvlPrepare(level);
  m_time.restart();
}

// PAINTING
void GameGLWidget::paintGLActiveGame()
{
  int const elapsed = m_time.elapsed();
  Update(elapsed / 1000.0f);

  QPainter painter;
  painter.begin(this);
  painter.setPen(Qt::white);
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

  QRect rect = QRect(0, LAST_WINDOW_VERTICAL_SIZE - GAME_PADDING_BOTTOM + 2, LAST_WINDOW_HORIZONTAL_SIZE - 10, GAME_PADDING_BOTTOM);

  QString text = GAME_RESULT + QString::number(m_space->GetGun().GetRate());

  if (elapsed != 0)
  {
    text += "\n" + QString::number(m_frames / (elapsed / 1000.0), 'f', 2) + " fps";
  }

  painter.drawText(rect, Qt::AlignRight | Qt::AlignVCenter, text);

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

void GameGLWidget::paintGLNextLevel()
{
  if (!m_nextLevel)  // pause with info
  {
    QPainter painter;
    painter.begin(this);

    QRect rect = QRect(0, 0, LAST_WINDOW_HORIZONTAL_SIZE, LAST_WINDOW_VERTICAL_SIZE);

    QString text = GAME_CURRENT_RESULT + QString::number(m_space->GetGun().GetRate()) + "\n"
        + GAME_PRE_NEXT_LEVEL + QString::number(m_level + 1) + "\n"
        + GAME_NEXT_ADDITIONAL + "\n\n";

    // Check cheat using
    if (CHEAT_USED)
    {
      text += GAME_USE_CHEATS_MSG + "\n\n";
    }

    // next level info
    text += GAME_NEXT_ALIEN_MODIF + "\n";
    if (ALIEN_MOVE_SPEED_TIMER_DEFAULT - (m_level * ALIEN_MOVE_SPEED_TIMER_INC) >= ALIEN_MOVE_SPEED_TIMER_MIN)
    {
      text += GAME_NEXT_ALIEN_MODIF_FAST_MOVE + "\n";
    }
    if (ALIEN_SHOOT_SPEED_DEFAULT - (m_level * ALIEN_SHOOT_SPEED_INC) >= ALIEN_SHOOT_SPEED_MIN)
    {
      text += GAME_NEXT_ALIEN_MODIF_FAST_SHOOT + "\n";
    }
    if (((m_level + 1) % ALIEN_HEALTH_LVL == 0) && ALIEN_HEALTH_DEFAULT + ((m_level + 1) / ALIEN_HEALTH_LVL * ALIEN_HEALTH_INC) <= ALIEN_HEALTH_MAX)
    {
      text += GAME_NEXT_ALIEN_MODIF_SPEC_LIFE;
    }

    painter.setPen(Qt::white);
    painter.drawText(rect, Qt::AlignCenter, text);
  }
  else              // next level
  {
    NextLevel(++m_level);
    paintGL();
  }
}

void GameGLWidget::paintGLGameOver()
{
  GAME_STARTED = false;
  if (!m_gameOver)
  {
    QPainter painter;
    painter.begin(this);
    painter.setPen(Qt::white);
    //painter.beginNativePainting();

    glFrontFace(GL_CW);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Render();

    glDisable(GL_CULL_FACE);
    glDisable(GL_BLEND);

    //painter.endNativePainting();

    QRect rect = QRect(5, LAST_WINDOW_VERTICAL_SIZE - GAME_PADDING_BOTTOM + 2, LAST_WINDOW_HORIZONTAL_SIZE - 10, GAME_PADDING_BOTTOM);

    QString text = GAME_OVER + "\n" + GAME_OVER_ADDITIONAL;

    painter.drawText(rect, Qt::AlignLeft | Qt::AlignVCenter, text);

    text = GAME_RESULT + QString::number(m_space->GetGun().GetRate());

    painter.drawText(rect, Qt::AlignRight | Qt::AlignVCenter, text);

    QPen pen = QPen(Qt::red);
    pen.setWidth(3);
    painter.setPen(pen);
    painter.drawLine(0, LAST_WINDOW_VERTICAL_SIZE - GAME_PADDING_BOTTOM + 5,  LAST_WINDOW_HORIZONTAL_SIZE, LAST_WINDOW_VERTICAL_SIZE - GAME_PADDING_BOTTOM + 5);

    painter.end();
  }
  else
  {
    m_gameWindow->m_mainWindow->InterfaceAddRecord();
    m_gameWindow->m_stackedWidget->setCurrentIndex(3);
  }
}

void GameGLWidget::paintGL()
{
  int GameState = m_space->CheckGameState();
  if (!GameState)
  {
    paintGLActiveGame();
  }
  else if (GameState == 1)  // next level
  {
    paintGLNextLevel();
  }
  else if (GameState == 2)  // game over gun died
  {
    paintGLGameOver();
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
  m_space->GameStep();
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

void GameGLWidget::SetVolume()
{
  if (m_space != nullptr) m_space->SetVolume();
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
  if (m_gameWindow->m_stackedWidget->currentIndex() == 2 )
  {
    if (QKeySequence(e->key()) == m_keyGunMoveLeft)
      m_directions[kLeftDirection] = true;

    else if (QKeySequence(e->key()) == m_keyGunMoveRight)
      m_directions[kRightDirection] = true;

    else if (QKeySequence(e->key()) == m_keyGunShoot && m_space->CheckGameState() == 0)
    {
      if (GUN_CAN_SHOOT)
      {
        GUN_CAN_SHOOT = false;
        m_space->GunShoot();
      }
    }

    // check zone
    if (QKeySequence(e->key()) == Qt::Key_Return)
    {
      if (m_space->CheckGameState() == 1) m_nextLevel = true;
      if (m_space->CheckGameState() == 2) m_gameOver = true;
    }

    // cheat zone
    if (e->key() == Qt::Key_F10)
    {
      CHEAT_USED = true;
      m_space->GetAlienManager().clear();
    }
    if (e->key() == Qt::Key_F11)
    {
      CHEAT_USED = true;
      BONUS_GOD = true;
    }
    if (e->key() == Qt::Key_F12)
    {
      CHEAT_USED = true;
      GUN_SHOOT_SPEED = 0.001;
    }
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
      QVector2D(GAME_PADDING_BOTTOM * 0.8 + GAME_PADDING_BOTTOM * (i + 0.5), GAME_PADDING_BOTTOM / 2 - 3),
      QSize(GAME_PADDING_BOTTOM * 0.5, GAME_PADDING_BOTTOM * 0.5),
      m_screenSize
    );
  }
}

void GameGLWidget::RenderBonus()
{
  QOpenGLTexture * bonusTexture = nullptr;
  // detect which bonus are active
  if (BONUS_X2)
    bonusTexture = m_bonusTexture[0];
  else if (BONUS_ADD_LIVE)
    bonusTexture = m_bonusTexture[1];
  else if (BONUS_GUN_FAST_SHOOT)
    bonusTexture = m_bonusTexture[2];
  else if (BONUS_LAZER)
    bonusTexture = m_bonusTexture[3];
  else if (BONUS_HEAL_OBSTACLES)
    bonusTexture = m_bonusTexture[4];
  else if (BONUS_HIT_ALL_ALIENS)
    bonusTexture = m_bonusTexture[5];
  else if (BONUS_GOD)
    bonusTexture = m_bonusTexture[6];
  else if (BONUS_ANTI_X2)
    bonusTexture = m_bonusTexture[7];
  else if (BONUS_ALIEN_FAST_SHOOT)
    bonusTexture = m_bonusTexture[8];
  else if (BONUS_HIT_OBSTACLES)
    bonusTexture = m_bonusTexture[9];
  else
    bonusTexture = m_bonusTexture[10];
  // paint
  m_texturedRect->Render
  (
    bonusTexture,
    QVector2D(GAME_PADDING_BOTTOM * 0.5, GAME_PADDING_BOTTOM / 2 - 3),
    QSize(GAME_PADDING_BOTTOM * 0.7, GAME_PADDING_BOTTOM * 0.7),
    m_screenSize
  );
}

void GameGLWidget::RenderBoom()
{
  BoomList & boom = m_space->GetBoomList();
  std::vector< BoomList::iterator > boomForDel;
  for(auto it = boom.begin(); it != boom.end(); ++it)
  {
    m_texturedRect->Render
    (
      m_boomTexture,
      QVector2D(it->m_place.x(), it->m_place.y()),
      QSize(it->GetWidth(), it->GetHeigth()),
      m_screenSize
    );
    it->m_timer--;
    if(it->m_timer == 0)
    {
      boomForDel.push_back(it);
    }
  }
  for(auto it = boomForDel.begin(); it != boomForDel.end(); ++it)
    boom.erase(*it);
}

void GameGLWidget::Render()
{
  m_texturedRect->Render(m_backgroundPicture, QVector2D(m_screenSize.width() / 2, m_screenSize.height() / 2), QSize(m_screenSize.width(), m_screenSize.height()), m_screenSize);
  this->RenderStar();
  if (m_space->CheckGameState() == 0)
  {
    this->RenderGun();
    this->RenderBonus();
  }
  this->RenderAlien();
  this->RenderShip();
  this->RenderObstacle();
  this->RenderBullet();
  this->RenderInformationString();
  this->RenderBoom();
}

Space2D* GameGLWidget::GetSpace(){ return m_space; }
