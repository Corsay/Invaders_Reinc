#include "gtest/gtest.h"
#include "ray2d.hpp"
#include <sstream>
#include <unordered_set>

TEST(ray2d_test, test_construction)
{
  // Тест на создание объекта по умолчанию.
  Ray2D r1;
  EXPECT_EQ(r1.x(), 0.0f);
  EXPECT_EQ(r1.y(), 0.0f);
  EXPECT_EQ(r1.direction(), 90.0f);
  // Тест на создание объекта с параметрами.
  Ray2D r2 = { 1.2f, 2.4f };
  EXPECT_EQ(r2.x(), 1.2f);
  EXPECT_EQ(r2.y(), 2.4f);
  EXPECT_EQ(r2.direction(), 90.0f);
  // Тест на создание копии объекта.
  Ray2D r3 = r2;
  EXPECT_EQ(r3.x(), 1.2f);
  EXPECT_EQ(r3.y(), 2.4f);
  EXPECT_EQ(r3.direction(), 90.0f);
}

TEST(ray2d_test, test_initializer_list)
{
  Ray2D r1 = { 1.0f, 2.0f, 37.0f };
  EXPECT_EQ(r1.x(), 1.0f);
  EXPECT_EQ(r1.y(), 2.0f);
  EXPECT_EQ(r1.direction(), 37.0f);

  Ray2D r2 = { 1.0f };
  EXPECT_EQ(r2.x(), 1.0f);
  EXPECT_EQ(r2.y(), 0.0f);
  EXPECT_EQ(r2.direction(), 90.0f);

  Ray2D r3 = { 1.0f, 2.0f, 90.0f, 17.58f };
  EXPECT_EQ(r3.x(), 1.0f);
  EXPECT_EQ(r3.y(), 2.0f);
  EXPECT_EQ(r3.direction(), 90.0f);

  r1.direction(360.0f);
  EXPECT_EQ(r1.direction(), 0.0f);
  r1.direction(405.0f);
  EXPECT_EQ(r1.direction(), 45.0f);
}

TEST(ray2d_test, test_assignment)
{
  Ray2D r1;
  r1 = { 1.2f, 2.4f };
  EXPECT_EQ(r1, Ray2D(1.2f, 2.4f, 90.0f));
}

TEST(ray2d_test, test_equality)
{
  Ray2D p1 = { 1.2f, 2.4f };
  Ray2D p2 = { 1.2f, 2.4f };
  Ray2D p3 = { 1.3f, 2.4f };
  Ray2D p4 = { 1.2f, 2.5f };

  EXPECT_EQ(p1, p2);
  EXPECT_NE(p1, p3);
}

TEST(ray2d_test, test_calculus)
{
  Ray2D r1 = { 1.0f, 1.0f, 45.0f };

  r1.VerticalShift(2.0f);
  EXPECT_EQ(r1, Ray2D(1.0f, 3.0f, 45.0f));
  r1.VerticalShift(-3.0f);
  EXPECT_EQ(r1, Ray2D(1.0f, 0.0f, 45.0f));
  r1.DirectionShift(1000.0f);
  EXPECT_EQ(r1, Ray2D(1.0f, 0.0f, 325.0f));
  r1.DirectionShift(-350.0f);
  EXPECT_EQ(r1, Ray2D(1.0f, 0.0f, 335.0f));
}

TEST(ray2d_test, test_square_brackets)
{
  Ray2D p1 = { 1.2f, 2.4f, 30.0f };
  EXPECT_EQ(p1[0], 1.2f);
  EXPECT_EQ(p1[1], 2.4f);
  EXPECT_EQ(p1[2], 30.0f);
  EXPECT_EQ(p1[3], 00.0f);
}

TEST(ray2d_test, test_Ray2D_output)
{
  std::stringstream s;
  s << Ray2D(1.2f, 0.2f, 13.2f);
  EXPECT_EQ(s.str(), "Ray2D {Point2D {1.2, 0.2}, 13.2}");
}

