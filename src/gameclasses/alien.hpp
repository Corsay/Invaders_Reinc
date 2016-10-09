#pragma once

#include "gameentity.hpp"

class Alien2D : public GameEntity2D
{
public:
  // Allow default constructor.
  Alien2D() = default;

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


  // Redefinition
  // square brackets
private:

  float m_health = 50.0f; // - health of the alien
  float m_speed = 1.0f;   // - shoot speed
};
