#pragma once

#include "gameentity.hpp"
#include "gun.hpp"
#include "alienmanager.hpp"
#include "bulletmanager.hpp"
#include "obstacle.hpp"
#include "factory.hpp"
#include "obstaclemanager.hpp"
#include <algorithm>

class Space2D final : public GameEntity2D
{
public:
  // Allow default constructor.
  Space2D() = default;

  // Destructor.
  ~Space2D() = default;

  // Constructors with parameters.
  Space2D(Point2D const & leftBottom, Point2D const & rightTop)
    :GameEntity2D(leftBottom, rightTop)
  {}
  // Capabilities
  // if add manager this code can be replaced, because later added keypress
  void GunMoveLeft()
  {
    if(m_gun.GetBox().left() - GUN_STEP <= GUN_LEFT_LIMIT)
      m_gun.GetBox().HorizontalShift(m_gun.GetBox().left() - GUN_LEFT_LIMIT);
    else
      m_gun.GetBox().HorizontalShift(-GUN_STEP);
  }
  void GunMoveRight()
  {
    if(m_gun.GetBox().right() + GUN_STEP >= GUN_LEFT_LIMIT)
      m_gun.GetBox().HorizontalShift( GUN_RIGHT_LIMIT - m_gun.GetBox().left());
    else
      m_gun.GetBox().HorizontalShift(GUN_STEP);
  }

  void GunShoot()  // if add manager this code can be replaced, because later added keypress
  {
    Point2D start = m_gun.GetBox().GetCenter();
    start.SetY(m_gun.GetBox().top());
    Bullet2D bullet(
      Point2D {start.x() - BULLET_WIDTH / 2, start.y() - BULLET_HEIGHT / 2},
      Point2D {start.x() + BULLET_WIDTH / 2, start.y() + BULLET_HEIGHT / 2},
      BULLET_DAMAGE_START,
      BULLET_SPEED_START
    );
    m_bulletManager.NewBullet(bullet, GunType);
  }

  void AlienShoot()
  {
    Alien2D alien = m_alienManager.SelectShooter(m_gun.GetBox());
    Point2D start = alien.GetBox().GetCenter();
    start.SetY(alien.GetBox().top());
    Bullet2D bullet(
      Point2D {start.x() - BULLET_WIDTH / 2, start.y() - BULLET_HEIGHT / 2},
      Point2D {start.x() + BULLET_WIDTH / 2, start.y() + BULLET_HEIGHT / 2},
      BULLET_DAMAGE_START,
      BULLET_SPEED_START
    );
    m_bulletManager.NewBullet(bullet, AlienType);
  }

  void CheckAllIntersections()
  {
    // check count of bullets in bulletManager
    BulletList & BulletFromGun = m_bulletManager.GetBulletsFromGunList();
    BulletList & BulletFromAlien = m_bulletManager.GetBulletsFromAliensList();

    for(auto it = BulletFromGun.begin(); it != BulletFromGun.end(); ++it)
      if( m_alienManager.CheckIntersection(*it) )
        BulletFromGun.erase(it);
      else if( m_obstacleManager.CheckIntersection(*it) )
        BulletFromGun.erase(it);

    for(auto it = BulletFromAlien.begin(); it != BulletFromAlien.end(); ++it)
      if( m_obstacleManager.CheckIntersection(*it) )
        BulletFromGun.erase(it);
      else if(m_gun.CheckIntersection(*it))
        BulletFromGun.erase(it);
  }

  unsigned int CheckGameState()
  {
    if (m_alienManager.GetLiveAliensCount() <= 0) return 1;     // all aliens defeated - level passed (increased)
    if (m_gun.GetHealth() <= 0) return 2;
    if (m_alienManager.GetLiveAliensCount() == 0) return 3;
    // gun dead once       - level restart (if gun_lives > 0)
    // gun dead last time  - game over     (if gun_lives <= 0)
    //нет пришельцев - уровень пройден

    return 0; // game continued
  }

  void GameStep()
  {
    CheckAllIntersections();
    //еще какие-то действия
    //смена изображения
    RedrawSpace();
  }



  void NewLvlPrepare(size_t const lvl)
  {
    throw std::runtime_error("Not released Space2D::NewLvlPrepare.");
    // configure space class fields for new lvl
  }
private:
  void RedrawSpace()
  {
    throw std::runtime_error("Not released Space2D::RedrawSpace.");
    // redraw game field
  }
  bool CheckObstacleIntersection(Bullet2D& b)
  {

  }

  Gun2D m_gun;                         // one gun            // maybe create manager(for multiplayer game mode)
  Alien2DManager m_alienManager;       // one alien manager  // maybe create something like Factory in it
  Obstacle2DManager m_obstacleManager;
  Bullet2DManager m_bulletManager;     // one bullet manager // maybe create something like Factory in it
  std::list<Obstacle2D> m_obstacles;   // list of obstacles  // maybe create manager and something like Factory in it
};
