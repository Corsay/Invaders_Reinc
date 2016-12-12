#include "gtest/gtest.h"
#include "gameclasses/ship.hpp"
#include <sstream>
#include <unordered_set>


TEST(ship2d_test, test_construction)
{
  // default constructor
  Ship2D s1;
  EXPECT_EQ(s1.GetHealth(), SHIP_HEALTH_START);
  EXPECT_EQ(s1.GetSpeed(), SHIP_SPEED_START);

  // Constructors with parameters.
  Ship2D s2 = { {1.2f, 2.4f}, {2.4f, 4.8f} };
  EXPECT_EQ(s2.GetHealth(), SHIP_HEALTH_START);
  EXPECT_EQ(s2.GetSpeed(), SHIP_SPEED_START);

  Ship2D s3 = { {5.2f, 8.4f}, {3.4f, 7.8f}, 55, 90 };
  EXPECT_EQ(s3.GetHealth(), 55);
  EXPECT_EQ(s3.GetSpeed(), 90);

  // Setters test
  s3.SetHealth(15);
  s3.SetSpeed(25);
  EXPECT_EQ(s3.GetHealth(), 15);
  EXPECT_EQ(s3.GetSpeed(), 25);

  // Copy constructor
  Ship2D s4 = s2;
  EXPECT_EQ(s4, s2);
}

TEST(ship2d_test, test_assignment)
{
  Ship2D s1;
  s1 = { {1.2f, 2.4f}, {3.6f, 4.8f} };
  EXPECT_EQ(s1, Ship2D (Point2D(1.2f, 2.4f), Point2D(3.6f, 4.8f), SHIP_HEALTH_START, SHIP_SPEED_START));

  Ship2D s2;
  s2 = s1;
  EXPECT_EQ(s1, s2);
}

TEST(ship2d_test, test_intersection_and_bonus)
{
  Ship2D s1;
  s1 = { {1.2f, 2.4f}, {3.6f, 4.8f} };
  EXPECT_EQ(s1, Ship2D (Point2D(1.2f, 2.4f), Point2D(3.6f, 4.8f), SHIP_HEALTH_START, SHIP_SPEED_START));

  Bullet2D b1 { {1.2f, 2.4f}, {3.6f, 4.8f} };
  b1.SetUpdateHandler([&](GameEntity2D const & ge){ logger << "the bullet from the gun hit in " << ge << std::endl; });
  Bullet2D b2 { {100.0f, 200.4f}, {150.0f, 250.8f} };

  EXPECT_TRUE(s1.CheckIntersection(b1));
  EXPECT_FALSE(s1.CheckIntersection(b2));
}
