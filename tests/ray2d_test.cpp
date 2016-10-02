#include "gtest/gtest.h"
#include "geometry.hpp"
#include <sstream>
#include <unordered_set>

TEST(ray2d_test, test_construction)
{
  // Тест на создание объекта по умолчанию.
  Ray2D r1;
  EXPECT_EQ(r1.X(), 0.0f);
  EXPECT_EQ(r1.Y(), 0.0f);
  EXPECT_EQ(r1.direction(), 0.0f);
  // Тест на создание объекта с параметрами.
  Ray2D r2 = { 1.2f, 2.4f };
  EXPECT_EQ(r2.X(), 1.2f);
  EXPECT_EQ(r2.Y(), 2.4f);
  EXPECT_EQ(r2.direction(), 0.0f);
  // Тест на создание копии объекта.
  Ray2D r3 = r2;
  EXPECT_EQ(r3.X(), 1.2f);
  EXPECT_EQ(r3.Y(), 2.4f);
  EXPECT_EQ(r3.direction(), 0.0f);
}

TEST(ray2d_test, test_initializer_list)
{
  Ray2D r1 = { 1.0f, 2.0f, 37.0f };
  EXPECT_EQ(r1.X(), 1.0f);
  EXPECT_EQ(r1.Y(), 2.0f);
  EXPECT_EQ(r1.direction(), 37.0f);

  Ray2D r2 = { 1.0f };
  EXPECT_EQ(r2.X(), 1.0f);
  EXPECT_EQ(r2.Y(), 0.0f);
  EXPECT_EQ(r2.direction(), 0.0f);

  Ray2D r3 = { 1.0f, 2.0f, 90.0f, 17.58f };
  EXPECT_EQ(r3.X(), 1.0f);
  EXPECT_EQ(r3.Y(), 2.0f);
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
  EXPECT_EQ(r1, Ray2D(1.2f, 2.4f, 0.0f));
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

/*TEST(ray2d_test, test_hash)
{
  Ray2D::Hash hasher;
  EXPECT_EQ(hasher(Ray2D(0.0f, 0.0f)), 0);

  std::unordered_set<Ray2D, Ray2D::Hash> hashTable;
  hashTable.insert(Ray2D(0.0f, 0.0f));
  hashTable.insert(Ray2D(1.0f, 0.0f));
  EXPECT_EQ(hashTable.size(), 2);
}*/

TEST(ray2d_test, test_Ray2D_output)
{
  std::stringstream s;
  s << Ray2D(1.2f, 0.2f, 13.2f);
  EXPECT_EQ(s.str(), "Ray2D {Point2D {1.2, 0.2}, 13.2}");
}

/*TEST(ray2d_test, test_intersection)
{
  Box2D b1 = { {-1.0f, 1.0f}, {1.0f, 2.0f} };
  Box2D b2 = { {-2.0f, 11.0f}, {-1.0f, 1.0f} };
  Box2D b3 = { {-1.0f, 1.0f}, {1.0f, 2.0f} };
  Box2D b4 = { {-1.0f, 1.0f}, {1.0f, 2.0f} };


  Ray2D r1={ 0.0f, 0.0f, 45.0f};
  Ray2D r2={ 0.0f, 0.0f, 90.0f};

  //EXPECT_TRUE(r1 && b1);
  EXPECT_TRUE(r2 && b1);




}*/
