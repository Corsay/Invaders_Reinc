#pragma once

#include "box2d.hpp"

class Obstacle2D : public Box2D
{
public:
  // Allow default constructor.
  Obstacle2D() = default;

  // Constructors with parameters.
  // need


  // Constructor with initialization list.
  // need or not (?!)


  // Getters
  // all getters for new fields


  // Setters
  // all settsers for new fields


  // Logical operators
  // don't know need or not (?!)


  // Math operations
  // don't know need or not (?!)


  // Capabilities

  // need to add function:
  // work with bulletManager -- get bullets from it, and use needed information
  // check intersection bullet with one of the m_entities (as param it get Bullet2D(check its as Box2D && Box2D))


  // Redefinition
  // square brackets
private:

  // create matrix
  void CreateBoxMatrix();

  // all m_entities == nullptr
  // -> destroy obstacle
  Box2D m_boxes;          // matrix of Boxes( BAD BECAUSE IN BOX2d HAVE NOT HP)
  float m_boxesHealth;    // matrix of Boxes health;
  // IsAlive == false - inform about need of call obstacle destructor
  // -> destroy obstacle
  float m_health = 50.0f;       // - health of all parts of obstacle
                                // to get health of one part of obstacle need to divide health of obstacle on count of parts
                                // this is need to create m_entities with correct health
};
