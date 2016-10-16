#include "gtest/gtest.h"
#include "gameclasses/obstacle.hpp"
#include <sstream>
#include <unordered_set>

TEST(obstacle2d_test, test_construction)
{
  // Constructor
  Obstacle2D o1;
  EXPECT_EQ(o1.GetBorder(), Box2D(Point2D(OBSTACLE_BOX_LEFT, OBSTACLE_BOX_BOTTOM), Point2D(OBSTACLE_BOX_LEFT + OBSTACLE_WIDTH, OBSTACLE_BOX_BOTTOM + OBSTACLE_HEIGHT)));
  EXPECT_EQ(o1.GetTotalHealth(), OBSTACLE_TOTAL_HEALTH);
  EXPECT_EQ(o1.GetCountOfRows(), 1);
  EXPECT_EQ(o1.GetCountOfColumn(), 5);


  Obstacle2D o2 = {Point2D(0.0f, 0.0f), Point2D(100.0f, 100.0f), 500};
  EXPECT_EQ(o2.GetBorder(), Box2D(Point2D(0.0f, 0.0f), Point2D(100.0f, 100.0f)));
  EXPECT_EQ(o2.GetTotalHealth(), 500);
  EXPECT_EQ(o2.GetCountOfRows(), 1);
  EXPECT_EQ(o2.GetCountOfColumn(), 5);

  Obstacle2D o3 = {Point2D(50.0f, 50.0f), Point2D(110.0f, 110.0f), 500, 2, 4};
  EXPECT_EQ(o3.GetBorder(), Box2D(Point2D(50.0f, 50.0f), Point2D(110.0f, 110.0f)));
  EXPECT_EQ(o3.GetTotalHealth(), 500);
  EXPECT_EQ(o3.GetCountOfRows(), 2);
  EXPECT_EQ(o3.GetCountOfColumn(), 4);
}

TEST(obstacle2d_test, test_assignment)
{
  Obstacle2D o1;
  o1 = {Point2D(50.0f, 50.0f), Point2D(110.0f, 110.0f), 500, 2, 4};

  BoxMatrix bMatrix = o1.GetBoxMatrix();
  for (size_t i = 0; i < bMatrix.size(); ++i)
  {
    BoxVector tempVect;
    tempVect = bMatrix[i];
    for (size_t j = 0; j < tempVect.size(); ++j)
    {
      // the same for Obstacle2D class
      EXPECT_EQ(tempVect[j],
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
    }
  }

  Obstacle2D o2;
  o2 = o1;
  EXPECT_EQ(o2.GetBoxesHealthMatrix(), o1.GetBoxesHealthMatrix());
  EXPECT_EQ(o2.GetBoxMatrix(), o1.GetBoxMatrix());
  EXPECT_EQ(o2.GetCountOfColumn(), o1.GetCountOfColumn());
  EXPECT_EQ(o2.GetCountOfRows(), o1.GetCountOfRows());
  EXPECT_EQ(o2.GetTotalHealth(), o1.GetTotalHealth());
}
