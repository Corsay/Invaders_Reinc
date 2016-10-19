#pragma once

#include "moveEntity.hpp"
#include "movable.hpp"
#include <cassert>

class Bullet2D final : public MoveEntity2D
{
public:
  // Allow default constructor.
    Bullet2D(){ Seter(); }

  // Destructor.
  ~Bullet2D() override = default;

  // Constructors with parameters.
  Bullet2D(Point2D const & leftBottom, Point2D const & rightTop)
    :MoveEntity2D(leftBottom, rightTop)
  { Seter(); }

  Bullet2D(Point2D const & leftBottom, Point2D const & rightTop, float damage, float speed)
    :MoveEntity2D(leftBottom, rightTop, damage, speed)
  {
    assert(m_Speed > 0);
    assert(m_health > 0);
  }

  // copy constructor and assignment operator
  Bullet2D(Bullet2D const & obj)
    :MoveEntity2D(obj.GetBorder(), obj.GetHealth(), obj.GetSpeed())
  {
    assert(m_Speed > 0);
    assert(m_health > 0);
  }

  Bullet2D & operator = (Bullet2D const & obj)
  {
    if (this == &obj) return *this;
    SetBorder(obj.GetBorder());
    m_health = obj.GetHealth();
    m_Speed = obj.GetSpeed();
    return *this;
  }

  // Capabilities
  void Move() override
  {
    throw std::runtime_error("Not released Bullet2D::Move.");
  }
private:
  Seter()
  {
    m_health = BULLET_DAMAGE_START;
    m_Speed = BULLET_SPEED_START;
  }
};

