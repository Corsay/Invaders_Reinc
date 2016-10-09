#pragma once
#include "box2d.hpp"

enum GunType{First, Second, Third};

class Gun2D : public Box2D
{
public:
    // Constructors with parameters.
    Gun2D(Point2D left_bottom, Point2D right_top, GunType type)
      :Box2D(left_bottom, right_top)
      {
        m_health = GUN_HEALTH_START + m_gunType * GUN_HEALTH_INC;
        m_speedShoot = GUN_SPEED_SHOOT_START + m_gunType * GUN_SPEED_SHOOT_INC;
        //или любые другие формулы
      }
  //no copy
  Gun2D(Gun2D clone) = delete;
  void operator=(Gun2D clone) = delete;

  // Constructor with initialization list.
  // need or not (?!)
  //довольно странно определять пришельца кучкой цифр
  //надеюсь не придется так делать в проекте

  // Copy constructor
  // can be useful
  //тогда пришельцы будут иметь одинаковые координаты, т.е. лежать друг на друге

  // Move constructor
  // not need


  // Getters
  inline float getHealth() { return m_health; }
  inline float getSpeedShoot() { return m_speedShoot; }
  // Setters
  inline void setHealth(float new_health) { m_health = new_health; }
  inline void setSpeedShoot(float new_speedShoot) { m_health = new_speedShoot; }


  // Logical operators
  // don't know need or not (?!)


  // Math operations
  // don't know need or not (?!)


  // Capabilities
  void Shoot(){}



private:
  // Box2D
  // leftBottom() - left bottom point of the gun
  // rightTop()   - right top point of the gun
  // left()       - left/right/top/bottom border of the gun, need to be <= space borders (how to get it? - maybe control all game from Space class)
  // GameEntity
  // IsAlive == false - defeat
  // -> destroy gun

  GunType m_gunType=First;
  float m_health = GUN_HEALTH_START; // - health of the gun
  float m_speedShoot = GUN_SPEED_SHOOT_START;   // - shoot speed
};
