#pragma once
#include "box2d.hpp"
enum AlienType{First, Second, Third};

class Alien2D : public Box2D
{
public:
    // Allow default constructor.
    Alien2D() = default;

    // Constructors with parameters.
    Alien2D(Point2D left_bottom, Point2D right_top, AlienType type)
      :Box2D(left_bottom, right_top)
      {
        m_health = 50.0f + m_alienType*50.0f;
        m_speedShoot = 1.0f + m_alienType*0.5f;
        //или любые другие формулы
      }
  //no copy
  Alien2D(Alien2D clone) = delete;
  void operator=(Alien2D clone) = delete;

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
  inline float getHealth() { return m_health; }
  inline float getSpeedShoot() { return m_speedShoot; }
  // Setters
  inline void setHealth(float new_health) { m_health = new_health; }
  inline void setSpeedShoot(float new_speedShoot) { m_health = new_speedShoot; }


  // Logical operators
  // don't know need or not (?!)


  // Math operations
  // don't know need or not (?!)


  // Capabilities
  void Shoot(){}



private:


  AlienType m_alienType=First;
  float m_health = 50.0f; // - health of the alien
  float m_speedShoot = 1.0f;   // - shoot speed
};
