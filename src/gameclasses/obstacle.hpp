#pragma once

#include "gameentity.hpp"

class Obstacle2D : public GameEntity2D
{
public:
  // Allow default constructor.
  Obstacle2D() = default;

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
  // work with bulletManager -- get bullets from it, and use needed information
  // check intersection bullet with one of the m_entities (as param it get Bullet2D(check its as Box2D && Box2D))


  // Redefinition
  // square brackets
private:

  // create matrix
  void CreateEntitiesMatrix();

  // all m_entities == nullptr
  // -> destroy obstacle
  GameEntity2D m_entities;      // matrix of GameEntities
  // IsAlive == false - inform about need of call obstacle destructor
  // -> destroy obstacle
  float m_health = 50.0f;       // - health of all parts of obstacle
                                // to get health of one part of obstacle need to divide health of obstacle on count of parts
                                // this is need to create m_entities with correct health
};
