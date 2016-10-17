#pragma once


#include "gameEntity.hpp"
#include "movable.hpp"

class MoveEntity2D : public GameEntity2D, public Movable
{
public:
  // Allow default constructor.
  MoveEntity2D() = default;

  // Destructor.
  ~MoveEntity2D() override = default;

  // Constructors with parameters.
  MoveEntity2D(Point2D const & leftBottom, Point2D const & rightTop)
    :GameEntity2D(leftBottom, rightTop)
  {}

  MoveEntity2D(Point2D const & leftBottom, Point2D const & rightTop, float health, float speedShoot)
    :GameEntity2D(leftBottom, rightTop, health), m_speedShoot(speedShoot)
  { assert(speedShoot >0 ); }

  MoveEntity2D(Box2D newBox, float health, float speedShoot)
    :GameEntity2D(newBox, health), m_speedShoot(speedShoot)
  { assert(speedShoot >0 ); }


  MoveEntity2D & operator = (MoveEntity2D const & obj)
  {
    if (this == &obj) return *this;
    SetBorder(obj.GetBorder());
    m_health = obj.GetHealth();
    m_speedShoot = obj.GetSpeedShoot();
    return *this;
  }

  // Getters
  inline float const GetSpeedShoot() const { return m_speedShoot; }
  // Setters
  inline void SetSpeedShoot(float const newSpeedShoot) { m_speedShoot = newSpeedShoot; }

  // Capabilities
  void Move() override
  {
    throw std::runtime_error("Not released MoveEntity2D::Move.");
  }
protected:
  float m_speedShoot = ALIEN_SPEED_SHOOT_START;   // - shoot speed
};
