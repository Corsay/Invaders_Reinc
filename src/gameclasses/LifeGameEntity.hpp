#pragma once

#include <cassert>
#include "gameEntity.hpp"

class LifeGameEntity2D : public GameEntity2D
{
public:
  // Allow default constructor.
  LifeGameEntity2D() = default;

  // Destructor.
  ~LifeGameEntity2D() = default;

  // Constructors with parameters.
  LifeGameEntity2D(Point2D const & leftBottom, Point2D const & rightTop)
      :GameEntity2D( Box2D{ leftBottom, rightTop } )
  {}

  LifeGameEntity2D(Point2D const & leftBottom, Point2D const & rightTop, float health)
    :GameEntity2D( Box2D{ leftBottom, rightTop } ), m_health(health)
  { assert(health > 0); }

  LifeGameEntity2D(Box2D newBox, float health)
    :GameEntity2D(newBox), m_health(health)
  { assert(health > 0); }


  // Getters
  inline float GetHealth() const { return m_health; }
  // Setters
  inline void SetHealth(float const newHealth) { m_health = newHealth; }

  bool operator == (LifeGameEntity2D const & obj)
  {
    return obj.GetBorder() == m_box && obj.GetHealth() == m_health;
  }

  // Capabilities
protected:
  float m_health = ALIEN_HEALTH_START;            // - health of the alien
};
