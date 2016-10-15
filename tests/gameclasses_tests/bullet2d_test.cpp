#include "gtest/gtest.h"
#include "gameclasses/bullet.hpp"
#include <sstream>
#include <unordered_set>

TEST(bullet2d_test, test_construction)
{
  // default constructor
  Bullet2D b1;
  EXPECT_EQ(b1.GetDamage(), BULLET_DAMAGE_START);
  EXPECT_EQ(b1.GetSpeed(), BULLET_SPEED_START);

  // Constructors with parameters.
  Bullet2D b2 = { {1.2f, 2.4f}, {2.4f, 4.8f} };
  EXPECT_EQ(b2.GetDamage(), BULLET_DAMAGE_START);
  EXPECT_EQ(b2.GetSpeed(), BULLET_SPEED_START);

  Bullet2D b3 = { {5.2f, 8.4f}, {3.4f, 7.8f}, 55, 90 };
  EXPECT_EQ(b3.GetDamage(), 55);
  EXPECT_EQ(b3.GetSpeed(), 90);

  // Setters test
  b3.SetDamage(15);
  b3.SetSpeed(25);
  EXPECT_EQ(b3.GetDamage(), 15);
  EXPECT_EQ(b3.GetSpeed(), 25);

  // Copy constructor
  Bullet2D b4 = b2;
  EXPECT_EQ(b4, b2);
}

TEST(bullet2d_test, test_assignment)
{
  Bullet2D b1;
  b1 = { {1.2f, 2.4f}, {3.6f, 4.8f} };
  EXPECT_EQ(b1, Bullet2D (Point2D(1.2f, 2.4f), Point2D(3.6f, 4.8f), BULLET_DAMAGE_START, BULLET_SPEED_START));

  Bullet2D b2;
  b2 = b1;
  EXPECT_EQ(b1, b2);
}

