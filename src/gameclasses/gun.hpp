#pragma once

#include "moveEntity.hpp"

class Gun2D final : public MoveEntity2D
{
public:
  // Allow default constructor.
  Gun2D()
  {GunSetStartValue();}

  // Destructor.
  ~Gun2D() override = default;

  // Constructors with parameters.
  Gun2D(Point2D const & leftBottom, Point2D const & rightTop)
    :MoveEntity2D(leftBottom, rightTop)
  {GunSetStartValue();}

  Gun2D(Point2D const & leftBottom, Point2D const & rightTop, size_t lives, float health, float Speed)
    :MoveEntity2D(leftBottom, rightTop, health, Speed), m_lives(lives)
  {}

  // copy constructor and assignment operator
  Gun2D(Gun2D const & obj)
    :MoveEntity2D(obj.GetBorder(), obj.GetHealth(), obj.GetSpeed()), m_lives(obj.GetLives())
  {}

  Gun2D & operator = (Gun2D const & obj)
  {
    if (this == &obj) return *this;
    SetBorder(obj.GetBorder());
    m_lives = obj.GetLives();
    SetHealth(obj.GetHealth());
    SetSpeed(obj.GetSpeed());
    return *this;
  }

  // Getters
  inline size_t const GetLives() const     { return m_lives; }
  inline float const GetRate() const       { return m_gunRate; }
  // Setters
  inline void SetLives(size_t const newLives)          { m_lives = newLives; }
  inline void SetRate(float const newGunRate)          { m_gunRate = newGunRate; }

private:
  inline void GunSetStartValue()
  {
    SetHealth(GUN_HEALTH_START);
    SetSpeed(GUN_SPEED_SHOOT_START);
  }
  size_t m_lives = GUN_LIVES_START;             // - default gun lives count
  float m_gunRate = 0;                          // - game rate (from original game) (increment depends on the type of shot down alien)
};
