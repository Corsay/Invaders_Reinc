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
  inline float const getDamage() const { return m_damage; }
  inline float const getSpeed() const { return m_speed; }
  // Setters
  inline void setDamage(float new_damage) { m_damage = new_damage; }
  inline void setSpeed(float new_speed) { m_speed = new_speed; }

  // Logical operators
  // don't know need or not (?!)


  // Math operations
  // don't know need or not (?!)


  // Capabilities
  void Fly(){}


  // Redefinition
  // square brackets
private:

  //BulletType m_BulletType=First;
  float m_damage = BULLET_DAMAGE_START; // - Damage of the Bullet
  float m_speed = BULLET_SPEED_INC;   // - fly speed
};

