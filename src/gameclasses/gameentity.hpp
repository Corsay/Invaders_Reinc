#pragma once

#include "box2d.hpp"

class GameEntity2D : public Box2D
{
public:
  // Allow default constructor.
  GameEntity2D() = default;

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

  // if IsAlive == false -> then need to call destructor of element
  bool IsAlive();

  // min, max positions ???? not need to remember it here, but hove to get it from space class i don't know now
  // Point2D m_leftBottomMin = {0.0f, 0.0f}, m_rightTopMax = {0.0f, 0.0f};
  // lenght and height (px)
  float m_lenght = 5.0f;
  float m_height = 5.0f;
};
