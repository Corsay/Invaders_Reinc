#include "gtest/gtest.h"
#include "gameclasses/obstaclemanager.hpp"
#include <sstream>
#include <unordered_set>

TEST(obstacle2dmanager_test, test_construction)
{
  // Constructor
  Obstacle2DManager o1;
  EXPECT_EQ(o1.GetCountOObstacle(), 4);

  Obstacle2DManager o2 = {5};
  EXPECT_EQ(o2.GetCountOObstacle(), 5);

  // copy constructor
  Obstacle2DManager o3 = o2;
  EXPECT_EQ(o3.GetCountOObstacle(), o2.GetCountOObstacle());
}

TEST(obstacle2dmanager_test, test_assignment)
{
  Obstacle2DManager o1;
  o1 = {5};

/*  for (size_t i = 0; i < o1.GetCountOObstacle(); ++i)
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

  BoxMatrix bMatrix = o1.GetBoxMatrix();
  for (size_t i = 0; i < bMatrix.size(); ++i)
  {
    BoxVector tempVect;
    tempVect = bMatrix[i];
    for (size_t j = 0; j < tempVect.size(); ++j)
    {
      // the same for Obstacle2D class
      EXPECT_EQ
      (
        tempVect[j]->GetBox(),
        Box2D
        (
          Point2D
          {
            ld.x() + j * partWidth,
            ld.y() + i * partHeight
          },
          Point2D
          {
            ld.x() + ( j + 1 ) * partWidth + 1,
            ld.y() + ( i + 1 ) * partHeight + 1
          }
        )
      );
    }
  }

  Obstacle2D o2;
  o2 = o1;
  EXPECT_EQ(o2.GetBoxMatrix()[1][0], o1.GetBoxMatrix()[1][0]);
  EXPECT_EQ(o2.GetBoxMatrix(), o1.GetBoxMatrix());
  EXPECT_EQ(o2.GetCountOfColumn(), o1.GetCountOfColumn());
  EXPECT_EQ(o2.GetCountOfRows(), o1.GetCountOfRows());
  EXPECT_EQ(o2.GetHealth(), o1.GetHealth());*/
}
