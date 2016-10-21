#include "gtest/gtest.h"
#include "gameclasses/gameentity.hpp"
#include <sstream>
#include <unordered_set>

TEST(gameentity2d_test, test_construction)
{
  // default constructor
  GameEntity2D ge1;
  EXPECT_EQ(ge1.GetBox(), Box2D(Point2D(0.0f, 0.0f), Point2D(0.0f, 0.0f)));
  EXPECT_EQ(ge1.GetEntity(), GameEntity2D (Box2D(Point2D(0.0f, 0.0f), Point2D(0.0f, 0.0f))));

  // Constructors with parameters.
  GameEntity2D ge2 = { {1.2f, 2.4f}, {2.4f, 4.8f} };
  EXPECT_EQ(ge2.GetBox(), Box2D(Point2D(1.2f, 2.4f), Point2D(2.4f, 4.8f)));
  EXPECT_EQ(ge2.GetEntity(), GameEntity2D (Point2D(1.2f, 2.4f), Point2D(2.4f, 4.8f)));

  // Setters test
  ge1.SetBox(Box2D(Point2D(2.4f, 3.4f), Point2D(3.6f, 6.0f)));
  EXPECT_EQ(ge1.GetBox(), Box2D(Point2D(2.4f, 3.4f), Point2D(3.6f, 6.0f)));
  EXPECT_EQ(ge1.GetEntity(), GameEntity2D (Box2D(Point2D(2.4f, 3.4f), Point2D(3.6f, 6.0f))));
  ge1.SetEntity(GameEntity2D(Box2D(Point2D(0.4f, 1.4f), Point2D(1.6f, 2.0f))));
  EXPECT_EQ(ge1.GetBox(), Box2D(Point2D(0.4f, 1.4f), Point2D(1.6f, 2.0f)));
  EXPECT_EQ(ge1.GetEntity(), GameEntity2D (Point2D(0.4f, 1.4f), Point2D(1.6f, 2.0f)));

  // Copy constructor
  GameEntity2D ge3 = ge2;
  EXPECT_EQ(ge3, ge2);
}

TEST(gameentity2d_test, test_assignment)
{
  GameEntity2D ge1;
  ge1 = { {1.2f, 2.4f}, {3.6f, 4.8f} };
  EXPECT_EQ(ge1, GameEntity2D (Box2D(Point2D(1.2f, 2.4f), Point2D(3.6f, 4.8f))));

  GameEntity2D ge2;
  ge2 = ge1;
  EXPECT_EQ(ge1, ge2);
}

TEST(gameentity2d_test, test_output)
{
  std::stringstream s;
  s << GameEntity2D({1.2f, 0.2f},{2.4f, 0.4f});
  EXPECT_EQ(s.str(), "GameEntity2D {Box2D {Point2D {1.2, 0.2}, Point2D {2.4, 0.4}}}");
}
