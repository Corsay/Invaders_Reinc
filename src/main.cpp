#include <iostream>
#include "gameclasses/space.hpp"

using namespace std;

int main()
{
  try
  {
    GameEntityFactory fac;
    fac.Register(Gun2D().Create());
    auto g = static_unique_ptr_cast<Gun2D>(fac.Create(EntitiesTypes::GunType));
    std::cout << g->GetBox() << std::endl;


    fac.Register(Alien2D().Create());
    auto a = static_unique_ptr_cast<Alien2D>(fac.Create(EntitiesTypes::AlienType));
    auto aa = static_unique_ptr_cast<Alien2D>(fac.Create(EntitiesTypes::AlienType));
    std::cout << a->GetBox() << std::endl << std::endl;
    std::cout << aa->GetBox() << std::endl << std::endl;


    // для работы варианта с шаблонами, типы должны быть указаны явно
    Factory fact;
    auto gun = fact.CreateNew<Gun2D>(Point2D{5.2f, 8.4f}, Point2D{3.4f, 7.8f}, 55.0f, 90.0f, 5);
    std::cout << gun->GetBox() << std::endl;
    std::cout << gun->GetHealth() << std::endl;
    std::cout << gun->GetSpeed() << std::endl;
    std::cout << gun->GetLives() << std::endl;
    std::cout << gun->GetRate() << std::endl;
  }
  catch (...)
  {
    std:cerr << "Unknown error!";
  }
  return 0;
}

