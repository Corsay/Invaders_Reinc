#pragma once

#include "box2d.hpp"
#include "movable.hpp"

class Gun2D : public Box2D, Movable
{
public:
  // Allow default constructor.
  Gun2D() = default;

  // Default destructor.
  ~Gun2D() override = default;

  // Constructors with parameters.
  Gun2D(Point2D left_bottom, Point2D right_top, float health, float speedShoot)
    :Box2D(left_bottom, right_top), m_health(health), m_speedShoot(speedShoot)
  {}

  // no copy constructor and assignment operator
  Gun2D(Gun2D const & obj) = delete;
  void operator = (Gun2D const & obj) = delete;

  // Getters
  inline float const GetRate() const       { return m_gunRate; }
  inline float const GetHealth() const     { return m_health; }
  inline float const GetSpeedShoot() const { return m_speedShoot; }
  // Setters
  inline void SetRate(float const new_gunRate)          { m_gunRate = new_gunRate; }
  inline void SetHealth(float const new_health)         { m_health = new_health; }
  inline void SetSpeedShoot(float const new_speedShoot) { m_health = new_speedShoot; }

  // Capabilities
  void Move() override {}
private:

  float m_gunRate = 0;                          // - game rate (from original game) (increment depends on the type of shot down alien)
  float m_health = GUN_HEALTH_START;            // - health of the gun
  float m_speedShoot = GUN_SPEED_SHOOT_START;   // - shoot speed
};
