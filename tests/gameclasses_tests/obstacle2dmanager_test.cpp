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
