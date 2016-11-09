#include <iostream>
#include "gameclasses/space.hpp"

using namespace std;

int main(){
  try
  {
    GameEntityFactory Fac;
    auto G = Fac.Create(EntitiesTypes::GunType);
    G->G();






  }
  catch (...)
  {
    std:cerr << "Unknown error!";
  }
  return 0;
}

