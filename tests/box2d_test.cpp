#include "gtest/gtest.h"
#include "box2d.hpp"
#include <sstream>
#include <unordered_set>


TEST(box2d_test, test_construction)
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

TEST(box2d_test, test_move)
{
    Box2D b1 = { {1.2f, 2.4f}, {3.6f, 4.8f} };
    Box2D b3 = { -5.6f, 7.8f };
    // move constructor
    Box2D b4 = std::move(b1);
    EXPECT_EQ(b1, Box2D(Point2D {0, 0}, Point2D {0, 0}));
    EXPECT_EQ(b4, Box2D(Point2D {1.2, 2.4}, Point2D {3.6, 4.8}));
    // move
    b1 = std::move(b3);
    EXPECT_EQ(b1, Box2D(Point2D {-5.6, 0}, Point2D {0, 7.8}));
    EXPECT_EQ(b3, Box2D(Point2D {0, 0}, Point2D {0, 0}));
}

TEST(box2d_test, test_initializer_list)
{
  Box2D b1 = { {1.0f, 2.0f}, {3.0f, 4.0f}, {0.0f, 1.0f} };
  EXPECT_EQ(b1.leftBottom(), Point2D(1.0f, 2.0f));
  EXPECT_EQ(b1.rightTop(), Point2D(3.0f, 4.0f));

  Box2D b2 = { {1.0f, 2.0f} };
  EXPECT_EQ(b2.leftBottom(), Point2D(0.0f, 0.0f)); // because swap
  EXPECT_EQ(b2.rightTop(), Point2D(1.0f, 2.0f));

  Box2D b3 = { 3.0f, 4.0f, 1.0f, 2.0f, 5.0f };
  EXPECT_EQ(b3.leftBottom(), Point2D(1.0f, 2.0f)); // because swap
  EXPECT_EQ(b3.rightTop(), Point2D(3.0f, 4.0f));

  Box2D b4 = { 1.0f, 2.0f };
  EXPECT_EQ(b4.leftBottom(), Point2D(0.0f, 0.0f)); // because swap
  EXPECT_EQ(b4.rightTop(), Point2D(1.0f, 2.0f));
}

TEST(box2d_test, test_swap)
{
  Box2D b1 = { 0.0f, 0.0f, -5.6f, 7.8f };
  Box2D b2 = { 0.0f, 0.0f, 5.6f, -7.8f };
  Box2D b3 = { 0.0f, 0.0f, 5.6f, 7.8f };
  Box2D b4 = { 0.0f, 0.0f, -5.6f, -7.8f };
  Box2D b5 = { -5.5f, 7.7f, -5.6f, 7.8f };
  Box2D b6 = { 5.5f, -7.7f, 5.6f, -7.8f };
  Box2D b7 = { 5.6f, 7.7f, 5.5f, 7.8f };
  Box2D b8 = { 3.2f, 5.4f, -3.1f, 1.9f };
  // input left_top and right_bottom points
  EXPECT_EQ(b1, Box2D (Point2D {-5.6, 0}, Point2D {0, 7.8}));
  EXPECT_EQ(b2, Box2D (Point2D {0, -7.8}, Point2D {5.6, 0}));
  EXPECT_EQ(b3, Box2D (Point2D {0, 0}, Point2D {5.6, 7.8}));
  EXPECT_EQ(b4, Box2D (Point2D {-5.6, -7.8}, Point2D {0, 0}));
  EXPECT_EQ(b5, Box2D (Point2D {-5.6, 7.7}, Point2D {-5.5, 7.8}));
  EXPECT_EQ(b6, Box2D (Point2D {5.5, -7.8}, Point2D {5.6, -7.7}));
  EXPECT_EQ(b7, Box2D (Point2D {5.5, 7.7}, Point2D {5.6, 7.8}));
  // input point in the wrong order
  EXPECT_EQ(b8, Box2D (Point2D {-3.1, 1.9}, Point2D {3.2, 5.4}));
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
  EXPECT_LT(b1, b3);//if(b1<b3)
  EXPECT_LT(b1, b4);
}

TEST(box2d_test, test_calculus)
{
  Box2D b1 = { {1.2f, 2.4f}, {1.2f, 2.6f} };
  Box2D b2 = { {1.0f, 2.0f}, {0.6f, 2.0f} };
  //after swap b2={ {0.6f, 2.0f}, {1.0f, 2.0f} };

  EXPECT_EQ(b1 + b2, Box2D(Point2D(1.8f, 4.4f), Point2D(2.2f, 4.6f)));
  EXPECT_EQ(b1 - b2, Box2D(Point2D(0.6f, 0.4f), Point2D(0.2f, 0.6f)));
  EXPECT_EQ(b1 * 2.0f, Box2D(Point2D(2.4f, 4.8f), Point2D(2.4f, 5.2f)));
  EXPECT_EQ(b1 / 2.0f, Box2D(Point2D(0.6f, 1.2f), Point2D(0.6f, 1.3f)));

  b2.HorizontalShift(2.0f);
  EXPECT_EQ(b2, Box2D(Point2D(2.6f, 2.0f), Point2D(3.0f, 2.0f)));
  b2.HorizontalShift(-5.0);
  EXPECT_EQ(b2, Box2D(Point2D(-2.4f, 2.0f), Point2D(-2.0f, 2.0f)));

  b2.VerticalShift(3.2f);
  EXPECT_EQ(b2, Box2D(Point2D(-2.4f, 5.2f), Point2D(-2.0f, 5.2f)));
  b2.VerticalShift(-2.5);
  EXPECT_EQ(b2, Box2D(Point2D(-2.4f, 2.7f), Point2D(-2.0f, 2.7f)));

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
  EXPECT_EQ(b1.Get_center(), Point2D(2.4, 3.6));
  EXPECT_EQ(b2.Get_center(), Point2D(4.5, 4));
}

TEST(box2d_test, test_intersection)
{
  Box2D b1 = { {2.0f, 2.0f}, {7.0f, 6.0f} };
  Box2D b2 = { {7.0f, 2.0f}, {13.0f, 6.0f} };
  Box2D b3 = { {8.0f, 2.0f}, {13.0f, 6.0f} };
  Box2D b4 = { {-5.0f, 3.0f}, {7.0f, 2.0f} };
  Box2D b5 = { {3.0f, 3.0f}, {6.0f, 5.0f} };

  EXPECT_EQ((b1 && b2), 1); // left
  EXPECT_EQ((b1 && b3), 0); // not intersect
  EXPECT_EQ((b1 && b4), 1); // bottom
  EXPECT_EQ((b1 && b5), 1); // inside

  // point in box
  Point2D p1={3.0f, 3.0f};
  Point2D p2={2.0f, 2.0f};
  Point2D p3={1.0f, 1.0f};

  EXPECT_TRUE(b1 && p1);
  EXPECT_TRUE(b1 && p2);
  EXPECT_FALSE(b1 && p3);
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
