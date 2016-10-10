#pragma once

#include "box2d.hpp"

class Gun2D : public Box2D
{
public:
  // Allow default constructor.
  Gun2D() = default;

  // Constructors with parameters.
  Gun2D(Point2D left_bottom, Point2D right_top, float health, float speedShoot)
    :Box2D(left_bottom, right_top), m_health(health), m_speedShoot(speedShoot)
  {}

  // no copy constructor and assignment operator
  Gun2D(Gun2D const & clone) = delete;
  void operator = (Gun2D const & clone) = delete;

  // Getters
  inline float const getHealth() const { return m_health; }
  inline float const getSpeedShoot() const { return m_speedShoot; }
  // Setters
  inline void setHealth(float const new_health) { m_health = new_health; }
  inline void setSpeedShoot(float const new_speedShoot) { m_health = new_speedShoot; }

  // Logical operators
  // don't know need or not (?!)


  // Math operations
  // don't know need or not (?!)


  // Capabilities
  void Shoot(){}


  // Redefinition
  // square brackets
private:
  // Box2D
  // leftBottom() - left bottom point of the gun
  // rightTop()   - right top point of the gun
  // left()       - left/right/top/bottom border of the gun, need to be <= space borders (how to get it? - maybe control all game from Space class)

  // IsAlive == false - defeat
  // -> destroy gun

  // GunType m_gunType=First;
  float m_health = GUN_HEALTH_START; // - health of the gun
  float m_speedShoot = GUN_SPEED_SHOOT_START;   // - shoot speed
};
