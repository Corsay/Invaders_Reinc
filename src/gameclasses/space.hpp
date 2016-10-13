#pragma once

#include "gun.hpp"
#include "alienmanager.hpp"
#include "bulletmanager.hpp"
#include "obstacle.hpp"

enum EntitiesTypes{Gun, Alien, Obstacle};

class Space2D : public Box2D
{
public:
  // Allow default constructor.
  Space2D() = default;

  // Constructors with parameters.
  Space2D(Point2D left_bottom, Point2D right_top)
    :Box2D(left_bottom, right_top)
  {
    // initialize all inside fields
  }

  // Getters
  // all getters for new fields


  // Setters
  // all setters for new fields


  // Capabilities
  // при выстреле вызывается m_bulletManager.NewAlienBullet(m_gun.Shoot());
  // то есть пуля передается в мэнджер
  // тип пули фомируется на основе типа пушки/пришельца до мэнеджера
  // каждую n-ую часть секунды проверяются пуди на пересечение

  void AlienShoot()
  {
    Alien2D alien = m_alienManager.GetShooter(m_gun.getBorder());
    Point2D start = alien.GetCenter();
    start.setY(alien.top());
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
    size_t countOfGunBullets = m_bulletManager.getCountOfGunBullets();
    size_t countOfAlienBullets = m_bulletManager.getCountOfAlienBullets();
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
    m_bulletManager.BulletsMove();
    // check intersections after bullets move
    CheckIntersections();
    // move aliens
    m_alienManager.AliensMove(this->GetBorder());  // AI move aliens
    // check intersections because aliens moved and it can intersect with bullets
    CheckIntersections();

    // shoot by aliens (I thing what this must be in timer(AI param))

    // check game state
    unsigned int state = CheckGameState();  // return 0 -> allright game continued, else restart or game over
    if (state);
    // in the end of game step redraw game field
    RedrawSpace();
  }

  void RedrawSpace()
  {
    // redraw game field
  }

  // function for input processing:............
  // check m_gun state
  // check m_alienManager state
  // move gun (send command to function in gun)
  // move aliens (standart moving or boss configuration moving) (send command to function in alienManager)
  // move bullets (send command to function in bulletManager)

  /*
   * how can check bullets intersection with obstacle/gun/alien variant:
   send m_bulletManager (if it state return nullptr(zero bullets strated))
   too functions in m_obstacles (if it != nullptr) and m_alienManager (if it != nullptr) (if it == nullptr -> lvl passed)
  */

  // functions of frame update:...............
  // redraw

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
  Obstacle2D m_obstacles;            // vector of obstacles
};
