#pragma once

#include <ctime>

#include "movedgameentity.hpp"
#include "bullet.hpp"

class Ship2D final : public MovedGameEntity2D
{
public:
  // Allow default constructor.
  Ship2D()
  {
    DefaultShipSetStartValue();
  }

  // Destructor.
  ~Ship2D() override = default;

  // Constructors with parameters.
  Ship2D(Point2D const & leftBottom, Point2D const & rightTop, short direct = 1)
    :MovedGameEntity2D(leftBottom, rightTop)
  {
    DefaultShipSetStartValue();
    m_direction = direct;
  }

  Ship2D(Point2D const & leftBottom, Point2D const & rightTop, float health, float speed,  short direct = 1)
    :MovedGameEntity2D(leftBottom, rightTop, health, speed)
  {
    m_direction = direct;
  }

  // copy constructor and assignment operator
  Ship2D(Ship2D const & obj)
    :MovedGameEntity2D(obj.GetMovedEntity())
  {}

  Ship2D & operator = (Ship2D const & obj)
  {
    if (this == &obj) return *this;
    SetMovedEntity(obj.GetMovedEntity());
    return *this;
  }


  // For factory
  inline EntitiesTypes GetEntityType() override { return EntitiesTypes::ShipType; }
  std::unique_ptr<GameEntity2D> Create() override
  {
    return std::unique_ptr<GameEntity2D>(new Ship2D());
  }


  // Capabilities
  void MoveShip()
  {
    this->GetBox().HorizontalShift(m_direction * SHIP_SPEED_START);
  }

  void RandomNegativeBonus()
  {
    srand(time(0));
    int randomValue = rand() % 100;
    if (randomValue < 10) // 10%
    {
      BONUS_HIT_OBSTACLES = true;
    }
    else if (randomValue < 70) // 60%
    {
      ALIEN_SHOOT_SPEED = BONUS_SPEED_ALIEN_FAST_SHOOT;
      BONUS_ALIEN_FAST_SHOOT = true;
    }
    else if (randomValue < 100) // 30%
    {
      BONUS_ANTI_X2 = true;
    }
  }

  void RandomPozitiveBonus()
  {
    srand(time(0));
    int randomValue = rand() % 124;
    if (randomValue < 5) // 5%
    {
      BONUS_GOD = true;
    }
    else if (randomValue < 15) // 10%
    {
      BONUS_ADD_LIVE = true;
    }
    else if (randomValue < 20) // 5%
    {
      BONUS_HEAL_OBSTACLES = true;
    }
    else if (randomValue < 39) // 19%
    {
      BONUS_X2 = true;
    }
    else if (randomValue < 44) // 5%
    {
      GUN_SHOOT_SPEED = BONUS_SPEED_LAZER_SHOOT;
      BONUS_LAZER = true;
    }
    else if (randomValue < 124) // 80%
    {
      GUN_SHOOT_SPEED = BONUS_SPEED_GUN_FAST_SHOOT;
      BONUS_GUN_FAST_SHOOT = true;
    }
    else // 1%
    {
      BONUS_HIT_ALL_ALIENS = true;
    }
  }

  bool CheckIntersection(Bullet2D const & bul)
  {
    if(! (bul.GetBox() && this->GetBox()))
      return false;

    // if intersect
    bul.Inform(*this);
    this->SetHealth(this->GetHealth() - bul.GetHealth());
    if(this->GetHealth() <= 0)
    {      
      RandomPozitiveBonus();
    }
    return true;
  }


  // Redefinition
  friend std::ostream & operator << (std::ostream & os, Ship2D const & obj)
  {
    os << "SHIP{"
       << obj.GetBox().leftBottom()
       << ", " << obj.GetBox().rightTop()
       << ", HP: " << obj.GetHealth()
       << ", speed: " << obj.GetSpeed()
       << "}";
    return os;
  }

private:
  inline void DefaultShipSetStartValue()
  {
    SetHealth(SHIP_HEALTH_START);
    SetSpeed(SHIP_SPEED_START);
  }
  short m_direction = 1;
};
