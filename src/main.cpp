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

    AlienVector temp_vect;
    for (auto it = aMatrix.begin(); it != aMatrix.end(); ++it)
    {
      temp_vect = *it;
      for(auto it2 = temp_vect.begin(); it2 != temp_vect.end(); ++it2)
      {
        cout << (*it2).GetBorder() << endl;
      }
      cout << endl;
    }

    Obstacle2D o1;
    cout << o1.GetBorder() << endl << endl;
    BoxMatrix bMatrix = o1.GetBoxMatrix();

    BoxVector tempVect;
    for (size_t i = 0; i < bMatrix.size(); ++i)
    {
      tempVect = bMatrix[i];
      for (size_t j = 0; j < tempVect.size(); ++j)
      {
        cout << tempVect[j].GetBorder() << endl;
      }
      cout << endl;
    }
    for (auto it = bMatrix.begin(); it != bMatrix.end(); ++it)
    {
      tempVect = *it;
      for(auto it2 = tempVect.begin(); it2 != tempVect.end(); ++it2)
      {
        cout << (*it2).GetBorder() << endl;
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

