#pragma once

#include "gun.hpp"
#include "alienmanager.hpp"
#include "bulletmanager.hpp"
#include "obstacle.hpp"

enum EntitiesTypes{Gun, Alien, Obstacle};

class Space2D final : public Box2D
{
public:
  // Allow default constructor.
  Space2D() = default;

  // Default destructor.
  ~Space2D() = default;

  // Constructors with parameters.
  Space2D(Point2D left_bottom, Point2D right_top)
    :Box2D(left_bottom, right_top)
  {}

  // Capabilities
  void AlienShoot()
  {
    Alien2D * alien = m_alienManager.GetShooter(m_gun.GetBorder());
    Point2D start = alien->GetCenter();
    start.SetY(alien->top());
    Bullet2D bullet(
      Point2D {start.x() - BULLET_WIDTH / 2, start.y() - BULLET_HEIGHT / 2},
      Point2D {start.x() + BULLET_WIDTH / 2, start.y() + BULLET_HEIGHT / 2},
      BULLET_DAMAGE_START,
      BULLET_SPEED_START
    );
    m_bulletManager.NewBullet(bullet, Alien);
  }

  void GunMove() // keypress
  {

  }

  void GunShoot() // keypress
  {
    Point2D start = m_gun.GetCenter();
    start.SetY(m_gun.top());
    Bullet2D bullet(
      Point2D {start.x() - BULLET_WIDTH / 2, start.y() - BULLET_HEIGHT / 2},
      Point2D {start.x() + BULLET_WIDTH / 2, start.y() + BULLET_HEIGHT / 2},
      BULLET_DAMAGE_START,
      BULLET_SPEED_START
    );
    m_bulletManager.NewBullet(bullet, Gun);
  }

  void CheckIntersections()
  {
    // check count of bullets in bulletManager
    size_t countOfGunBullets = m_bulletManager.GetCountOfGunBullets();
    size_t countOfAlienBullets = m_bulletManager.GetCountOfAlienBullets();
    // if count of alienBullets > 0 checkIntersections with Gun and Obstacles
    if (countOfAlienBullets > 0)
    {
        // send gun and all obstacles to function in m_bulletManager
    }
    // if count of gunBullets > 0 checkIntersections with Aliens and Obstacles
    if (countOfGunBullets > 0)
    {
        // send aliens and all obstacles to function in m_bulletManager
    }
  }

  unsigned int CheckGameState()
  {
    if (m_alienManager.GetLiveAliensCount() <= 0) return 1;     // all aliens defeated - level passed
    if (m_gun.GetHealth() <= 0) return 2;
    // gun dead once       - level restart (if gun_lives > 0)   // THIS INFORMATION(gun_lives) CONTAINS NOT HERE AND NOT IN GUN
    // gun dead last time  - game over     (if gun_lives <= 0)  // THIS INFORMATION(gun_lives) CONTAINS NOT HERE AND NOT IN GUN

    return 0; // game continued
  }

  void GameStep()
  {
    // move bullets
    m_bulletManager.BulletsMove(this->GetBorder());
    // check intersections after bullets move
    CheckIntersections();
    // move aliens
    m_alienManager.AliensMove(this->GetBorder());  // AI move aliens
    // check intersections because aliens moved and it can intersect with bullets
    CheckIntersections();

    // shoot by aliens (I thing what this must be in timer(AI param))

    // check game state
    unsigned int state = CheckGameState();  // return 0 -> allright game continued, else restart or game over
    if (state) {}
    // in the end of game step redraw game field
    RedrawSpace();
  }

  void RedrawSpace()
  {
    // redraw game field
  }
private:

  // Box2D
  // leftBottom() - left bottom point of the gun
  // rightTop()   - right top point of the gun
  // left()       - left/right/top/bottom border of all game space, if one of the next objects leave space(like bullets), it destroy

  // m_gun == nullptr -> level failed (game over or restart level, because gun was destroyed by alien)
  // -> destroy Space
  Gun2D m_gun;                       // one gun
  // m_alienManager == nullptr -> level passed (go to the next level or game succesfull finished, because all aliens on current level destroyed)
  // -> destroy space
  Alien2DManager m_alienManager;     // one alien manager
  // m_bulletManager == nullptr -> incorrect work of the classes
  // -> destroyed only then destroyed space
  Bullet2DManager m_bulletManager;   // one bullet manager
  // m_obstacle == nullptr - destroyed all obstacles
  // -> nothing to do
  std::list<Obstacle2D> m_obstacles; // list of obstacles
};
