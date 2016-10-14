#include <iostream>
#include "gameclasses/space.hpp"

using namespace std;

int main()
{
  Alien2D ali;
  Alien2D al( Point2D{0.0f, 0.0f}, Point2D{5.0f, 3.0f}, 50, 50);

  Space2D sp;

  sp.AlienShoot();
  cout << sp.CheckGameState() << endl;

  cout << "hello" << endl;
  return 0;
}

