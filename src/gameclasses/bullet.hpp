#pragma once

#include "movedgameentity.hpp"

class Bullet2D final : public MovedGameEntity2D
{
public:
  // Allow default constructor.
  Bullet2D()
  {
    DefaultBulletSetStartValue();
  }
  // Destructor.
  ~Bullet2D() override = default;

  /*
  std::unique_ptr<GameEntity2D> Create
    (Point2D const & leftBottom, Point2D const & rightTop, float damage, float speed)
  {
    return std::unique_ptr<MovedGameEntity2D>(new Bullet2D(leftBottom, rightTop, damage, speed));
  }
  std::unique_ptr<GameEntity2D> Create
    (Point2D const & leftBottom, Point2D const & rightTop)
  {
    return std::unique_ptr<GameEntity2D>(new Bullet2D(leftBottom, rightTop));
  }
  */

  // Constructors with parameters.
  Bullet2D(Point2D const & leftBottom, Point2D const & rightTop)
    :MovedGameEntity2D(leftBottom, rightTop)
  {
    DefaultBulletSetStartValue();
  }

  Bullet2D(Point2D const & leftBottom, Point2D const & rightTop, float damage, float speed)
    :MovedGameEntity2D(leftBottom, rightTop, damage, speed)
  {}

  // copy constructor and assignment operator
  Bullet2D(Bullet2D const & obj)
    :MovedGameEntity2D(obj.GetMovedEntity())
  {}

  Bullet2D & operator = (Bullet2D const & obj)
  {
    if (this == &obj) return *this;
    SetMovedEntity(obj.GetMovedEntity());
    return *this;
  }

  // Capabilities
  void Move() override
  {
    throw std::runtime_error("Not released Bullet2D::Move.");
  }

  // Redefinition
  friend std::ostream & operator << (std::ostream & os, Bullet2D const & obj)
  {
    os << "BULLET{"
       << obj.GetBox().leftBottom()
       << ", " << obj.GetBox().rightTop()
       << ", HP: " << obj.GetHealth()
       << ", speed: " << obj.GetSpeed()
       << "}";
    return os;
  }

  inline EntitiesTypes GetEntityType() override { return EntitiesTypes::BulletType; }

private:
  inline void DefaultBulletSetStartValue()
  {
    SetHealth(BULLET_DAMAGE_START);
    SetSpeed(BULLET_SPEED_START);
  }
};

