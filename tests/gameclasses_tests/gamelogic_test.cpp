#include "gtest/gtest.h"
#include "gameclasses/space.hpp"


TEST(gamelogic_test, alien_intersection)
{
    Alien2DManager al(1, 2);
    Bullet2D b1( Point2D{155.0f, 90.0f}, Point2D{165.0f, 100.0f});
    Bullet2D b2( Point2D{165.0f, 100.0f}, Point2D{175.0f, 110.0f});
    Bullet2D b3( Point2D{95.0f, 115.0f}, Point2D{105.0f, 125.0f});
    Bullet2D b4( Point2D{121.0f, 62.0f}, Point2D{133.0f, 74.0f});

    EXPECT_FALSE(al.CheckIntersection(b1));
    EXPECT_TRUE(al.CheckIntersection(b2));
    EXPECT_TRUE(al.CheckIntersection(b3));
    EXPECT_FALSE(al.CheckIntersection(b4));
}

TEST(gun_test, alien_intersection)
{
    Gun2D g( Point2D{100.0f, 80.0f}, Point2D{150.0f,120.0f});
    Bullet2D b1( Point2D{155.0f, 90.0f}, Point2D{165.0f, 100.0f});
    Bullet2D b2( Point2D{95.0f, 115.0f}, Point2D{105.0f, 125.0f});
    Bullet2D b3( Point2D{121.0f, 62.0f}, Point2D{133.0f, 74.0f});

    EXPECT_FALSE(g.CheckIntersection(b1));
    EXPECT_TRUE(g.CheckIntersection(b2));
    EXPECT_FALSE(g.CheckIntersection(b3));
}

TEST(obstacle_test, alien_intersection)
{
    Obstacle2DManager O(2);
    Bullet2D b1( Point2D{155.0f, 90.0f}, Point2D{165.0f, 100.0f});
    Bullet2D b2( Point2D{95.0f, 175.0f}, Point2D{105.0f, 185.0f});
    Bullet2D b3( Point2D{121.0f, 62.0f}, Point2D{133.0f, 74.0f});

    EXPECT_FALSE(O.CheckIntersection(b1));
    EXPECT_TRUE(O.CheckIntersection(b2));
    EXPECT_FALSE(O.CheckIntersection(b3));
}

