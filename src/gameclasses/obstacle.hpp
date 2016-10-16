#pragma once

#include "box2d.hpp"
#include <vector>

using BoxVector = std::vector<Box2D>;           // Alias
using BoxMatrix = std::vector<BoxVector>;       // Alias
using HealthVector = std::vector<float>;        // Alias
using HealthMatrix = std::vector<HealthVector>; // Alias

class Obstacle2D : public Box2D
{
public:
  // constructor.
  Obstacle2D()
  {   
    SetBorder(Box2D(Point2D(OBSTACLE_BOX_LEFT, OBSTACLE_BOX_BOTTOM), Point2D(OBSTACLE_BOX_LEFT + OBSTACLE_WIDTH, OBSTACLE_BOX_BOTTOM + OBSTACLE_HEIGHT)));
    m_totalHealth = OBSTACLE_TOTAL_HEALTH;
    FillBoxMatrix(1, 5);
  }

  // Destructor.
  ~Obstacle2D() = default;

  // Constructors with parameters.
  Obstacle2D(Point2D leftBottom, Point2D rightTop, float totalHealth)
    :Box2D(leftBottom, rightTop), m_totalHealth(totalHealth)
  {
    FillBoxMatrix(1, 5);
  }

  Obstacle2D(Point2D leftBottom, Point2D rightTop, float totalHealth, size_t const countRow, size_t const countColumn)
    :Box2D(leftBottom, rightTop), m_totalHealth(totalHealth)
  {
    FillBoxMatrix(countRow, countColumn);
  }

  // no copy constructor
  Obstacle2D(Obstacle2D const & obj) = delete;
  // assignment operator
  Obstacle2D & operator = (Obstacle2D const & obj)
  {
    if (this == &obj) return *this;
    m_boxes = obj.GetBoxMatrix();
    m_boxesHealth = obj.GetBoxesHealthMatrix();
    m_totalHealth = obj.GetTotalHealth();
    return *this;
  }

  // Getters
  inline BoxMatrix const GetBoxMatrix() const            { return m_boxes; }
  inline HealthMatrix const GetBoxesHealthMatrix() const { return m_boxesHealth; }
  inline float const GetTotalHealth() const              { return m_totalHealth; }
  inline size_t const GetCountOfRows() const             { return m_boxes.size(); }
  inline size_t const GetCountOfColumn() const           { return m_boxes[0].size(); }
  // Setters
  inline void SetTotalHealth(float const newTotalHealth) { m_totalHealth = newTotalHealth; }

private:

  void FillBoxMatrix(size_t const countRow, size_t const countColumn)
  {
    float healthOfPart = m_totalHealth / (countRow * countColumn);

    m_boxes.reserve(countRow);
    m_boxesHealth.reserve(countRow);
    for (size_t i = 0; i < countRow; ++i)
    {
      BoxVector tempBoxVect;
      HealthVector tempBoxHealthVect;
      tempBoxVect.reserve(countColumn);
      tempBoxHealthVect.reserve(countColumn);
      for(size_t j = 0; j < countColumn; ++j)
      {
        tempBoxVect.push_back
        (
          Box2D
          (
            Point2D
            {
              OBSTACLE_BOX_LEFT + j * OBSTACLE_PART_WIDTH,
              OBSTACLE_BOX_BOTTOM + i * OBSTACLE_PART_WIDTH
            },
            Point2D
            {
              OBSTACLE_BOX_LEFT + j * OBSTACLE_PART_WIDTH + OBSTACLE_PART_WIDTH,
              OBSTACLE_BOX_BOTTOM + i * OBSTACLE_PART_WIDTH + OBSTACLE_PART_HEIGHT,
            }
          )
        );
        tempBoxHealthVect.push_back(healthOfPart);
      }
      m_boxes.push_back(tempBoxVect);
      m_boxesHealth.push_back(tempBoxHealthVect);
    }
  }

  BoxMatrix m_boxes;                           // matrix of Boxes
  HealthMatrix m_boxesHealth;                  // matrix of Boxes health;
  float m_totalHealth = OBSTACLE_TOTAL_HEALTH;
};
