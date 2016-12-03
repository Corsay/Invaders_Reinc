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
  {m_direction = direct;}

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
    if(m_int_timer_start != 0)
      m_int_timer_start--;
    else
      this->GetBox().HorizontalShift(m_direction * SHIP_SPEED_START);
  }

  void RandomBonus()
  {
    srand(time(0));
    int randomValue = rand() % 99;
    if (randomValue < 5) BONUS_GOD = true;                  // 5%
    else if (randomValue < 95) GUN_SHOOT_SPEED = 40; // BONUS_FAST_SHOOT = true;     // 90%
    else if (randomValue < 99) GUN_SHOOT_SPEED = 1;  // BONUS_LAZER = true;          // 5%
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
      RandomBonus();
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
    m_int_timer_start = 1200 + rand()%1200;
    // не чаще чем в 1000/60=20 секунд, не реже чем в 40 секунд
  }
  short m_direction = 1;
  short m_int_timer_start = 0;
};
