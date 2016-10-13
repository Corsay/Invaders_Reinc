#pragma once

#include "box2d.hpp"

class Alien2D : public Box2D
{
public:
  // Allow default constructor.
  Alien2D() = default;

  // Constructors with parameters.
  Alien2D(Point2D leftBottom, Point2D rightTop, float health, float speedShoot)
    :Box2D(leftBottom, rightTop), m_health(health), m_speedShoot(speedShoot)
  {}

  // no copy constructor and assignment operator
  Alien2D(Alien2D const & clone) = delete;
  void operator = (Alien2D const & clone) = delete;

  // Getters
  inline float const getHealth() const     { return m_health; }
  inline float const getSpeedShoot() const { return m_speedShoot; }
  // Setters
  inline void setHealth(float const new_health)         { m_health = new_health; }
  inline void setSpeedShoot(float const new_speedShoot) { m_health = new_speedShoot; }

  // Capabilities
  void Move()
  {

  }

  // Redefinition
  /*Alien2D operator [] (unsigned int index) const
  {
    if (index > 3 || index < 0) return this;
    return index == 0 ? m_leftBottom : index == 1 ? m_rightTop : index == 2 ? m_health : m_speedShoot;
  }*/
private:

  float m_health = ALIEN_HEALTH_START;            // - health of the alien
  float m_speedShoot = ALIEN_SPEED_SHOOT_START;   // - shoot speed
};
