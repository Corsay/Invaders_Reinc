#include <iostream>
#include "gameclasses/space.hpp"

using namespace std;

int main()
{
  try
  {
    Alien2D ali;
    Alien2D al( Point2D{0.0f, 0.0f}, Point2D{5.0f, 3.0f}, 50, 50);

    Space2D sp;

    sp.AlienShoot();
    cout << sp.CheckGameState() << endl;

    Gun2D gun;
    //gun.Move();

    Alien2DManager am1 ;
    am1 = {2, 3};
    AlienMatrix aMatrix = am1.GetAlienMatrix();
    for (auto it = aMatrix.begin(); it != aMatrix.end(); ++it)
    {
      AlienVector temp_vect;
      temp_vect = *it;
      for(auto it2 = temp_vect.begin(); it2 != temp_vect.end(); ++it2)
      {
        cout << *it2 << endl;
      }
      cout << endl;
    }

    Obstacle2D o1;
    cout << o1.GetBorder() << endl << endl;
    BoxMatrix bMatrix = o1.GetBoxMatrix();
    for (size_t i = 0; i < bMatrix.size(); ++i)
    {
      BoxVector tempVect;
      tempVect = bMatrix[i];
      for (size_t j = 0; j < tempVect.size(); ++j)
      {
        cout << tempVect[j] << endl;
      }
      cout << endl;
    }
    for (auto it = bMatrix.begin(); it != bMatrix.end(); ++it)
    {
      BoxVector tempVect;
      tempVect = *it;
      for(auto it2 = tempVect.begin(); it2 != tempVect.end(); ++it2)
      {
        cout << *it2 << endl;
      }
      cout << endl;
    }

    cout << "hello" << endl;
  }
  catch (...)
  {
    std:cerr << "Unknown error!";
  }

  return 0;
}

