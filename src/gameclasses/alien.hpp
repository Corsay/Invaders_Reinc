#pragma once

#include "moveEntity.hpp"

class Alien2D : public MoveEntity2D
{
public:
  // Allow default constructor.
  Alien2D() = default;

  // Destructor.
  ~Alien2D() override = default;

  // Constructors with parameters.
  Alien2D(Point2D const & leftBottom, Point2D const & rightTop)
    :MoveEntity2D(leftBottom, rightTop)
  {}

  Alien2D(Point2D const & leftBottom, Point2D const & rightTop, float health, float speedShoot)
    :MoveEntity2D(leftBottom, rightTop, health, speedShoot)
  {}

  // copy constructor and assignment operator
  Alien2D(Alien2D const & obj)
    :MoveEntity2D(obj)
  {}

private:

};
