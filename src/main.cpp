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
    logger << "some alien health  = " <<  al.GetHealth() << endl;
    logger << "to be continued..." << endl;

    logger.Off();
    //это не будет никуда записано
    logger << "Here logger is Off" << sp << endl;
    logger.On();
    logger.Checkout();//запись в консоль

    Gun2D gun;
    logger << "This write in concole:  " << gun << endl;
    logger << WHERE << endl;

    logger.Checkout("second_log.txt");
    //информация о генерации матрицы и сама матрица запишутся во второй файл
    logger << "second log file" << endl;
    Alien2DManager am1 ;
    am1 = {2, 3};
    AlienMatrix aMatrix = am1.GetAlienMatrix();

    AlienVector temp_vect;
    for (auto it = aMatrix.begin(); it != aMatrix.end(); ++it)
    {
      temp_vect = *it;
      for(auto it2 = temp_vect.begin(); it2 != temp_vect.end(); ++it2)
      {
        logger << (*it2).GetBox() << endl;
      }
    }

    logger.Checkout("log.txt");
    //последующая информация ДОПШЕТСЯ в первый файл
    logger << "continued" << endl;

    Obstacle2D o1;
    logger << o1.GetBox();
    BoxMatrix bMatrix = o1.GetBoxMatrix();

    BoxVector tempVect;
    for (size_t i = 0; i < bMatrix.size(); ++i)
    {
      tempVect = bMatrix[i];
      for (size_t j = 0; j < tempVect.size(); ++j)
      {
        logger << tempVect[j].GetBox() << endl;
      }
    }
    for (auto it = bMatrix.begin(); it != bMatrix.end(); ++it)
    {
      tempVect = *it;
      for(auto it2 = tempVect.begin(); it2 != tempVect.end(); ++it2)
      {
        logger << (*it2).GetBox() << endl;
      }
    }
  }
  catch (...)
  {
    std:cerr << "Unknown error!";
  }
  return 0;
}

