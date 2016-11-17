#include "gtest/gtest.h"
#include "gameclasses/alien.hpp"
#include <sstream>
#include <unordered_set>


TEST(alien2d_test, test_construction)
{
  // default constructor
  Alien2D a1;
  EXPECT_EQ(a1.GetHealth(), ALIEN_HEALTH_START);
  EXPECT_EQ(a1.GetSpeed(), ALIEN_SPEED_SHOOT_START);

  // Constructors with parameters.
  Alien2D a2 = { {1.2f, 2.4f}, {2.4f, 4.8f} };
  EXPECT_EQ(a2.GetHealth(), ALIEN_HEALTH_START);
  EXPECT_EQ(a2.GetSpeed(), ALIEN_SPEED_SHOOT_START);

  Alien2D a3 = { {5.2f, 8.4f}, {3.4f, 7.8f}, 55, 90 };
  EXPECT_EQ(a3.GetHealth(), 55);
  EXPECT_EQ(a3.GetSpeed(), 90);

  // Setters test
  a3.SetHealth(15);
  a3.SetSpeed(25);
  EXPECT_EQ(a3.GetHealth(), 15);
  EXPECT_EQ(a3.GetSpeed(), 25);

  // Copy constructor
  Alien2D a4 = a2;
  EXPECT_EQ(a4, a2);
}

TEST(alien2d_test, test_assignment)
{
  Alien2D a1;
  a1 = { {1.2f, 2.4f}, {3.6f, 4.8f} };
  EXPECT_EQ(a1, Alien2D (Point2D(1.2f, 2.4f), Point2D(3.6f, 4.8f), ALIEN_HEALTH_START, ALIEN_SPEED_SHOOT_START));

  Alien2D a2;
  a2 = a1;
  EXPECT_EQ(a1, a2);
}
