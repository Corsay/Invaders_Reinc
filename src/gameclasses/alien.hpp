#pragma once

#include "box2d.hpp"
#include "movable.hpp"

class Alien2D : public Box2D, public Movable
{
public:
  // Allow default constructor.
  Alien2D() = default;

  // Destructor.
  ~Alien2D() override = default;

  // Constructors with parameters.
  Alien2D(Point2D const & leftBottom, Point2D const & rightTop)
    :Box2D(leftBottom, rightTop)
  {}

  Alien2D(Point2D const & leftBottom, Point2D const & rightTop, float health, float speedShoot)
    :Box2D(leftBottom, rightTop), m_health(health), m_speedShoot(speedShoot)
  {}

  // copy constructor and assignment operator
  Alien2D(Alien2D const & obj)
    :Box2D(obj.GetBorder()), m_health(obj.GetHealth()), m_speedShoot(obj.GetSpeedShoot())
  {}

  Alien2D & operator = (Alien2D const & obj)
  {
    if (this == &obj) return *this;
    SetBorder(obj.GetBorder());
    m_health = obj.GetHealth();
    m_speedShoot = obj.GetSpeedShoot();
    return *this;
  }

  // Getters
  inline float const GetHealth() const     { return m_health; }
  inline float const GetSpeedShoot() const { return m_speedShoot; }
  // Setters
  inline void SetHealth(float const newHealth)         { m_health = newHealth; }
  inline void SetSpeedShoot(float const newSpeedShoot) { m_speedShoot = newSpeedShoot; }

  // Capabilities
  void Move() override
  {
    throw std::runtime_error("Not released Alien2D::Move.");
  }
private:

  float m_health = ALIEN_HEALTH_START;            // - health of the alien
  float m_speedShoot = ALIEN_SPEED_SHOOT_START;   // - shoot speed
};
