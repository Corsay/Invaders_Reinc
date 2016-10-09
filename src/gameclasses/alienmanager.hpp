#pragma once

#include "alien.hpp"

class Alien2DManager
{
public:
  // Allow default constructor.
  Alien2DManager() = default;

  // Constructors with parameters.
  // need


  // Constructor with initialization list.
  // need or not (?!)


  // Copy constructor
  // can be useful


  // Move constructor
  // not need


  // Getters
  // all getters for new fields


  // Setters
  // all settsers for new fields


  // Logical operators
  // don't know need or not (?!)


  // Assignment operator.
  // can be useful =


  // Move operator
  // not need


  // Math operations
  // don't know need or not (?!)


  // Capabilities

  // need to add function:
  // work with bulletManager
  // check intersection bullet with one of the m_aliens (as param it get Bullet2D(check its as Box2D && Box2D))
  // move aliens (standart moving or boss configuration moving)


  // Redefinition
  // square brackets
private:

  Alien2D m_aliens;      // matrix of Aliens
  // m_liveAliensCount == 0 - level passed
  // -> destroy AlienManager
  int m_liveAliensCount = 5;
};
