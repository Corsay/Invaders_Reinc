#include "gtest/gtest.h"
#include "gameclasses/lifegameentity.hpp"
#include <sstream>
#include <unordered_set>

TEST(lifegameentity2d_test, test_construction)
{
  // constructor
  LifeGameEntity2D lge1;
  EXPECT_EQ(lge1.GetEntity(), GameEntity2D (Point2D(0.0f, 0.0f), Point2D(0.0f, 0.0f)));
  EXPECT_EQ(lge1.GetHealth(), DEFAULT_HEALTH);

  // Constructors with parameters.
  LifeGameEntity2D lge2 = { {1.2f, 2.4f}, {2.4f, 4.8f} };
  EXPECT_EQ(lge2.GetEntity(), GameEntity2D (Point2D(1.2f, 2.4f), Point2D(2.4f, 4.8f)));
  EXPECT_EQ(lge2.GetHealth(), DEFAULT_HEALTH);

  LifeGameEntity2D lge3 = { Box2D{Point2D{5.2f, 8.4f}, Point2D{3.4f, 7.8f}}, 55};
  EXPECT_EQ(lge3.GetEntity(), GameEntity2D (Point2D(5.2f, 8.4f), Point2D(3.4f, 7.8f)));
  EXPECT_EQ(lge3.GetHealth(), 55);

  // Setters test
  lge3.SetEntity(GameEntity2D (Point2D(1.0f, 0.0f), Point2D(0.0f, 2.0f)));
  lge3.SetHealth(25);
  EXPECT_EQ(lge3.GetEntity(), GameEntity2D (Point2D(1.0f, 0.0f), Point2D(0.0f, 2.0f)));
  EXPECT_EQ(lge3.GetHealth(), 25);

  // Copy constructor
  LifeGameEntity2D lge4 = lge2;
  EXPECT_EQ(lge4, lge2);
}

TEST(lifegameentity2d_test, test_assignment)
{
  LifeGameEntity2D lge1;
  lge1 = { {1.2f, 2.4f}, {3.6f, 4.8f} };
  EXPECT_EQ(lge1, LifeGameEntity2D (Point2D(1.2f, 2.4f), Point2D(3.6f, 4.8f), DEFAULT_HEALTH));

  LifeGameEntity2D lge2;
  lge2 = lge1;
  EXPECT_EQ(lge1, lge2);
}

TEST(lifegameentity2d_test, test_throw)
{
  EXPECT_THROW(LifeGameEntity2D ({1.2f, 2.4f}, {3.6f, 4.8f}, 0), std::out_of_range);
}

TEST(lifegameentity2d_test, test_output)
{
  std::stringstream s;
  s << LifeGameEntity2D({1.2f, 0.2f},{2.4f, 0.4f});
  EXPECT_EQ(s.str(), "LifeGameEntity2D {GameEntity2D {Box2D {Point2D {1.2, 0.2}, Point2D {2.4, 0.4}}}, Health: 50}");
}
