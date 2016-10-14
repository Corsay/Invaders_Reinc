#include "gtest/gtest.h"
#include "gameclasses/alien.hpp"
#include <sstream>
#include <unordered_set>

TEST(alien2d_test, test_construction)
{
  // Тест на создание объекта по умолчанию.
  Box2D b1;
  EXPECT_EQ(b1.leftBottom(), Point2D(0.0f, 0.0f));
  EXPECT_EQ(b1.leftBottom().x(), 0.0f);
  EXPECT_EQ(b1.leftBottom().y(), 0.0f);
  EXPECT_EQ(b1.rightTop(), Point2D(0.0f, 0.0f));
  EXPECT_EQ(b1.rightTop().x(), 0.0f);
  EXPECT_EQ(b1.rightTop().y(), 0.0f);

  // Тест на создание объекта с параметрами.
  Box2D b2 = { {1.2f, 2.4f}, {2.4f, 4.8f} };
  EXPECT_EQ(b2.leftBottom(), Point2D(1.2f, 2.4f));
  EXPECT_EQ(b2.leftBottom().x(), 1.2f);
  EXPECT_EQ(b2.leftBottom().y(), 2.4f);
  EXPECT_EQ(b2.rightTop(), Point2D(2.4f, 4.8f));
  EXPECT_EQ(b2.rightTop().x(), 2.4f);
  EXPECT_EQ(b2.rightTop().y(), 4.8f);

  Box2D b3 = { 1.0f, 2.2f, 0.0f, 1.0f };
  EXPECT_EQ(b3.leftBottom(), Point2D(0.0f, 1.0f));
  EXPECT_EQ(b3.leftBottom().x(), 0.0f);
  EXPECT_EQ(b3.leftBottom().y(), 1.0f);
  EXPECT_EQ(b3.rightTop(), Point2D(1.0f, 2.2f));
  EXPECT_EQ(b3.rightTop().x(), 1.0f);
  EXPECT_EQ(b3.rightTop().y(), 2.2f);

  // Тест на создание копии объекта.
  Box2D b4 = b3;
  EXPECT_EQ(b4, b3);
}
