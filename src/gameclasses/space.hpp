#pragma once

#include "gameentity.hpp"
#include "gun.hpp"
#include "alienmanager.hpp"
#include "bulletmanager.hpp"
#include "obstacle.hpp"
#include "factory.hpp"

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
  void GunMove()  // if add manager this code can be replaced, because later added keypress
  {
    throw std::runtime_error("Not released Space2D::GunMove.");
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

  void CheckIntersections()
  {
    // check count of bullets in bulletManager
    size_t countOfGunBullets = m_bulletManager.GetCountOfGunBullets();
    size_t countOfAlienBullets = m_bulletManager.GetCountOfAlienBullets();
    // if count of alienBullets > 0 checkIntersections with Gun and Obstacles
    if (countOfAlienBullets > 0)
    {
      throw std::runtime_error("Not full released Space2D::CheckIntersections(WithGun).");
      // send gun and all obstacles to functions in m_bulletManager
    }
    // if count of gunBullets > 0 checkIntersections with Aliens and Obstacles
    if (countOfGunBullets > 0)
    {
      throw std::runtime_error("Not full released Space2D::CheckIntersections(WithAlien).");
      // send aliens and all obstacles to functions in m_bulletManager
    }
  }

  unsigned int CheckGameState()
  {
    if (m_alienManager.GetLiveAliensCount() <= 0) return 1;     // all aliens defeated - level passed (increased)
    if (m_gun.GetHealth() <= 0) return 2;
    // gun dead once       - level restart (if gun_lives > 0)
    // gun dead last time  - game over     (if gun_lives <= 0)

    return 0; // game continued
  }

  void GameStep()
  {
    throw std::runtime_error("Not released Space2D::GameStep.");
  }

  void RedrawSpace()
  {
    throw std::runtime_error("Not released Space2D::RedrawSpace.");
    // redraw game field
  }

  void NewLvlPrepare(size_t const lvl)
  {
    throw std::runtime_error("Not released Space2D::NewLvlPrepare.");
    // configure space class fields for new lvl
  }

private:
  void FillObcstaclesList(size_t const count) // if add obstacles manager this code can be replaced
  {
    throw std::runtime_error("Not released Space2D::FillObcstaclesList.");
  }

  Gun2D m_gun;                       // one gun            // maybe create manager(for multiplayer game mode)
  Alien2DManager m_alienManager;     // one alien manager  // maybe create something like Factory in it
  Bullet2DManager m_bulletManager;   // one bullet manager // maybe create something like Factory in it
  std::list<Obstacle2D> m_obstacles; // list of obstacles  // maybe create manager and something like Factory in it
};
