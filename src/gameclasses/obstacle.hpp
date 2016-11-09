#pragma once

#include "lifegameentity.hpp"
#include <vector>

using BoxVector = std::vector<LifeGameEntity2D>;// Alias
using BoxMatrix = std::vector<BoxVector>;       // Alias

class Obstacle2D final : public LifeGameEntity2D
{
public:
  // constructor.
  Obstacle2D()
  {
    SetEntity(GameEntity2D{Box2D(Point2D(OBSTACLE_BOX_LEFT, OBSTACLE_BOX_BOTTOM), Point2D(OBSTACLE_BOX_LEFT + OBSTACLE_WIDTH, OBSTACLE_BOX_BOTTOM + OBSTACLE_HEIGHT))});
    FillBoxMatrix(1, 5);
    SetHealth(OBSTACLE_TOTAL_HEALTH);
  }

  // Destructor.
  ~Obstacle2D() = default;

  // Constructors with parameters.
  Obstacle2D(Point2D const & leftBottom, Point2D const & rightTop, float totalHealth = OBSTACLE_TOTAL_HEALTH)
    :LifeGameEntity2D(leftBottom, rightTop, totalHealth)
  {
    FillBoxMatrix(1, 5);
  }

  Obstacle2D(Point2D const & leftBottom, Point2D const & rightTop, float totalHealth, size_t const countRow, size_t const countColumn)
    :LifeGameEntity2D(leftBottom, rightTop, totalHealth)
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
    SetHealth(obj.GetHealth());
    return *this;
  }

  // Getters
  inline BoxMatrix const GetBoxMatrix() const            { return m_boxes; }
  inline size_t const GetCountOfRows() const             { return m_boxes.size(); }
  inline size_t const GetCountOfColumn() const           { return m_boxes[0].size(); }

  // Redefinition
  friend std::ostream & operator << (std::ostream & os, Obstacle2D & obj)
  {
    os << "OBSTACLE{"
       << obj.GetBox().leftBottom()
       << ", " << obj.GetBox().rightTop()
       << ", " << obj.GetHealth()
       << "}";
    return os;
  }
  inline EntitiesTypes GetEntityType(){ return EntitiesTypes::ObstacleType; }
private:

  void FillBoxMatrix(size_t const countRow, size_t const countColumn)
  {
    float healthOfPart = GetHealth() / (countRow * countColumn);

    m_boxes.reserve(countRow);
    for (size_t i = 0; i < countRow; ++i)
    {
      BoxVector tempBoxVect;
      tempBoxVect.reserve(countColumn);
      for(size_t j = 0; j < countColumn; ++j)
      {
        tempBoxVect.push_back
        (
          LifeGameEntity2D{
            Box2D
            {
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
            },
            healthOfPart
          }
        );
      }
      m_boxes.push_back(tempBoxVect);
    }
  }

  BoxMatrix m_boxes;  // matrix of LifeGameEntityes
};
