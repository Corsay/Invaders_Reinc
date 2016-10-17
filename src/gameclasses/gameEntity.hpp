#pragma once

#include <cassert>
#include "box2d.hpp"

class GameEntity2D : public Box2D
{
public:
  // Allow default constructor.
  GameEntity2D() = default;

  // Destructor.
  ~GameEntity2D() = default;

  // Constructors with parameters.
  GameEntity2D(Point2D const & leftBottom, Point2D const & rightTop)
    :Box2D(leftBottom, rightTop)
  {}

  GameEntity2D(Point2D const & leftBottom, Point2D const & rightTop, float health)
    :Box2D(leftBottom, rightTop), m_health(health)
  { assert(health > 0); }

  GameEntity2D(Box2D newBox, float health)
    :Box2D(newBox), m_health(health)
  { assert(health > 0); }

  // Getters
  inline float const GetHealth() const     { return m_health; }
  // Setters
  inline void SetHealth(float const newHealth)         { m_health = newHealth; }

  // Capabilities
protected:
  float m_health = ALIEN_HEALTH_START;            // - health of the alien
};
