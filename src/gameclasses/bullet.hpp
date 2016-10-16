#pragma once

#include "box2d.hpp"
#include "movable.hpp"

class Bullet2D : public Box2D, Movable
{
public:
  // Allow default constructor.
  Bullet2D() = default;

  // Destructor.
  ~Bullet2D() override = default;

  // Constructors with parameters.
  Bullet2D(Point2D leftBottom, Point2D rightTop)
    :Box2D(leftBottom, rightTop)
  {}

  Bullet2D(Point2D leftBottom, Point2D rightTop, float damage, float speed)
    :Box2D(leftBottom, rightTop), m_damage(damage), m_speed(speed)
  {}

  // copy constructor and assignment operator
  Bullet2D(Bullet2D const & obj)
    :Box2D(obj.GetBorder()), m_damage(obj.GetDamage()), m_speed(obj.GetSpeed())
  {}
  Bullet2D & operator = (Bullet2D const & obj)
  {
    if (this == &obj) return *this;
    SetBorder(obj.GetBorder());
    m_damage = obj.GetDamage();
    m_speed = obj.GetSpeed();
    return *this;
  }

  // Getters
  inline float const GetDamage() const { return m_damage; }
  inline float const GetSpeed() const  { return m_speed; }
  // Setters
  inline void SetDamage(float const newDamage) { m_damage = newDamage; }
  inline void SetSpeed(float const newSpeed)   { m_speed = newSpeed; }

  // Capabilities
  void Move() override
  {
    std::runtime_error("Not released.");
  }
private:

  float m_damage = BULLET_DAMAGE_START; // - damage of the Bullet
  float m_speed = BULLET_SPEED_START;   // - move speed
};

