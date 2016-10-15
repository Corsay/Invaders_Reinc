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

  Gun2D gun;
  gun.Move();

  Alien2DManager am1 = {2, 3};
  AlienMatrix aMatrix = am1.GetAlienMatrix();
  for (auto it = aMatrix.begin(); it != aMatrix.end(); ++it)
  {
    std::vector<Alien2D> temp_vect;
    temp_vect = *it;
    for(auto it2 = temp_vect.begin(); it2 != temp_vect.end(); ++it2)
    {
      cout << *it2 << endl;
    }
    cout << endl;
  }

  cout << "hello" << endl;
  return 0;
}

