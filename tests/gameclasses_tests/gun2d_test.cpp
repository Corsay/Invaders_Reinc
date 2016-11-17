#include "gtest/gtest.h"
#include "gameclasses/gun.hpp"
#include <sstream>
#include <unordered_set>

TEST(gun2d_test, test_construction)
{
  // default constructor
  Gun2D g1;
  EXPECT_EQ(g1.GetHealth(), GUN_HEALTH_START);
  EXPECT_EQ(g1.GetSpeed(), GUN_SPEED_SHOOT_START);
  EXPECT_EQ(g1.GetLives(), GUN_LIVES_START);
  EXPECT_EQ(g1.GetRate(), 0);

  // Constructors with parameters.
  Gun2D g2 = { {1.2f, 2.4f}, {2.4f, 4.8f} };
  EXPECT_EQ(g2.GetHealth(), GUN_HEALTH_START);
  EXPECT_EQ(g2.GetSpeed(), GUN_SPEED_SHOOT_START);
  EXPECT_EQ(g2.GetLives(), GUN_LIVES_START);
  EXPECT_EQ(g2.GetRate(), 0);

  Gun2D g3 = { {5.2f, 8.4f}, {3.4f, 7.8f}, 55, 90, 5 };
  EXPECT_EQ(g3.GetHealth(), 55);
  EXPECT_EQ(g3.GetSpeed(), 90);
  EXPECT_EQ(g3.GetLives(), 5);
  EXPECT_EQ(g3.GetRate(), 0);

  // Setters test
  g3.SetHealth(15);
  g3.SetSpeed(25);
  g3.SetLives(g3.GetLives() + 1);
  g3.SetRate(g3.GetRate() + 10);
  EXPECT_EQ(g3.GetHealth(), 15);
  EXPECT_EQ(g3.GetSpeed(), 25);
  EXPECT_EQ(g3.GetLives(), 6);
  EXPECT_EQ(g3.GetRate(), 10);

  // Copy constructor
  Gun2D g4 = g2;
  EXPECT_EQ(g4, g2);
}

TEST(gun2d_test, test_assignment)
{
  Gun2D g1;
  g1 = { {1.2f, 2.4f}, {3.6f, 4.8f} };
  EXPECT_EQ(g1, Gun2D (Point2D(1.2f, 2.4f), Point2D(3.6f, 4.8f), GUN_HEALTH_START, GUN_SPEED_SHOOT_START, GUN_LIVES_START));

  Gun2D g2;
  g2 = g1;
  EXPECT_EQ(g1, g2);
}

TEST(gun2d_test, test_throw)
{
  Gun2D g1;
  EXPECT_THROW(Gun2D({1.2f, 2.4f}, {3.6f, 4.8f}, 20.0f, 15.0f, 0), std::out_of_range);
}
