#pragma once

#include "bullet.hpp"
#include <list>

class Bullet2DManager
{
public:
  // Allow default constructor.
  Bullet2DManager() = default;

  // Constructors with parameters.
  // need


  // Getters
  // all getters for new fields


  // Setters
  // all settsers for new fields


  // Logical operators
  // don't know need or not (?!)


  // Math operations
  // don't know need or not (?!)


  // Capabilities
  CreateAlienBullet(Point2D start)
  {
      m_fromAlien.push_back
      (
        Bullet2D
        {
          Point2D{start.x()-BULLET_WIDTH/2, start.y()-BULLET_HEIGHT},
          Point2D{start.x()+BULLET_WIDTH/2, start.y()+BULLET_HEIGHT},
          BULLET_DAMAGE_START,
          BULLET_SPEED_START
        }
      );
  }
  CreateGunBullet(Point2D start)
  {
      m_fromGun.push_back
      (
        Bullet2D
        {
          Point2D{start.x()-BULLET_WIDTH/2, start.y()-BULLET_HEIGHT},
          Point2D{start.x()+BULLET_WIDTH/2, start.y()+BULLET_HEIGHT},
          BULLET_DAMAGE_START,
          BULLET_SPEED_START
        }
      );
  }

  // Redefinition
  // square brackets
private:
    list<Bullet2D> m_fromAlien;
    list<Bullet2D> m_fromGun;
};
