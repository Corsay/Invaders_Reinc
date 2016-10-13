#pragma once

#include "box2d.hpp"

class Obstacle2D : public Box2D
{
public:
  // Allow default constructor.
  Obstacle2D() = default;

  // Constructors with parameters.
  Obstacle2D(Point2D left_bottom, Point2D right_top, float totalHealth)
    :Box2D(left_bottom, right_top), m_totalHealth(totalHealth)
  {}

  // Getters
  inline int const GetTotalHealth() const { return m_totalHealth; }

  // Setters
  inline void SetTotalHealth(float const new_totalHealth) { m_totalHealth = new_totalHealth; }


  // Capabilities

  // need to add function:
  // work with bulletManager -- get bullets from it, and use needed information
  // check intersection bullet with one of the m_entities (as param it get Bullet2D(check its as Box2D && Box2D))
private:

  // create matrix
  void CreateBoxMatrix()
  {

  }

  // all m_boxes == nullptr
  // -> destroy obstacle

  std::vector< std::vector<Box2D *> > m_boxes;       // matrix of Boxes (BAD BECAUSE IN BOX2d HAVE NOT HP)
  std::vector< std::vector<float *> > m_boxesHealth; // matrix of Boxes health;
  // IsAlive == false - inform about need of call obstacle destructor
  // -> destroy obstacle
  float m_totalHealth = OBSTACLE_TOTAL_HEALTH;
    // - health of all parts of obstacle
    // to get health of one part of obstacle need to divide health of obstacle on count of parts
    // this is need to create m_entities with correct health
};