TEST(ray2d_test, test_intersection)
{
  //Box2D b1 = { {-1.0f, 1.0f}, {1.0f, 2.0f} };
  //Box2D b2 = { {-2.0f, 11.0f}, {-1.0f, 1.0f} };
  //Box2D b3 = { {-1.0f, 1.0f}, {1.0f, 2.0f} };
  //Box2D b4 = { {-1.0f, 1.0f}, {1.0f, 2.0f} };

  //Ray2D r1={ 0.0f, 0.0f, 45.0f};
  //Ray2D r2={ 0.0f, 0.0f, 90.0f};
  //EXPECT_TRUE(r1 && b1);
  //EXPECT_TRUE(r2 && b1);

  Box2D b1 = { {2.0f, 2.0f}, {7.0f, 6.0f} };

  // from bottom
  Ray2D r1={ 4.0f, 0.0f, 135.0f};
  Ray2D r2={ 2.0f, 0.0f, 90.0f};
  Ray2D r3={ 5.0f, 0.0f, 45.0f};
  // from left
  Ray2D r4={ 0.0f, 4.0f, 0.0f};
  Ray2D r5={ 0.0f, 4.0f, 45.0f};
  Ray2D r6={ 0.0f, 4.0f, -45.0f};
  // from top
  Ray2D r7={ 4.5f, 8.0f, 270.0f};
  Ray2D r8={ 4.0f, 8.0f, -135.0f};
  Ray2D r9={ 5.0f, 8.0f, -45.0f};
  // from right
  Ray2D r10={ 9.0f, 4.0f, 135.0f};
  Ray2D r11={ 9.0f, 4.0f, 180.0f};
  Ray2D r12={ 9.0f, 4.0f, 225.0f};
  // near box
  Ray2D r13={ 2.0f-kEps*2, 2.0f-kEps*2, 90.0f};  // bottom UP    90
  Ray2D r14={ 2.0f-kEps*2, 2.0f-kEps*2, 0.0f};   // bottom Right 0
  Ray2D r15={ 7.0f+kEps*2, 2.0f-kEps*2, 180.0f}; // bottom LEFT  180
  Ray2D r16={ 7.0f+kEps*2, 2.0f-kEps*2, 90.0f};  // bottom UP    90
  Ray2D r17={ 7.0f+kEps*2, 6.0f+kEps*2, -90.0f}; // bottom Down  270
  Ray2D r18={ 7.0f+kEps*2, 6.0f+kEps*2, 180.0f}; // bottom Left  180
  Ray2D r19={ 2.0f-kEps*2, 6.0f+kEps*2, 0.0f};   // bottom Right 0
  Ray2D r20={ 2.0f-kEps*2, 6.0f+kEps*2, -90.0f}; // bottom Down  270

  // check
  EXPECT_TRUE(r1 && b1);
  EXPECT_TRUE(r2 && b1);
  EXPECT_TRUE(r3 && b1);
  EXPECT_TRUE(r4 && b1);
  EXPECT_TRUE(r5 && b1);
  EXPECT_TRUE(r6 && b1);
  EXPECT_TRUE(r7 && b1);
  EXPECT_TRUE(r8 && b1);
  EXPECT_TRUE(r9 && b1);
  EXPECT_TRUE(r10 && b1);
  EXPECT_TRUE(r11 && b1);
  EXPECT_TRUE(r12 && b1);
  EXPECT_FALSE(r13 && b1);
  EXPECT_FALSE(r14 && b1);
  EXPECT_FALSE(r15 && b1);
  EXPECT_FALSE(r16 && b1);
  EXPECT_FALSE(r17 && b1);
  EXPECT_FALSE(r18 && b1);
  EXPECT_FALSE(r19 && b1);
  EXPECT_FALSE(r20 && b1);
}
