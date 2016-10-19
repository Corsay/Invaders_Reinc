#pragma once


#include "LifeGameEntity.hpp"
#include "movable.hpp"

class MoveEntity2D : public LifeGameEntity2D, public Movable
{
public:
  // Allow default constructor.
  MoveEntity2D() = default;

  // Destructor.
  ~MoveEntity2D() override = default;

  // Constructors with parameters.
  MoveEntity2D(Point2D const & leftBottom, Point2D const & rightTop)
    :LifeGameEntity2D(leftBottom, rightTop)
  {}

  MoveEntity2D(Point2D const & leftBottom, Point2D const & rightTop, float health, float Speed)
    :LifeGameEntity2D(leftBottom, rightTop, health), m_Speed(Speed)
  { assert(Speed >0 ); }

  MoveEntity2D(Box2D newBox, float health, float Speed)
    :LifeGameEntity2D(newBox, health), m_Speed(Speed)
  { assert(Speed >0 ); }


  MoveEntity2D & operator = (MoveEntity2D const & obj)
  {
    if (this == &obj) return *this;
    SetBorder(obj.GetBorder());
    m_health = obj.GetHealth();
    m_Speed = obj.GetSpeed();
    return *this;
  }

  // Getters
  inline float const GetSpeed() const { return m_Speed; }
  // Setters
  inline void SetSpeed(float const newSpeed) { m_Speed = newSpeed; }

  bool operator == (MoveEntity2D const & obj)
  {
    return obj.GetBorder() == m_box && obj.GetHealth() == m_health && obj.GetSpeed() == m_Speed;
  }

  // Capabilities
  void Move() override
  {
    throw std::runtime_error("Not released MoveEntity2D::Move.");
  }
protected:
  float m_Speed = ALIEN_SPEED_SHOOT_START;   // - shoot speed
};
