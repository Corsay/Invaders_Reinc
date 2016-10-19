#include "gtest/gtest.h"
#include "gameclasses/space.hpp"
#include <sstream>
#include <unordered_set>

TEST(space2d_test, test_construction)
{
  // constructor
  Space2D s1;
  EXPECT_EQ(s1.CheckGameState(), 0);

  // Constructors with parameters.
  Space2D s2 = { {0.0f, 0.0f}, {1024.0f, 720.0f} };
  EXPECT_EQ(s2.GetBox(), Box2D( Point2D(0.0f, 720.0f), Point2D(1024.0f, 0.0f)));

  Space2D s3 = { {5.2f, 8.4f}, {3.4f, 7.8f}};
  EXPECT_EQ(s3.GetBox(), Box2D( Point2D(5.2f, 8.4f), Point2D(3.4f, 7.8f)));
}

TEST(space2d_test, test_throw)
{
  Space2D s1;
  EXPECT_THROW(s1.GameStep(), std::runtime_error);
  EXPECT_THROW(s1.GunMove(), std::runtime_error);
  EXPECT_THROW(s1.RedrawSpace(), std::runtime_error);
  EXPECT_THROW(s1.NewLvlPrepare(1), std::runtime_error);
}
