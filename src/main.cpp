#include <iostream>

#include "box2d.hpp"

using namespace std;

int main()
{
  //cout << "Hello World!" << endl;

  // Тест на создание объекта по умолчанию.
  Point2D p1;
  cout << p1 << endl;
  //EXPECT_EQ(p1.x(), 0.0f);
  //EXPECT_EQ(p1.y(), 0.0f);

  // Тест на создание объекта с параметрами.
  Point2D p2 = { 1.2f, 3.8f };
  cout << p2 << endl;
  //EXPECT_EQ(p2.x(), 1.2f);
  //EXPECT_EQ(p2.y(), 2.4f);

  // Тест на создание копии объекта.
  Point2D p3 = p2;
  cout << p2 << endl;
  cout << p3 << endl << endl;
  //EXPECT_EQ(p3, p2);

  // square brackets point2d
  Point2D p4 = { 1.2f, 2.4f };
  cout << p4[0] << endl;
  cout << p4[1] << endl;
  cout << p4[2] << endl << endl;
  //EXPECT_EQ(p1[0], 1.2f);
  //EXPECT_EQ(p1[1], 2.4f);
  //EXPECT_EQ(p1[2], 0.0f);

  //hasher
  Point2D::Hash hasher;
  cout << hasher(Point2D(0.0f, 0.0f)) << endl;
  cout << hasher(p4) << endl << endl;
  //EXPECT_EQ(hasher(Point2D(0.0f, 0.0f)), 0);


  cout << endl;
  // Тест на создание объекта по умолчанию.
  Box2D b1;
  cout << b1 << endl;
  cout << b1.left_bottom() << endl;
  cout << b1.right_top() << endl;
  //EXPECT_EQ(p1.x(), 0.0f);
  //EXPECT_EQ(p1.y(), 0.0f);

  // Тест на создание объекта с параметрами.
  Box2D b2 = { p1, p2, p3 };
  cout << b2 << endl;
  //EXPECT_EQ(b2.left_bottom(), 1.2f);
  //EXPECT_EQ(b2.right_top(), 2.4f);

  // Тест на создание копии объекта.
  Box2D b3 = b2;
  cout << b2 << endl;
  cout << b3 << endl << endl;
  //EXPECT_EQ(b3, b2);

  // square brackets box2d
  Box2D b4 = { p2, p4 };
  cout << b4[0] << endl;
  cout << b4[0][0] << endl;
  cout << b4[0][1] << endl;
  cout << b4[0][2] << endl;
  cout << b4[1] << endl;
  cout << b4[2] << endl << endl;


  cout << endl;
  //             x1    y1      x2    y2
  Box2D b5 = { {1.2f, 2.4f}, {2.4f, 2.4f} };
  Box2D b6 = { {1.2f, 2.4f}, {2.4f, 2.4f} };
  Box2D b7 = { {1.3f, 2.4f}, {1.4f, 10.4f} };
  Box2D b8 = { {2.2f, 2.2f}, {7.2f, 6.5f} };
  //           [0][0] [0][1] [1][0] [1][1]

  float s1 = sqrt( pow(b5[1][0] - b5[0][0], 2) * pow (b5[1][1] - b5[0][1], 2) );
  float s2 = sqrt( pow(b6[1][0] - b6[0][0], 2) * pow (b6[1][1] - b6[0][1], 2) );

  float s3 = sqrt( pow(b7[1][0] - b7[0][0], 2) * pow (b7[1][1] - b7[0][1], 2) );
  float s4 = sqrt( pow(b8[1][0] - b8[0][0], 2) * pow (b8[1][1] - b8[0][1], 2) );

  cout << s1 << endl << s2 << endl;
  cout << s3 << endl << s4 << endl << endl;

  cout << endl;
  //
  Box2D b9 =  { {1.2f, 2.4f}, {1.2f, 2.6f} };
  Box2D b10 = { {1.0f, 2.0f}, {0.6f, 2.0f} };

  cout << b9 + b10 << endl;
  cout << b9 - b10 << endl;
  cout << b9 * 2.0f << endl;
  cout << b9 / 2.0f << endl;

  cout << endl;

  return 0;
}

