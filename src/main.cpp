#include <iostream>
#include "gameclasses/space.hpp"

using namespace std;

int main(){
  try
  {
    GameEntityFactory fac;
    //fac.Register(Gun2D().Create());
    auto G = static_unique_ptr_cast<Gun2D>(fac.Create(EntitiesTypes::GunType));
    G->G();

    auto A = static_unique_ptr_cast<Alien2D>(fac.Create(EntitiesTypes::AlienType));
    A->A();
    auto AA = static_unique_ptr_cast<Alien2D>(fac.Create(EntitiesTypes::AlienType));
    AA->A();
    //A->G();
  }
  catch (...)
  {
    std:cerr << "Unknown error!";
  }
  return 0;
}

