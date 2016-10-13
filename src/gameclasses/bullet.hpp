#pragma once

#include "box2d.hpp"

class Bullet2D : Box2D
{
public:
  // Allow default constructor.
  Bullet2D() = default;

  // Constructors with parameters.
  Bullet2D(Point2D left_bottom, Point2D right_top, float damage, float speed)
    :Box2D(left_bottom, right_top), m_damage(damage), m_speed(speed)
  {}

  // no copy constructor and assignment operator
  Bullet2D(Bullet2D const & clone) = delete;
  void operator = (Bullet2D const & clone) = delete;

  // Getters
  inline float const GetDamage() const { return m_damage; }
  inline float const GetSpeed() const  { return m_speed; }
  // Setters
  inline void setDamage(float new_damage) { m_damage = new_damage; }
  inline void setSpeed(float new_speed)   { m_speed = new_speed; }

  // Capabilities
  void Move()
  {

  }

  // Redefinition
  /*Bullet2D operator [] (unsigned int index) const
  {
    if (index > 3 || index < 0) return this;
    return index == 0 ? m_leftBottom : index == 1 ? m_rightTop : index == 2 ? m_damage : m_speed;
  }*/
private:

  float m_damage = BULLET_DAMAGE_START; // - damage of the Bullet
  float m_speed = BULLET_SPEED_INC;     // - move speed
};

