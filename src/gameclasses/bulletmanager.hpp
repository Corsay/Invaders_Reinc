#pragma once

#include "bullet.hpp"
#include "gun.hpp"
#include "alien.hpp"
#include <list>

class Bullet2DManager
{
public:
  // constructor.
  Bullet2DManager() = default;

  // destructor.
  ~Bullet2DManager() = default;

  // no copy constructor and assignment operator
  Bullet2DManager(Bullet2DManager const & obj) = delete;
  void operator = (Bullet2DManager const & obj) = delete;

  // Getters
  inline size_t const GetCountOfAlienBullets() const { return m_fromAlien.size(); }
  inline size_t const GetCountOfGunBullets() const   { return m_fromGun.size(); }

  // Capabilities
  /*
  CheckAllBullets(vector<vector<Alien2D *>> & aliens, Gun2D & gun)
  {

  }
  */

  bool NewBullet(Bullet2D const & bullet, int Type)
  {
    switch (Type)
    {
      case 0: // gun bullet
      {
        m_fromGun.push_back(bullet);
        break;
      }
      case 1: // alien bullet
      {
        m_fromAlien.push_back(bullet);
        break;
      }
      default:
      {
        return false; // error undefined type
      }
    }
    return true; // allright
  }

  void BulletsMove(Box2D const & border)
  {
    for(auto it = m_fromAlien.begin(); it != m_fromAlien.end(); it++)
    {
      it->VerticalShift(-BULLET_SPEED_START);
    }

    for(auto it = m_fromGun.begin(); it != m_fromGun.end(); it++)
    {
      it->VerticalShift(BULLET_SPEED_START);
    }
  }
private:

  /*bool Check(Alien2D * alien)
  {
    for(auto it = m_fromGun.begin(); it != m_fromGun.end(); it++)
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
    for(auto it = m_fromAlien.begin(); it != m_fromAlien.end(); it++)
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
  }*/

  std::list<Bullet2D> m_fromAlien;
  std::list<Bullet2D> m_fromGun;
};
