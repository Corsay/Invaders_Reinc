#pragma once

#include "box2d.hpp"
#include <vector>

using BoxMatrix = std::vector< std::vector<Box2D *> >;  // Alias
using HealthMatrix = std::vector< std::vector<float> >; // Alias

class Obstacle2D : public Box2D
{
public:
  // Allow default constructor.
  Obstacle2D()
  {
    FillBoxMatrix(5,11);
  }

  // Destructor.
  ~Obstacle2D() = default;

  // Constructors with parameters.
  Obstacle2D(Point2D left_bottom, Point2D right_top, float totalHealth)
    :Box2D(left_bottom, right_top), m_totalHealth(totalHealth)
  {}

  // Getters
  inline BoxMatrix const GetBoxMatrix() const            { return m_boxes; }
  inline HealthMatrix const GetBoxexHealthMatrix() const { return m_boxesHealth; }
  inline float const GetTotalHealth() const              { return m_totalHealth; }
  inline size_t const GetCountOfRows() const             { return m_boxes.size(); }
  inline size_t const GetCountOfColumn() const           { return m_boxes[0].size(); }
  // Setters
  inline void SetTotalHealth(float const new_totalHealth) { m_totalHealth = new_totalHealth; }

private:

  // Fill m_boxes and m_boxesHealth Matrix
  void FillBoxMatrix(size_t const countRow, size_t const countColumn)
  {
    std::runtime_error("Not released.");
  }

  BoxMatrix m_boxes;                           // matrix of Boxes
  HealthMatrix m_boxesHealth;                  // matrix of Boxes health;
  float m_totalHealth = OBSTACLE_TOTAL_HEALTH;
};
