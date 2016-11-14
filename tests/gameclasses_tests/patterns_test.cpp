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
  EXPECT_EQ(g->GetBox(), Box2D(Point2D(0.0f, 0.0f), Point2D(0.0f, 0.0f)));

  auto a = static_unique_ptr_cast<Alien2D>(fac.Create(EntitiesTypes::AlienType));
  auto aa = static_unique_ptr_cast<Alien2D>(fac.Create(EntitiesTypes::AlienType));
  EXPECT_EQ(a->GetBox(), Box2D(Point2D(0.0f, 0.0f), Point2D(0.0f, 0.0f)));
  EXPECT_EQ(aa->GetBox(), Box2D(Point2D(0.0f, 0.0f), Point2D(0.0f, 0.0f)));
}
