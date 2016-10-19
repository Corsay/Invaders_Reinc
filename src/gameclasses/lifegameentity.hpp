#pragma once

#include <cassert>
#include "gameentity.hpp"

class LifeGameEntity2D : public GameEntity2D
{
public:
  // Allow default constructor.
  LifeGameEntity2D() = default;

  // Destructor.
  ~LifeGameEntity2D() = default;

  // Constructors with parameters.
  LifeGameEntity2D(Point2D const & leftBottom, Point2D const & rightTop)
    :GameEntity2D(Box2D{leftBottom, rightTop})
  {}

  LifeGameEntity2D(Point2D const & leftBottom, Point2D const & rightTop, float health)
    :GameEntity2D(Box2D{leftBottom, rightTop}), m_health(health)
  {
    assert(health > 0 && "Health must be more then ZERO!");
  }

  LifeGameEntity2D(Box2D const & newBox, float health)
    :GameEntity2D(newBox), m_health(health)
  {
    assert(health > 0 && "Health must be more then ZERO!");
  }

  LifeGameEntity2D(GameEntity2D const & newEntity, float health)
    :GameEntity2D(newEntity), m_health(health)
  {
    assert(health > 0 && "Health must be more then ZERO!");
  }

  // Getters
  inline LifeGameEntity2D GetLifeEntity() const { return LifeGameEntity2D{ GetEntity(), m_health }; }
  inline float GetHealth() const { return m_health; }
  // Setters
  inline  void SetLifeEntity(LifeGameEntity2D const & newLifeEntity)
  {
    SetEntity(newLifeEntity.GetEntity());
    m_health = newLifeEntity.GetHealth();
  }
  inline void SetHealth(float const newHealth) { m_health = newHealth; }

  // Logical operators
  bool operator == (LifeGameEntity2D const & obj)
  {
    return obj.GetBox() == GetBox() && obj.GetHealth() == m_health;
  }

private:
  float m_health = DEFAULT_HEALTH; // default health
};
