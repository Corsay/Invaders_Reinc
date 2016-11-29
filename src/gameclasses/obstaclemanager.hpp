#pragma once

#include "obstacle.hpp"
#include "bullet.hpp"
#include <vector>

using ObstacleVector = std::vector<Obstacle2D *>;     // Alias

class Obstacle2DManager
{
public:
  // constructor.
  Obstacle2DManager()
  {
    CreateObstacleVector(4); // initialize default matrix
  }

  // Destructor.
  ~Obstacle2DManager()
  {
    for(size_t i = 0; i != m_obstacles.size(); ++i)
      delete m_obstacles[i];
    m_obstacles.clear();
  }

  // Constructors with parameters.
  Obstacle2DManager(size_t const countObstacle)
  {
    CreateObstacleVector(countObstacle);
  }

  // copy constructor
  Obstacle2DManager(Obstacle2DManager const & obj)
  {
    m_obstacles = obj.GetObstacleVector();
  }


  // assignment operator
  Obstacle2DManager & operator = (Obstacle2DManager const & obj)
  {
    if (this == &obj) return *this;
    m_obstacles = obj.GetObstacleVector();
    return *this;
  }


  // Getters
  inline ObstacleVector const & GetObstacleVector() const { return m_obstacles; }
  inline ObstacleVector & GetObstacleVector() { return m_obstacles; }
  inline size_t const GetCountOObstacle() const { return m_obstacles.size(); }


  // Capabilities
  bool CheckIntersection(Bullet2D const & bul)
  {
    for(auto it = m_obstacles.begin(); it != m_obstacles.end(); ++it)
    {
      if((*it)->CheckIntersection(bul))
      {
        bul.Inform(*(*it));
        return true;
      }
    }
    return false;
  }

  void CreateObstacleVector(size_t const countObstacle)
  {
    m_obstacles.clear();
    m_obstacles.reserve(countObstacle);
    for (size_t i = 0; i < countObstacle; ++i)
    {
      m_obstacles.push_back
      (
        new Obstacle2D
        (
          Point2D
          {
            OBSTACLE_BOX_LEFT + (i + 1) * OBSTACLE_DISTANCE + i * OBSTACLE_WIDTH,
            OBSTACLE_BOX_BOTTOM
          },
          Point2D
          {
            OBSTACLE_BOX_LEFT + (i + 1) * ( OBSTACLE_DISTANCE + OBSTACLE_WIDTH ),
            OBSTACLE_BOX_BOTTOM + OBSTACLE_HEIGHT
          }
        )
      );
    }
  }

private:
  ObstacleVector m_obstacles;          // matrix of Obstacles
};
