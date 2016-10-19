#pragma once

#include "movedgameentity.hpp"

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

  // copy constructor and assignment operator
  Alien2D(MovedGameEntity2D const & obj)
    :MovedGameEntity2D(obj)
  {}

  // Capabilities
  void Move() override
  {
    throw std::runtime_error("Not released Bullet2D::Move.");
  }
private:
  inline void DefaultAlienSetStartValue()
  {
    SetHealth(BULLET_DAMAGE_START);
    SetSpeed(BULLET_SPEED_START);
  }
};
