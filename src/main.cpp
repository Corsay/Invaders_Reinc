#include <iostream>
#include "gameclasses/alien.hpp"

using namespace std;

int main()
{
  Alien2D al( Point2D{0.0f, 0.0f}, Point2D{5.0f, 3.0f}, First);
  cout << "hello" << endl;
  return 0;
}

