#pragma once

#include "box.hpp"

class Bullet2D : public Box2D
{
public:
  // Allow default constructor.
  Bullet2D() = default;

  // Constructors with parameters.
  // need


  // Constructor with initialization list.
  // need or not (?!)


  // Copy constructor
  // can be useful


  // Move constructor
  // not need


  // Getters
  // all getters for new fields


  // Setters
  // all settsers for new fields


  // Logical operators
  // don't know need or not (?!)


  // Assignment operator.
  // can be useful =


  // Move operator
  // not need


  // Math operations
  // don't know need or not (?!)


  // Capabilities


  // Redefinition
  // square brackets
private:

  float m_speed = 1.0f;   // - speed
};

#pragma once
#include "box2d.hpp"

enum BulletType{First, Second, Third};

class Bullet2D : public Box2D
{
public:
    // Constructors with parameters.
    Bullet2D(Point2D left_bottom, Point2D right_top, BulletType type)
      :Box2D(left_bottom, right_top)
      {
        m_damage = BULLET_DAMAGE_START + m_bulletType * BULLET_DAMAGE_INC;
        m_speed = BULLET_SPEED_START + m_bulletType * BULLET_SPEED_INC;
        //или любые другие формулы
      }
  //no copy
  Bullet2D(Bullet2D const & clone) = delete;
  void operator=(Bullet2D const & clone) = delete;

  // Constructor with initialization list.
  // need or not (?!)
  //довольно странно определять пришельца кучкой цифр
  //надеюсь не придется так делать в проекте

  // Copy constructor
  // can be useful
  //тогда пришельцы будут иметь одинаковые координаты, т.е. лежать друг на друге

  // Move constructor
  // not need


  // Getters
  inline float getDamage() { return m_damage; }
  inline float getSpeed { return m_speed; }
  // Setters
  inline void setDamage(float new_damage) { m_Damage = new_Damage; }


  // Logical operators
  // don't know need or not (?!)


  // Math operations
  // don't know need or not (?!)


  // Capabilities
  void Shoot(){}



private:


  BulletType m_BulletType=First;
  float m_damage = BULLET_DAMAGE_START; // - Damage of the Bullet
  float m_speed = BULLET_SPEED_INC;   // - shoot speed
};

