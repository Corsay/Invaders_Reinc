#include "gtest/gtest.h"
#include "gameclasses/bulletmanager.hpp"
#include <sstream>
#include <unordered_set>

TEST(bullet2dmanager_test, test_construction)
{
  // default constructor
  Bullet2DManager bm1;
  EXPECT_EQ(bm1.GetCountOfAlienBullets(), 0);
  EXPECT_EQ(bm1.GetCountOfGunBullets(), 0);
}

TEST(bullet2dmanager_test, test_add_bullets)
{
  Bullet2DManager bm1;
  EXPECT_EQ(bm1.GetCountOfAlienBullets(), 0);
  EXPECT_EQ(bm1.GetCountOfGunBullets(), 0);

  // add gun bullet
  bm1.NewBullet(
    Bullet2D(),
    Gun
  );
  EXPECT_EQ(bm1.GetCountOfAlienBullets(), 0);
  EXPECT_EQ(bm1.GetCountOfGunBullets(), 1);

  // add alien bullet
  bm1.NewBullet(
    Bullet2D(),
    Alien
  );
  EXPECT_EQ(bm1.GetCountOfAlienBullets(), 1);
  EXPECT_EQ(bm1.GetCountOfGunBullets(), 1);
}

TEST(bullet2dmanager_test, test_throw)
{
  Bullet2DManager bm1;
  EXPECT_THROW(bm1.CheckAllInterections(), std::runtime_error);
  EXPECT_THROW(bm1.BulletsMove(Box2D{}), std::runtime_error);
}
