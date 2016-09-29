#include "gtest/gtest.h"
#include "box2d.hpp"
#include <sstream>
#include <unordered_set>


TEST(box2d_test, test_construction)
{
  // Тест на создание объекта по умолчанию.
  Box2D b1;
  EXPECT_EQ(b1.left_bottom(), Point2D(0.0f, 0.0f));
  EXPECT_EQ(b1.left_bottom().x(), 0.0f);
  EXPECT_EQ(b1.left_bottom().y(), 0.0f);
  EXPECT_EQ(b1.right_top(), Point2D(0.0f, 0.0f));
  EXPECT_EQ(b1.right_top().x(), 0.0f);
  EXPECT_EQ(b1.right_top().y(), 0.0f);

  // Тест на создание объекта с параметрами.
  Box2D b2 = { {1.2f, 2.4f}, {2.4f, 4.8f} };
  EXPECT_EQ(b2.left_bottom(), Point2D(1.2f, 2.4f));
  EXPECT_EQ(b2.left_bottom().x(), 1.2f);
  EXPECT_EQ(b2.left_bottom().y(), 2.4f);
  EXPECT_EQ(b2.right_top(), Point2D(2.4f, 4.8f));
  EXPECT_EQ(b2.right_top().x(), 2.4f);
  EXPECT_EQ(b2.right_top().y(), 4.8f);

  // Тест на создание копии объекта.
  Box2D b3 = b2;
  EXPECT_EQ(b3, b2);
}

TEST(box2d_test, test_initializer_list)
{
  Box2D b1 = { {1.0f, 2.0f}, {3.0f, 4.0f}, {5.0f, 6.0f} };
  EXPECT_EQ(b1.left_bottom(), Point2D(1.0f, 2.0f));
  EXPECT_EQ(b1.right_top(), Point2D(3.0f, 4.0f));

  Box2D b2 = { {1.0f, 2.0f} };
  EXPECT_EQ(b2.left_bottom(), Point2D(1.0f, 2.0f));
  EXPECT_EQ(b2.right_top(), Point2D(0.0f, 0.0f));
}

TEST(box2d_test, test_assignment)
{
  Box2D b1;
  b1 = { {1.2f, 2.4f}, {3.6f, 4.8f} };
  EXPECT_EQ(b1, Box2D(Point2D(1.2f, 2.4f), Point2D(3.6f, 4.8f)));
}

TEST(box2d_test, test_equality)
{
  Box2D b1 = { {1.2f, 2.4f}, {2.4f, 2.4f} };
  Box2D b2 = { {1.2f, 2.4f}, {2.4f, 2.4f} };
  Box2D b3 = { {1.3f, 2.4f}, {1.4f, 10.4f} };
  Box2D b4 = { {2.2f, 2.2f}, {7.2f, 6.5f} };

  EXPECT_EQ(b1, b2);
  EXPECT_NE(b1, b3);
  EXPECT_LT(b1, b3);
  EXPECT_LT(b1, b4);
}

TEST(box2d_test, test_calculus)
{
  Box2D b1 = { {1.2f, 2.4f}, {1.2f, 2.6f} };
  Box2D b2 = { {1.0f, 2.0f}, {0.6f, 2.0f} };

  EXPECT_EQ(b1 + b2, Box2D(Point2D(2.2f, 4.4f), Point2D(1.8f, 4.6f)));
  EXPECT_EQ(b1 - b2, Box2D(Point2D(0.2f, 0.4f), Point2D(0.6f, 0.6f)));
  EXPECT_EQ(b1 * 2.0f, Box2D(Point2D(2.4f, 4.8f), Point2D(2.4f, 5.2f)));
  EXPECT_EQ(b1 / 2.0f, Box2D(Point2D(0.6f, 1.2f), Point2D(0.6f, 1.3f)));

  b1 += { {1.2f, 2.4f}, {3.6f, 4.8f} };
  EXPECT_EQ(b1, Box2D(Point2D(2.4f, 4.8f), Point2D(4.8f, 7.4f)));

  b1 -= { {1.2f, 2.4f}, {3.6f, 4.8f} };
  EXPECT_EQ(b1, Box2D(Point2D(1.2f, 2.4f), Point2D(1.2f, 2.6f)));

  b1 *= 2.0f;
  EXPECT_EQ(b1, Box2D(Point2D(2.4f, 4.8f), Point2D(2.4f, 5.2f)));

  b1 /= 2.0f;
  EXPECT_EQ(b1, Box2D(Point2D(1.2f, 2.4f), Point2D(1.2f, 2.6f)));
}

TEST(box2d_test, test_square_brackets)
{
  Box2D b1 = { {1.2f, 2.4f}, {3.6f, 4.8f} };
  EXPECT_EQ(b1[0], Point2D(1.2f, 2.4f));
  EXPECT_EQ(b1[0][0], 1.2f);
  EXPECT_EQ(b1[0][1], 2.4f);
  EXPECT_EQ(b1[0][2], 0.0f);
  EXPECT_EQ(b1[1], Point2D(3.6f, 4.8f));
  EXPECT_EQ(b1[1][0], 3.6f);
  EXPECT_EQ(b1[1][1], 4.8f);
  EXPECT_EQ(b1[1][2], 0.0f);
  EXPECT_EQ(b1[2], Point2D(0.0f, 0.0f));
  EXPECT_EQ(b1[2][0], 0.0f);
  EXPECT_EQ(b1[2][1], 0.0f);
}

TEST(box2d_test, test_center)
{
  Box2D b1 = { {1.2f, 2.4f}, {3.6f, 4.8f} };
  Box2D b2 = { {2.0f, 2.0f}, {7.0f, 6.0f} };
  EXPECT_EQ(b1.get_center(), Point2D(2.4, 3.6));
  EXPECT_EQ(b2.get_center(), Point2D(4.5, 4));
}

TEST(box2d_test, test_intersection)
{
  Box2D b13 = { {2.0f, 2.0f}, {7.0f, 6.0f} };
  Box2D b14 = { {7.0f, 2.0f}, {13.0f, 6.0f} };
  Box2D b15 = { {8.0f, 2.0f}, {13.0f, 6.0f} };
  Box2D b16 = { {-5.0f, 3.0f}, {7.0f, 2.0f} };
  Box2D b17 = { {3.0f, 3.0f}, {6.0f, 5.0f} };

  EXPECT_EQ(b13.check_intersection(b14), 1); // left
  EXPECT_EQ(b13.check_intersection(b15), 0); // not intersect
  EXPECT_EQ(b13.check_intersection(b16), 1); // bottom
  EXPECT_EQ(b13.check_intersection(b17), 1); // inside
}

TEST(box2d_test, test_hash)
{
  Box2D::Hash hasher;
  Box2D b1;
  EXPECT_EQ(hasher(b1), 0);
  EXPECT_EQ(hasher(Box2D(Point2D(0.0f, 0.0f), Point2D(0.0f, 0.0f))), 0);

  std::unordered_set<Box2D, Box2D::Hash> hashTable;
  hashTable.insert(Box2D(Point2D(0.0f, 0.0f), Point2D(0.0f, 0.0f)));
  hashTable.insert(Box2D(Point2D(1.0f, 0.0f), Point2D(0.0f, 2.0f)));
  EXPECT_EQ(hashTable.size(), 2);
}

TEST(box2d_test, test_output)
{
  std::stringstream s;
  s << Box2D({1.2f, 0.2f},{2.4f, 0.4f});
  EXPECT_EQ(s.str(), "Box2D {Point2D {1.2, 0.2}, Point2D {2.4, 0.4}}");
}
