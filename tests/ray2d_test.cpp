#include "gtest/gtest.h"
#include "gameclasses/geometry/ray2d.hpp"
#include <sstream>
#include <unordered_set>

TEST(ray2d_test, test_construction)
{
  // Тест на создание объекта по умолчанию.
  Ray2D r1;
  EXPECT_EQ(r1.x(), 0.0f);
  EXPECT_EQ(r1.y(), 0.0f);
  EXPECT_EQ(r1.GetDirection(), 90.0f);
  // Тест на создание объекта с параметрами.
  Ray2D r2 = { 1.2f, 2.4f };
  EXPECT_EQ(r2.x(), 1.2f);
  EXPECT_EQ(r2.y(), 2.4f);
  EXPECT_EQ(r2.GetDirection(), 90.0f);
  // Тест на создание копии объекта.
  Ray2D r3 = r2;
  EXPECT_EQ(r3.x(), 1.2f);
  EXPECT_EQ(r3.y(), 2.4f);
  EXPECT_EQ(r3.GetDirection(), 90.0f);
}

TEST(ray2d_test, test_move)
{
    Ray2D r1 = { {1.2f, 2.4f}, 180.0f };
    Ray2D r3 = { -5.6f, 7.8f, 45.0f };
    // move constructor
    Ray2D r4 = std::move(r1);
    EXPECT_EQ(r1, Ray2D (Point2D {0, 0}, 90));
    EXPECT_EQ(r4, Ray2D (Point2D {1.2, 2.4}, 180));
    // move
    r1 = std::move(r3);
    EXPECT_EQ(r1, Ray2D (Point2D {-5.6, 7.8}, 45));
    EXPECT_EQ(r3, Ray2D (Point2D {0, 0}, 90));
}

TEST(ray2d_test, test_initializer_list)
{
  Ray2D r1 = { 1.0f, 2.0f, 37.0f };
  EXPECT_EQ(r1.x(), 1.0f);
  EXPECT_EQ(r1.y(), 2.0f);
  EXPECT_EQ(r1.GetDirection(), 37.0f);

  Ray2D r2 = { 1.0f };
  EXPECT_EQ(r2.x(), 1.0f);
  EXPECT_EQ(r2.y(), 0.0f);
  EXPECT_EQ(r2.GetDirection(), 90.0f);

  Ray2D r3 = { 1.0f, 2.0f, 90.0f, 17.58f };
  EXPECT_EQ(r3.x(), 1.0f);
  EXPECT_EQ(r3.y(), 2.0f);
  EXPECT_EQ(r3.GetDirection(), 90.0f);

  r1.SetDirection(360.0f);
  EXPECT_EQ(r1.GetDirection(), 0.0f);
  r1.SetDirection(405.0f);
  EXPECT_EQ(r1.GetDirection(), 45.0f);
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
  r1.DirectionShiftAngle(1000.0f);
  EXPECT_EQ(r1, Ray2D(1.0f, 0.0f, 325.0f));
  r1.DirectionShiftAngle(-350.0f);
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
  Box2D b1 = { {2.0f, 2.0f}, {7.0f, 6.0f} };

  // from bottom
  Ray2D r1={ 4.0f, 0.0f, 135.0f};  // left
  Ray2D r2={ 2.0f, 0.0f, 90.0f};   // up
  Ray2D r3={ 5.0f, 0.0f, 45.0f};   // right
  // from left
  Ray2D r4={ 0.0f, 4.0f, 0.0f};    // right
  Ray2D r5={ 0.0f, 4.0f, 45.0f};   // up
  Ray2D r6={ 0.0f, 4.0f, -45.0f};  // down
  // from top
  Ray2D r7={ 4.0f, 8.0f, -135.0f}; // left
  Ray2D r8={ 4.5f, 8.0f, 270.0f};  // down
  Ray2D r9={ 5.0f, 8.0f, -45.0f};  // right
  // from right
  Ray2D r10={ 9.0f, 4.0f, 135.0f}; // up
  Ray2D r11={ 9.0f, 4.0f, 180.0f}; // left
  Ray2D r12={ 9.0f, 4.0f, 225.0f}; // down
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

  Ray2D r21={ 2.0f, 2.0f-kEps*2, -90.0f}; // bottom Down  270
  Ray2D r22={ 2.0f-kEps*2, 6.0f, 180.0f}; // Left   Left  180
  Ray2D r23={ 7.0f, 6.0f+kEps*2, 90.0f};  // Top    Up    90
  Ray2D r24={ 7.0f+kEps*2, 2.0f, 0.0f};   // Right  Right 0

  EXPECT_FALSE(r21 && b1);
  EXPECT_FALSE(r22 && b1);
  EXPECT_FALSE(r23 && b1);
  EXPECT_FALSE(r24 && b1);

  Point2D p{2.0f, 3.0f};
  Ray2D r25{p, 0.0f};
  Ray2D r26{p, 45.0f};
  Ray2D r27{p, 90.0f};
  Ray2D r28{p, 135.0f};
  Ray2D r29{p, 180.0f};
  Ray2D r30{p, 225.0f};
  Ray2D r31{p, 270.0f};
  Ray2D r32{p, 315.0f};

  EXPECT_TRUE(r25 && b1);
  EXPECT_TRUE(r26 && b1);
  EXPECT_TRUE(r27 && b1);
  EXPECT_TRUE(r28 && b1);
  EXPECT_TRUE(r29 && b1);
  EXPECT_TRUE(r30 && b1);
  EXPECT_TRUE(r31 && b1);
  EXPECT_TRUE(r32 && b1);

  Point2D p2={4.3f, 5.3f};
  Point2D p3={0.7f, 1.7f};
  Ray2D r26_copy{p, 49.999f};

  EXPECT_TRUE(r26 && p2);
  EXPECT_FALSE(r26_copy && p3);

  EXPECT_FALSE(r26 && p3);
  r26.DirectionShiftAngle(180.0f);
  EXPECT_TRUE(r26 && p3);
}
