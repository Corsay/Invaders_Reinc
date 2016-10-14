#pragma once

#include "box2d.hpp"
#include <vector>

class Obstacle2D : public Box2D
{
public:
  // Allow default constructor.
  Obstacle2D() = default;

  // destructor.
  ~Obstacle2D() = default;

  // Constructors with parameters.
  Obstacle2D(Point2D left_bottom, Point2D right_top, float totalHealth)
    :Box2D(left_bottom, right_top), m_totalHealth(totalHealth)
  {}

  // Getters
  inline int const GetTotalHealth() const { return m_totalHealth; }
  // Setters
  inline void SetTotalHealth(float const new_totalHealth) { m_totalHealth = new_totalHealth; }

private:

  // create matrix
  void FillBoxMatrix()
  {

  }

  std::vector< std::vector<Box2D *> > m_boxes;     // matrix of Boxes
  std::vector< std::vector<float> > m_boxesHealth; // matrix of Boxes health;
  // IsAlive == false - inform about need of call obstacle destructor
  // -> destroy obstacle
  float m_totalHealth = OBSTACLE_TOTAL_HEALTH;
    // - health of all parts of obstacle
    // to get health of one part of obstacle need to divide health of obstacle on count of parts
    // this is need to create m_entities with correct health
};
