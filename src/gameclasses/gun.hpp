#pragma once

#include "box2d.hpp"
#include "movable.hpp"

class Gun2D : public Box2D, public Movable
{
public:
  // Allow default constructor.
  Gun2D() = default;

  // Destructor.
  ~Gun2D() override = default;

  // Constructors with parameters.
  Gun2D(Point2D const & leftBottom, Point2D const & rightTop)
    :Box2D(leftBottom, rightTop)
  {}

  Gun2D(Point2D const & leftBottom, Point2D const & rightTop, size_t lives, float health, float speedShoot)
    :Box2D(leftBottom, rightTop), m_lives(lives), m_health(health), m_speedShoot(speedShoot)
  {}

  // copy constructor and assignment operator
  Gun2D(Gun2D const & obj)
    :Box2D(obj.GetBorder()), m_lives(obj.GetLives()), m_health(obj.GetHealth()), m_speedShoot(obj.GetSpeedShoot())
  {}

  Gun2D & operator = (Gun2D const & obj)
  {
    if (this == &obj) return *this;
    SetBorder(obj.GetBorder());
    m_lives = obj.GetLives();
    m_health = obj.GetHealth();
    m_speedShoot = obj.GetSpeedShoot();
    return *this;
  }

  // Getters
  inline size_t const GetLives() const     { return m_lives; }
  inline float const GetRate() const       { return m_gunRate; }
  inline float const GetHealth() const     { return m_health; }
  inline float const GetSpeedShoot() const { return m_speedShoot; }
  // Setters
  inline void SetLives(size_t const newLives)          { m_lives = newLives; }
  inline void SetRate(float const newGunRate)          { m_gunRate = newGunRate; }
  inline void SetHealth(float const newHealth)         { m_health = newHealth; }
  inline void SetSpeedShoot(float const newSpeedShoot) { m_speedShoot = newSpeedShoot; }

  // Capabilities
  void Move() override
  {
    throw std::runtime_error("Not released Gun2D::Move.");
  }
private:

  size_t m_lives = GUN_LIVES_START;             // - default gun lives count
  float m_gunRate = 0;                          // - game rate (from original game) (increment depends on the type of shot down alien)
  float m_health = GUN_HEALTH_START;            // - health of the gun
  float m_speedShoot = GUN_SPEED_SHOOT_START;   // - shoot speed
};
