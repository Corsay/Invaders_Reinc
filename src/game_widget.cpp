#include "game_widget.hpp"

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

#include "game_window.hpp"

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
  setMinimumSize(1024, 768);
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


  m_space = new Space2D;
  m_time.start();

}

void GameGLWidget::paintGL()
{
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  Render();

  glDisable(GL_BLEND);

  update();
}

void GameGLWidget::resizeGL(int w, int h)
{
  m_screenSize.setWidth(w);
  m_screenSize.setHeight(h);
}

void GameGLWidget::Update(float elapsedSeconds)
{
  float const kSpeed = 20.0f; // pixels per second.

  if (m_directions[kUpDirection])
    m_position.setY(m_position.y() + kSpeed * elapsedSeconds);
  if (m_directions[kDownDirection])
    m_position.setY(m_position.y() - kSpeed * elapsedSeconds);
  if (m_directions[kLeftDirection])
    m_position.setX(m_position.x() - kSpeed * elapsedSeconds);
  if (m_directions[kRightDirection])
    m_position.setX(m_position.x() + kSpeed * elapsedSeconds);
}

void GameGLWidget::StarRender()
{
  static std::deque<int> starsX;
  static std::deque<int> starsY;
  static std::deque<int> starsT;
  static std::deque<int> starsP;
  m_texturedRect->Render(m_backgroundPicture, QVector2D(m_screenSize.width() / 2, m_screenSize.height() / 2), QSize(m_screenSize.width(), m_screenSize.height()), m_screenSize);

  static float t = 1000.0f;
  //случайная звезда
  if(qrand()%1 == 0)
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
  m_texturedRect->Render(m_gunTexture, QVector2D(
                                                   m_space->GetGun().GetBox().GetCenter().x(),
                                                   m_space->GetGun().GetBox().GetCenter().y()
                                                 ), QSize(
                                                            m_space->GetGun().GetBox().GetWidth(),
                                                            m_space->GetGun().GetBox().GetHeight()
                                                          ), m_screenSize);
}
void GameGLWidget::AlienRender()
{
  AlienMatrix const & alMat = m_space->GetAlienMatrix();
  for (size_t i = 0; i < alMat.size(); ++i)
    for(size_t j = 0; j < alMat[0].size(); ++j)
    {
        m_texturedRect->Render(m_alienTexture, QVector2D(
                                                         alMat[i][j]->GetBox().GetCenter().x(),
                                                         alMat[i][j]->GetBox().GetCenter().y()
                                                       ), QSize(
                                                                  alMat[i][j]->GetBox().GetWidth(),
                                                                  alMat[i][j]->GetBox().GetHeight()
                                                                ), m_screenSize);
    }
}
void GameGLWidget::ObstacleRender()
{
  ObstacleVector const & ObVec = m_space->GetObstacleVector();
  for (size_t k = 0; k < ObVec.size(); ++k)
    for(size_t i = 0; i < ObVec[k]->GetBoxMatrix().size(); ++i)
      for(size_t j = 0; j < ObVec[k]->GetBoxMatrix()[0].size(); ++j)
      {
          m_texturedRect->Render(m_partObstacleTexture, QVector2D(
                                                             ObVec[k]->GetBox().GetCenter().x(),
                                                             ObVec[k]->GetBox().GetCenter().y()
                                                           ), QSize(
                                                                    ObVec[k]->GetBox().GetWidth(),
                                                                    ObVec[k]->GetBox().GetHeight()
                                                                  ), m_screenSize);
      }
}
void GameGLWidget::BulletRender(){
  BulletList const & bulListGun = m_space->GetBulletFromGun();
  BulletList const & bulListAli = m_space->GetBulletFromAlien();
  for(auto it = bulListGun.begin(); it !=bulListGun.end(); ++it)
    m_texturedRect->Render(m_bulletFromGunTexture, QVector2D(
                                                       it->GetBox().GetCenter().x(),
                                                       it->GetBox().GetCenter().y()
                                                     ), QSize(
                                                              it->GetBox().GetWidth(),
                                                              it->GetBox().GetHeight()
                                                            ), m_screenSize);

  for(auto it = bulListAli.begin(); it !=bulListAli.end(); ++it)
    m_texturedRect->Render(m_bulletFromAlienTexture, QVector2D(
                                                       it->GetBox().GetCenter().x(),
                                                       it->GetBox().GetCenter().y()
                                                     ), QSize(
                                                              it->GetBox().GetWidth(),
                                                              it->GetBox().GetHeight()
                                                            ), m_screenSize);


}

void GameGLWidget::Render()
{
  this->StarRender();
  this->GunRender();
  this->AlienRender();
  this->ObstacleRender();
  this->BulletRender();
}
