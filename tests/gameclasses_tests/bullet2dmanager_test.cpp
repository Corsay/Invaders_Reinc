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

}
