#include "gtest/gtest.h"
#include "gameclasses/alienmanager.hpp"
#include <sstream>
#include <unordered_set>

TEST(alien2dmanager_test, test_construction)
{
  // Constructor
  Alien2DManager am1;
  EXPECT_EQ(am1.GetCountOfRows(), 5);
  EXPECT_EQ(am1.GetCountOfColumn(), 11);
  EXPECT_EQ(am1.GetLiveAliensCount(), 5*11);

  // Constructors with parameters.
  Alien2DManager am2 = {3, 7};
  EXPECT_EQ(am2.GetCountOfRows(), 3);
  EXPECT_EQ(am2.GetCountOfColumn(), 7);
  EXPECT_EQ(am2.GetLiveAliensCount(), 3*7);
}

TEST(alien2dmanager_test, test_assignment)
{
  Alien2DManager am1;
  am1 = {2, 3};

  AlienMatrix aMatrix = am1.GetAlienMatrix();
  size_t i = 0;
  for (auto itRow = aMatrix.begin(); itRow != aMatrix.end(); ++itRow)
  {
    AlienVector tempVect;
    tempVect = *itRow;
    size_t j = 0;
    for(auto itColumn = tempVect.begin(); itColumn != tempVect.end(); ++itColumn)
    {
      // output like this because << operator not released for Alien2D class
      EXPECT_EQ((*itColumn)->GetBox(),
        Box2D
        (
          Point2D
          {
            ALIEN_BOX_LEFT + j * (ALIEN_WIDTH + ALIEN_HORIZONTAL_DISTANCE),
            ALIEN_BOX_TOP + i * (ALIEN_HEIGHT + ALIEN_VERTICAL_DISTANCE)
          },
          Point2D
          {
            ALIEN_BOX_LEFT + j * (ALIEN_WIDTH + ALIEN_HORIZONTAL_DISTANCE) + ALIEN_WIDTH,
            ALIEN_BOX_TOP + i * (ALIEN_HEIGHT + ALIEN_VERTICAL_DISTANCE) + ALIEN_HEIGHT,
          }
        )
      );
      j++;
    }
    i++;
  }

  Alien2DManager am2;
  am2 = am1;
  EXPECT_EQ(am2.GetLiveAliensCount(), am1.GetLiveAliensCount());
}
