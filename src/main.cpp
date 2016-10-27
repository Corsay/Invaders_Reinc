#include <iostream>
#include "gameclasses/space.hpp"

using namespace std;

int main()
{
  try
  {
    Space2D sp;
    Alien2D al1;
    logger << al1 << endl;

    logger.Checkout("second_log.txt");

    Alien2D al2(Point2D{1.0f,1.0f}, Point2D{5.0f, 5.0f}, 50.0f, 2.0f);
    logger << al2 << std::endl;

    Alien2DManager alM(2, 3);
    logger << alM.GetAlienMatrix();

    Bullet2D bul;
    logger << bul << std::endl;

    logger.Checkout("log.txt");

    logger.Off();
    logger << "Some string" << std::endl;
    logger.On();
    logger << "the end" << std::endl;
  }
  catch (...)
  {
    std:cerr << "Unknown error!";
  }
  return 0;
}

