#include "gtest/gtest.h"
#include "gameclasses/space.hpp"
#include "gameclasses/logger.hpp"
#include <iostream>
#include <fstream>

TEST(logger_test, test_logger_work)
{
  //очищаем файлы от предыдущих тестов
  logger.Checkout();
  logger.Off();
  std::ofstream fout;
  fout.open("log.txt");
  fout.close();
  fout.open("second_log.txt");
  fout.close();
  logger.On();
  logger.Checkout("log.txt");

  Space2D sp;
  Alien2D al1;
  logger << al1 << std::endl;

  logger.Checkout("second_log.txt");

  Alien2D al2 = Alien2D(Point2D{1.0f,1.0f}, Point2D{5.0f, 5.0f}, 50.0f, 2.0f);
  logger << al2;

  Alien2DManager alM(2, 3);
  logger << alM.GetAlienMatrix();

  Bullet2D bul;
  logger << bul << std::endl;

  logger.Checkout("log.txt");

  logger.Off();
  logger << "Some string" << std::endl;
  logger.On();
  logger << "the end!!!" << std::endl;

  std::ifstream fin1("log.txt");
  std::ifstream fin2("second_log.txt");

  std::string file1(""), file2("");
  char c;
  if(fin1.is_open())
  {
    while((c = fin1.get()) != EOF)
    {
      file1 += c;
    }
  }
  if(fin2.is_open())
  {
    while((c = fin2.get()) != EOF)
    {
      file2 += c;
    }
  }
  EXPECT_EQ(file1.size(), 232);
  EXPECT_EQ(file2.size(), 261);
}
