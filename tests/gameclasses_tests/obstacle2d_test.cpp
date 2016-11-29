#include "gtest/gtest.h"
#include "gameclasses/obstacle.hpp"
#include <sstream>
#include <unordered_set>

TEST(obstacle2d_test, test_construction)
{
  // Constructor
  Obstacle2D o1;
  EXPECT_EQ(o1.GetBox(), Box2D(Point2D(OBSTACLE_BOX_LEFT, OBSTACLE_BOX_BOTTOM), Point2D(OBSTACLE_BOX_LEFT + OBSTACLE_WIDTH, OBSTACLE_BOX_BOTTOM + OBSTACLE_HEIGHT)));
  EXPECT_EQ(o1.GetHealth(), OBSTACLE_TOTAL_HEALTH);
  EXPECT_EQ(o1.GetCountOfRows(), OBSTACLE_COUNT_VERTICAL_PART);
  EXPECT_EQ(o1.GetCountOfColumn(), OBSTACLE_COUNT_HORIZONTAL_PART);


  Obstacle2D o2 = {Point2D(0.0f, 0.0f), Point2D(100.0f, 100.0f), 500};
  EXPECT_EQ(o2.GetBox(), Box2D(Point2D(0.0f, 0.0f), Point2D(100.0f, 100.0f)));
  EXPECT_EQ(o2.GetHealth(), 500);
  EXPECT_EQ(o2.GetCountOfRows(), OBSTACLE_COUNT_VERTICAL_PART);
  EXPECT_EQ(o2.GetCountOfColumn(), OBSTACLE_COUNT_HORIZONTAL_PART);

  Obstacle2D o3 = {Point2D(50.0f, 50.0f), Point2D(110.0f, 110.0f), 500};
  EXPECT_EQ(o3.GetBox(), Box2D(Point2D(50.0f, 50.0f), Point2D(110.0f, 110.0f)));
  EXPECT_EQ(o3.GetHealth(), 500);
  EXPECT_EQ(o3.GetCountOfRows(), OBSTACLE_COUNT_VERTICAL_PART);
  EXPECT_EQ(o3.GetCountOfColumn(), OBSTACLE_COUNT_HORIZONTAL_PART);
}

TEST(obstacle2d_test, test_assignment)
{
  Point2D ld(50.0f, 50.0f), rt(110.0f, 110.0f);
  float partWidth = (rt.x() - ld.x()) / OBSTACLE_COUNT_HORIZONTAL_PART, partHeight = (rt.y() - ld.y()) / OBSTACLE_COUNT_VERTICAL_PART;

  Obstacle2D o1;
  o1 = {ld, rt, 500};

  BoxMatrix bMatrix = o1.GetBoxMatrix();
  for (size_t i = 0; i < bMatrix.size(); ++i)
  {
    BoxVector tempVect;
    tempVect = bMatrix[i];
    for (size_t j = 0; j < tempVect.size(); ++j)
    {
      if (tempVect[j] != nullptr)
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
  }

  Obstacle2D o2;
  o2 = o1;
  EXPECT_EQ(o2.GetBoxMatrix()[1][0], o1.GetBoxMatrix()[1][0]);
  EXPECT_EQ(o2.GetBoxMatrix(), o1.GetBoxMatrix());
  EXPECT_EQ(o2.GetCountOfColumn(), o1.GetCountOfColumn());
  EXPECT_EQ(o2.GetCountOfRows(), o1.GetCountOfRows());
  EXPECT_EQ(o2.GetHealth(), o1.GetHealth());
}
