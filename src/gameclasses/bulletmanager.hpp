#pragma once

#include "bullet.hpp"
#include <list>

using BulletList = std::list<Bullet2D>; // Alias

class Bullet2DManager
{
public:
  // constructor.
  Bullet2DManager() = default;

  // Destructor.
  ~Bullet2DManager() = default;

  // copy constructor
  Bullet2DManager(Bullet2DManager const & obj)
  {
    m_fromAlien = obj.GetBulletsFromAliensList();
    m_fromGun = obj.GetBulletsFromGunList();
  }

  // assignment operator (for next level reinit)
  Bullet2DManager & operator = (Bullet2DManager const & obj)
  {
    if (this == &obj) return *this;
    m_fromAlien = obj.GetBulletsFromAliensList();
    m_fromGun = obj.GetBulletsFromGunList();
    return *this;
  }


  // Getters
  inline BulletList  const & GetBulletsFromAliensList() const { return m_fromAlien; }
  inline BulletList  const & GetBulletsFromGunList() const    { return m_fromGun; }
  inline BulletList & GetBulletsFromAliensList()      { return m_fromAlien; }
  inline BulletList & GetBulletsFromGunList()         { return m_fromGun; }
  inline size_t const GetCountOfAlienBullets() const  { return m_fromAlien.size(); }
  inline size_t const GetCountOfGunBullets() const    { return m_fromGun.size(); }


  // Capabilities
  void BulletsMove(float const & top)
  {
    std::list<std::list<Bullet2D>::iterator> itList;

    // move aliens bullets
    for(auto it = m_fromAlien.begin(); it != m_fromAlien.end(); ++it)
    {
      // need to delete bullet if true
      if (it->GetBox().bottom() < GAME_PADDING_BOTTOM) itList.push_back(it);
      else it->GetBox().VerticalShift(-(it->GetSpeed())); // if in left bottom (0; 0)
    }

    // erase itList
    for(auto it = itList.begin(); it != itList.end(); ++it)
    {
      m_fromAlien.erase(*it);
    }
    itList.clear();

    // move gun bullets
    for(auto it = m_fromGun.begin(); it != m_fromGun.end(); ++it)
    {
      // need to delete bullet if true
      if (it->GetBox().bottom() > top) itList.push_back(it);
      else it->GetBox().VerticalShift(it->GetSpeed());    // if in left bottom (0; 0)
    }

    // erase itList
    for(auto it = itList.begin(); it != itList.end(); ++it)
    {
      m_fromGun.erase(*it);
    }
    itList.clear();
  }

  bool NewBullet(Bullet2D const & bullet, EntitiesTypes Type)
  {
    switch (Type)
    {
      case GunType: // gun bullet add
      {
        m_fromGun.push_back(bullet);
        break;
      }
      case AlienType: // alien bullet add
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

private:
  BulletList m_fromAlien;
  BulletList m_fromGun;
};
