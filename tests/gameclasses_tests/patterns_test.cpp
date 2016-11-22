#include "gtest/gtest.h"
#include "gameclasses/space.hpp"
#include <sstream>
#include <unordered_set>

TEST(patterns_test, test_template_factory)
{
  Factory fact;
  auto gun = fact.CreateNew<Gun2D>(Point2D{5.2f, 8.4f}, Point2D{3.4f, 7.8f}, 55.0f, 90.0f, 5);
  EXPECT_EQ(gun->GetBox(), Box2D(Point2D(5.2f, 8.4f), Point2D(3.4f, 7.8f)));
  EXPECT_EQ(gun->GetHealth(), 55);
  EXPECT_EQ(gun->GetSpeed(), 90);
  EXPECT_EQ(gun->GetLives(), 5);
}

TEST(patterns_test, test_abstract_factory)
{
  GameEntityFactory fac;
  fac.Register(Gun2D().Create());
  fac.Register(Alien2D().Create());

  auto g = static_unique_ptr_cast<Gun2D>(fac.Create(EntitiesTypes::GunType));
  EXPECT_EQ(g->GetBox(), Box2D(GUN_START_X, GUN_START_Y, GUN_START_X + GUN_WIDTH, GUN_START_Y + GUN_HEIGHT));

  auto a = static_unique_ptr_cast<Alien2D>(fac.Create(EntitiesTypes::AlienType));
  auto aa = static_unique_ptr_cast<Alien2D>(fac.Create(EntitiesTypes::AlienType));
  EXPECT_EQ(a->GetBox(), Box2D(Point2D(0.0f, 0.0f), Point2D(0.0f, 0.0f)));
  EXPECT_EQ(aa->GetBox(), Box2D(Point2D(0.0f, 0.0f), Point2D(0.0f, 0.0f)));
}

TEST(patterns_test, test_observer)
{
  Gun2D gun = { {5.2f, 8.4f}, {3.4f, 7.8f}, 55, 90, 5 };
  Bullet2D bul = { {5.0f, 8.0f}, {5.0f, 8.0f} };
  bul.SetUpdateHandler( [&](GameEntity2D const & ge){ std::cout << "the bullet from the alien hit in " << ge << std::endl; }  );

  EXPECT_TRUE(gun.CheckIntersection(bul));
  // the bullet from the alien hit in GameEntity2D {Box2D {Point2D {3.4, 7.8}, Point2D {5.2, 8.4}}}
}
