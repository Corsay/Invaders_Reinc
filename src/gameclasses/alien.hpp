#pragma once
#include "box2d.hpp"

enum AlienType{First, Second, Third};

class Alien2D : public Box2D
{
public:
    // Constructors with parameters.
    Alien2D(Point2D left_bottom, Point2D right_top, AlienType type)
      :Box2D(left_bottom, right_top)
      {
        m_health = ALIEN_HEALTH_START + m_alienType * ALIEN_HEALTH_INC;
        m_speedShoot = ALIEN_SPEED_SHOOT_START + m_alienType * ALIEN_SPEED_SHOOT_INC;
        //или любые другие формулы
      }
  //no copy
  Alien2D(Alien2D const & clone) = delete;
  void operator=(Alien2D const & clone) = delete;

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
  float m_health = ALIEN_HEALTH_START; // - health of the alien
  float m_speedShoot = ALIEN_SPEED_SHOOT_START;   // - shoot speed
};
