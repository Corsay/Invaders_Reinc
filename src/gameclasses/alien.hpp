#pragma once

#include "movedgameentity.hpp"

enum AlienTypes
{
  Pirate = 10,
  Raider = 30,
  Bombardier = 50
};

class Alien2D final : public MovedGameEntity2D
{
public:
  // Allow default constructor.
  Alien2D()
  {
    DefaultAlienSetStartValue();
  }

  // Destructor.
  ~Alien2D() override = default;

  // Constructors with parameters.
  Alien2D(Point2D const & leftBottom, Point2D const & rightTop)
    :MovedGameEntity2D(leftBottom, rightTop)
  {
    DefaultAlienSetStartValue();
  }

  Alien2D(Point2D const & leftBottom, Point2D const & rightTop, float health, float speedShoot)
    :MovedGameEntity2D(leftBottom, rightTop, health, speedShoot)
  {}

  Alien2D(Point2D const & leftBottom, Point2D const & rightTop, float health, float speedShoot, int type)
    :MovedGameEntity2D(leftBottom, rightTop, health, speedShoot), m_type(type)
  {}

  // copy constructor and assignment operator
  Alien2D(Alien2D const & obj)
    :MovedGameEntity2D(obj.GetMovedEntity())
  {}

  Alien2D & operator = (Alien2D const & obj)
  {
    if (this == &obj) return *this;
    SetMovedEntity(obj.GetMovedEntity());
    return *this;
  }

  // getters
  int const GetType() const { return this->m_type; }

  // For factory
  inline EntitiesTypes GetEntityType() override { return EntitiesTypes::AlienType; }
  std::unique_ptr<GameEntity2D> Create() override
  {
    return std::unique_ptr<GameEntity2D>(new Alien2D());
  }


  // Redefinition
  friend std::ostream & operator << (std::ostream & os, Alien2D const & obj)
  {
    os << "ALIEN{"
       << obj.GetBox().leftBottom()
       << ", " << obj.GetBox().rightTop()
       << ", HP: " << obj.GetHealth()
       << ", speed: " << obj.GetSpeed()
       << "}";
    return os;
  }

private:
  inline void DefaultAlienSetStartValue()
  {
    SetHealth(ALIEN_HEALTH);
    SetSpeed(ALIEN_SPEED_SHOOT_START);
  }

  int m_type = AlienTypes::Pirate;
};
