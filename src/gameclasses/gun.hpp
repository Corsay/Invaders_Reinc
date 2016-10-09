#pragma once

#include "gameentity.hpp"

class Gun2D : public GameEntity2D
{
public:
  // Allow default constructor.
  Gun2D() = default;

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

  // Box2D
  // leftBottom() - left bottom point of the gun
  // rightTop()   - right top point of the gun
  // left()       - left/right/top/bottom border of the gun, need to be <= space borders (how to get it? - maybe control all game from Space class)
  // GameEntity
  // IsAlive == false - defeat
  // -> destroy gun
  float m_health = 50.0f; // - health of the gun
  float m_speed = 1.0f;   // - shoot speed
  // m_lenght - lenght
  // m_height - height (getheight)
};
