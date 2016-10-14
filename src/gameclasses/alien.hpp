#pragma once

#include "box2d.hpp"
#include "movable.hpp"

class Alien2D : public Box2D, Movable
{
public:
  // Allow default constructor.
  Alien2D() = default;

  // Default destructor.
  ~Alien2D() override = default;

  // Constructors with parameters.
  Alien2D(Point2D leftBottom, Point2D rightTop, float health, float speedShoot)
    :Box2D(leftBottom, rightTop), m_health(health), m_speedShoot(speedShoot)
  {}

  // no copy constructor and assignment operator
  Alien2D(Alien2D const & obj) = delete;
  void operator = (Alien2D const & obj) = delete;

  // Getters
  inline float const GetHealth() const     { return m_health; }
  inline float const GetSpeedShoot() const { return m_speedShoot; }
  // Setters
  inline void SetHealth(float const new_health)         { m_health = new_health; }
  inline void SetSpeedShoot(float const new_speedShoot) { m_health = new_speedShoot; }

  // Capabilities
  void Move() override {}
private:

  float m_health = ALIEN_HEALTH_START;            // - health of the alien
  float m_speedShoot = ALIEN_SPEED_SHOOT_START;   // - shoot speed
};
