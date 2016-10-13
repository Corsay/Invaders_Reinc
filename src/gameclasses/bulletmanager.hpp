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


  // Logical operators
  // don't know need or not (?!)


  // Math operations
  // don't know need or not (?!)


  // Capabilities
  NewAlienBullet(Bullet2D bullet)
  {
      m_fromAlien.push_back();
  }
  NewAlienBullet(Bullet2D bullet)
  {
      m_fromGun.push_back();
  }
  CheckAllBullets(vector< vector<Alien2D *>& aliens, Gun & gun)
  {

  }


  void BulletsMove()
  {
    for(auto it = m_fromAlien.begin(); it != m_fromGun; it++)
      it->VerticalShift(-BULLET_SPEED_START);

    for(auto it = m_fromGun.begin(); it != m_fromGun; it++)
      it->VerticalShift(BULLET_SPEED_START);

  }

  // Redefinition
  // square brackets
private:
  bool Check(Alien2D * alien)
  {
    for(auto it = m_fromAlien.begin(); it != m_fromGun; it++)
      if(*it && *alien)
      {
        if( *alien.GetHealth() <= BULLET_DAMAGE_START)
        {
          delete alien;
          alien = nullptr;
        }
        else
          *alien.SetHealth( *alien.GetHealth - BULLET_DAMAGE_START);//определяется типом пули
        m_fromGun.erase(it);
        return true;
      }
      else
      {
        //пересечение с препятствием/ями
      }
    return false;
  }
  bool Check(Gun & gun)
  {
    for(auto it = m_fromGun.begin(); it != m_fromGun; it++)
      if(*it && gun)
      {
        if( gun.GetHealth() <= BULLET_DAMAGE_START)
        {
          cout << " минус жизнь";
        }
        else
          *alien.SetHealth( *alien.GetHealth - BULLET_DAMAGE_START);//определяется типом пули
        m_fromGun.erase(it);
        return true;
      }
      else
      {
        //пересечение с препятствием/ями
      }
    return false;
  }

  list<Bullet2D> m_fromAlien;
  list<Bullet2D> m_fromGun;
};
