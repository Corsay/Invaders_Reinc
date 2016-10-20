#include "gtest/gtest.h"
#include "gameclasses/movedgameentity.hpp"
#include <sstream>
#include <unordered_set>

TEST(movedgameentity2d_test, test_construction)
{
  // constructor
  MovedGameEntity2D mge1;
  EXPECT_EQ(mge1.GetLifeEntity(), LifeGameEntity2D (Point2D(0.0f, 0.0f), Point2D(0.0f, 0.0f), DEFAULT_HEALTH));
  EXPECT_EQ(mge1.GetHealth(), DEFAULT_HEALTH);
  EXPECT_EQ(mge1.GetSpeed(), DEFAULT_SPEED);

  // Constructors with parameters.
  MovedGameEntity2D mge2 = { {1.2f, 2.4f}, {2.4f, 4.8f}, 15 };
  EXPECT_EQ(mge2.GetLifeEntity(), LifeGameEntity2D (Point2D(1.2f, 2.4f), Point2D(2.4f, 4.8f), 15));
  EXPECT_EQ(mge2.GetHealth(), 15);
  EXPECT_EQ(mge2.GetSpeed(), DEFAULT_SPEED);

  MovedGameEntity2D mge3 = { Box2D{Point2D{5.2f, 8.4f}, Point2D{3.4f, 7.8f}}, 65, 10};
  EXPECT_EQ(mge3.GetLifeEntity(), LifeGameEntity2D (Point2D(5.2f, 8.4f), Point2D(3.4f, 7.8f), 65));
  EXPECT_EQ(mge3.GetHealth(), 65);
  EXPECT_EQ(mge3.GetSpeed(), 10);

  // Setters test
  mge3.SetLifeEntity(LifeGameEntity2D (Point2D(1.0f, 0.0f), Point2D(0.0f, 2.0f), 115));
  mge3.SetSpeed(5);
  EXPECT_EQ(mge3.GetLifeEntity(), LifeGameEntity2D (Point2D(1.0f, 0.0f), Point2D(0.0f, 2.0f), 115));
  EXPECT_EQ(mge3.GetSpeed(), 5);

  // Copy constructor
  MovedGameEntity2D mge4 = mge2;
  EXPECT_EQ(mge4, mge2);
}

TEST(movedgameentity2d_test, test_assignment)
{
  MovedGameEntity2D mge1;
  mge1 = { {1.2f, 2.4f}, {3.6f, 4.8f} };
  EXPECT_EQ(mge1, MovedGameEntity2D (Point2D(1.2f, 2.4f), Point2D(3.6f, 4.8f), DEFAULT_HEALTH, DEFAULT_SPEED));

  MovedGameEntity2D mge2;
  mge2 = mge1;
  EXPECT_EQ(mge1, mge2);
}

TEST(movedgameentity2d_test, test_throw)
{
  EXPECT_THROW(MovedGameEntity2D ({1.2f, 2.4f}, {3.6f, 4.8f}, 0, 20), std::out_of_range);
  EXPECT_THROW(MovedGameEntity2D ({1.2f, 2.4f}, {3.6f, 4.8f}, 10, 0), std::out_of_range);
}

TEST(movedgameentity2d_test, test_output)
{
  std::stringstream s;
  s << MovedGameEntity2D({1.2f, 0.2f},{2.4f, 0.4f});
  EXPECT_EQ(s.str(), "MovedGameEntity2D {LifeGameEntity2D {GameEntity2D {Box2D {Point2D {1.2, 0.2}, Point2D {2.4, 0.4}}}, Health: 50}, Speed: 0.5}");
}
