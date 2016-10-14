#pragma once

#include "box2d.hpp"
#include "movable.hpp"

class Bullet2D : public Box2D, Movable
{
public:
  // Allow default constructor.
  Bullet2D() = default;

  // Default destructor.
  ~Bullet2D() override = default;

  // Constructors with parameters.
  Bullet2D(Point2D left_bottom, Point2D right_top, float damage, float speed)
    :Box2D(left_bottom, right_top), m_damage(damage), m_speed(speed)
  {}

  // no copy constructor and assignment operator
  Bullet2D(Bullet2D const & obj)
    :Box2D(obj.GetBorder()), m_damage(obj.GetDamage()), m_speed(obj.GetSpeed())
  {}
  void operator = (Bullet2D const & obj) = delete;

  // Getters
  inline float const GetDamage() const { return m_damage; }
  inline float const GetSpeed() const  { return m_speed; }
  // Setters
  inline void SetDamage(float new_damage) { m_damage = new_damage; }
  inline void SetSpeed(float new_speed)   { m_speed = new_speed; }

  // Capabilities
  void Move() override {}
private:

  float m_damage = BULLET_DAMAGE_START; // - damage of the Bullet
  float m_speed = BULLET_SPEED_INC;     // - move speed
};

