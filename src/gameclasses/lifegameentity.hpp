#pragma once

#include <cassert>
#include "gameentity.hpp"
#include "factory.hpp"

class LifeGameEntity2D : public GameEntity2D
{
public:
  // Allow default constructor.
  LifeGameEntity2D() = default;

  // Destructor.
  virtual ~LifeGameEntity2D() = default;

  // Constructors with parameters.
  LifeGameEntity2D(Point2D const & leftBottom, Point2D const & rightTop)
    :GameEntity2D(Box2D{leftBottom, rightTop})
  {}

  LifeGameEntity2D(Point2D const & leftBottom, Point2D const & rightTop, float health)
    :GameEntity2D(Box2D{leftBottom, rightTop}), m_health(health)
  {
    if (health <= 0) throw std::out_of_range("Health must be more then ZERO!");
  }

  LifeGameEntity2D(Box2D const & newBox, float health)
    :GameEntity2D(newBox), m_health(health)
  {
    if (health <= 0) throw std::out_of_range("Health must be more then ZERO!");
  }

  LifeGameEntity2D(GameEntity2D const & newEntity, float health)
    :GameEntity2D(newEntity), m_health(health)
  {
    if (health <= 0) throw std::out_of_range("Health must be more then ZERO!");
  }

  // Assignment operator
  LifeGameEntity2D & operator = (LifeGameEntity2D const & obj)
  {
    if (this == &obj) return *this;
    SetLifeEntity(obj.GetLifeEntity());
    return *this;
  }


  // Getters
  inline LifeGameEntity2D GetLifeEntity() const { return *this; }
  inline float GetHealth() const { return m_health; }
  // Setters
  inline  void SetLifeEntity(LifeGameEntity2D const & newLifeEntity)
  {
    SetEntity(newLifeEntity.GetEntity());
    m_health = newLifeEntity.GetHealth();
  }
  inline void SetHealth(float const newHealth)
  {
    if(newHealth <= 0)
      m_health = 0;
    else
      m_health = newHealth;
  }


  // Logical operators
  bool operator == (LifeGameEntity2D const & obj) const
  {
    return obj.GetBox() == GetBox() && obj.GetHealth() == m_health;
  }


  // Redefinition
  friend std::ostream & operator << (std::ostream & os, LifeGameEntity2D const & obj)
  {
    os << "LifeGameEntity2D {" << obj.GetEntity() << ", Health: " << obj.GetHealth() << "}";
    return os;
  }

private:
  float m_health = DEFAULT_HEALTH; // default health
};
