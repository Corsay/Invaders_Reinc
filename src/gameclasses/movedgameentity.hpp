#pragma once

#include "lifegameentity.hpp"

class MovedGameEntity2D : public LifeGameEntity2D
{
public:
  // Allow default constructor.
  MovedGameEntity2D() = default;

  // Destructor.
  virtual ~MovedGameEntity2D() = default;

  // Constructors with parameters.
  MovedGameEntity2D(Point2D const & leftBottom, Point2D const & rightTop)
    :LifeGameEntity2D(leftBottom, rightTop)
  {}

  MovedGameEntity2D(Point2D const & leftBottom, Point2D const & rightTop, float health)
    :LifeGameEntity2D(leftBottom, rightTop, health)
  {}

  MovedGameEntity2D(Point2D const & leftBottom, Point2D const & rightTop, float health, float speed)
    :LifeGameEntity2D(leftBottom, rightTop, health), m_speed(speed)
  {
    if (speed <= 0) throw std::out_of_range("Speed must be more then ZERO!");
  }

  MovedGameEntity2D(Box2D const & newBox, float health)
    :LifeGameEntity2D(newBox, health)
  {}

  MovedGameEntity2D(Box2D const & newBox, float health, float speed)
    :LifeGameEntity2D(newBox, health), m_speed(speed)
  {
    if (speed <= 0) throw std::out_of_range("Speed must be more then ZERO!");
  }

  MovedGameEntity2D(LifeGameEntity2D const & newLifeEntity, float speed)
    :LifeGameEntity2D(newLifeEntity), m_speed(speed)
  {
    if (speed <= 0) throw std::out_of_range("Speed must be more then ZERO!");
  }

  // Assignment operator
  MovedGameEntity2D & operator = (MovedGameEntity2D const & obj)
  {
    if (this == &obj) return *this;
    SetMovedEntity(obj.GetMovedEntity());
    return *this;
  }


  // Getters
  inline MovedGameEntity2D GetMovedEntity() const { return *this; }
  inline float const GetSpeed() const { return m_speed; }

  // Setters
  inline void SetMovedEntity(MovedGameEntity2D const & newMovedEntity)
  {
    SetLifeEntity(newMovedEntity.GetLifeEntity());
    m_speed = newMovedEntity.GetSpeed();
  }
  inline void SetSpeed(float const newSpeed) { m_speed = newSpeed; }


  // Logical operators
  bool operator == (MovedGameEntity2D const & obj) const
  {
    return obj.GetBox() == GetBox() && obj.GetHealth() == GetHealth() && obj.GetSpeed() == m_speed;
  }


  // Capabilities
  virtual void Move(size_t horiz, size_t vert)
  {
    throw std::runtime_error("Not released MoveEntity2D::Move.");
  }


  // Redefinition
  friend std::ostream & operator << (std::ostream & os, MovedGameEntity2D const & obj)
  {
    os << "MovedGameEntity2D {" << obj.GetLifeEntity() << ", Speed: " << obj.GetSpeed() << "}";
    return os;
  }

private:
  float m_speed = DEFAULT_SPEED;   // - default shoot speed
};
