#include "gtest/gtest.h"
#include "gameclasses/alienmanager.hpp"
#include <sstream>
#include <unordered_set>

TEST(alien2dmanager_test, test_construction)
{
  // default constructor
  Alien2DManager am1;
  EXPECT_EQ(am1.GetCountOfRows(), 5);
  EXPECT_EQ(am1.GetCountOfColumn(), 11);
  EXPECT_EQ(am1.GetLiveAliensCount(), 5*11);

  // Constructors with parameters.
  Alien2DManager am2 = {3, 7};
  EXPECT_EQ(am2.GetCountOfRows(), 3);
  EXPECT_EQ(am2.GetCountOfColumn(), 7);
  EXPECT_EQ(am2.GetLiveAliensCount(), 3*7);
}

TEST(alien2dmanager_test, test_assignment)
{
  /*Alien2DManager am1 = {5, 7};
  //am1 = {5, 7};
  //EXPECT_EQ(a1, Alien2DManager (Point2D(1.2f, 2.4f), Point2D(3.6f, 4.8f), ALIEN_HEALTH_START, ALIEN_SPEED_SHOOT_START));

  Alien2DManager am2;
  am2 = am1;
  EXPECT_EQ(am2, am1);*/
}
