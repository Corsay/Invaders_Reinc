#include "gtest/gtest.h"
#include "gameclasses/space.hpp"
#include <sstream>
#include <unordered_set>

TEST(space2d_test, test_construction)
{
  // constructor
  try
  {
    //Space2D s1;
    //s1.CheckGameState();
  }
  catch (std::exception & e)
  {
    std::cout << e.what();
  }


  // Constructors with parameters.
  //Space2D s2 = { {1.2f, 2.4f}, {2.4f, 4.8f} };

  //Space2D s3 = { {5.2f, 8.4f}, {3.4f, 7.8f}};
  //EXPECT_EQ(s3.GetBorder(), Box2D( Point2D(), Point2D()));


}
