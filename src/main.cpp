#include <iostream>

#include "ray2d.hpp"

using namespace std;

int main()
{
  //cout << "Hello World!" << endl;

  int m = 3;

  switch (m)
  {
  // Point2D
    case 0:
    {
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
      Point2D::Hash point_hasher;
      cout << point_hasher(Point2D(0.0f, 0.0f)) << endl;
      cout << point_hasher(p4) << endl << endl;
      //EXPECT_EQ(hasher(Point2D(0.0f, 0.0f)), 0);

      break;
    }
  // Box2D
    case 1:
    {
      Point2D p1;
      Point2D p2 = { 1.2f, 3.8f };
      Point2D p3 = p2;
      Point2D p4 = { 1.2f, 2.4f };

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
      //
      Box2D b11 = { {1.2f, 2.4f}, {3.6f, 4.8f} };
      Box2D b12 = { {2.0f, 2.0f}, {7.0f, 6.0f} };

      cout << b11.Get_center() << endl;
      cout << b12.Get_center() << endl;

      cout << endl;
      //
      Box2D b13 = { {2.0f, 2.0f}, {7.0f, 6.0f} };
      Box2D b14 = { {7.0f, 2.0f}, {13.0f, 6.0f} };
      Box2D b15 = { {8.0f, 2.0f}, {13.0f, 6.0f} };
      Box2D b16 = { {-5.0f, 3.0f}, {7.0f, 2.0f} };
      Box2D b17 = { {3.0f, 3.0f}, {6.0f, 5.0f} };

      cout << (b13 && b14) << endl; // left
      cout << (b13 && b15) << endl; // not intersect
      cout << (b13 && b16) << endl; // bottom
      cout << (b13 && b17) << endl; // inside

      cout << endl;
      // hash
      Box2D::Hash box_hasher;
      Box2D b18;
      Box2D b19 = { {2.0f, 2.0f}, {7.0f, 6.0f} };
      cout << box_hasher(b18) << endl;
      cout << box_hasher(b19) << endl;

      break;
    }
  // Ray2D
    case 2:
    {
      Box2D b1 = { {2.0f, 2.0f}, {7.0f, 6.0f} };

      // from bottom
      Ray2D r1={ 4.0f, 0.0f, 135.0f};  // left
      Ray2D r2={ 2.0f, 0.0f, 90.0f};   // up
      Ray2D r3={ 5.0f, 0.0f, 45.0f};   // right
      // from left
      Ray2D r4={ 0.0f, 4.0f, 0.0f};    // right
      Ray2D r5={ 0.0f, 4.0f, 45.0f};   // up
      Ray2D r6={ 0.0f, 4.0f, -45.0f};  // down
      // from top
      Ray2D r7={ 4.0f, 8.0f, -135.0f}; // left
      Ray2D r8={ 4.5f, 8.0f, 270.0f};  // down
      Ray2D r9={ 5.0f, 8.0f, -45.0f};  // right
      // from right
      Ray2D r10={ 9.0f, 4.0f, 135.0f}; // up
      Ray2D r11={ 9.0f, 4.0f, 180.0f}; // left
      Ray2D r12={ 9.0f, 4.0f, 225.0f}; // down
      // near box
      Ray2D r13={ 2.0f-kEps*2, 2.0f-kEps*2, 90.0f};  // bottom UP    90
      Ray2D r14={ 2.0f-kEps*2, 2.0f-kEps*2, 0.0f};   // bottom Right 0
      Ray2D r15={ 7.0f+kEps*2, 2.0f-kEps*2, 180.0f}; // bottom LEFT  180
      Ray2D r16={ 7.0f+kEps*2, 2.0f-kEps*2, 90.0f};  // bottom UP    90
      Ray2D r17={ 7.0f+kEps*2, 6.0f+kEps*2, -90.0f}; // bottom Down  270
      Ray2D r18={ 7.0f+kEps*2, 6.0f+kEps*2, 180.0f}; // bottom Left  180
      Ray2D r19={ 2.0f-kEps*2, 6.0f+kEps*2, 0.0f};   // bottom Right 0
      Ray2D r20={ 2.0f-kEps*2, 6.0f+kEps*2, -90.0f}; // bottom Down  270

      // check
      cout << (r1 && b1) << endl;
      cout << (r2 && b1) << endl;
      cout << (r3 && b1) << endl;
      cout << (r4 && b1) << endl;
      cout << (r5 && b1) << endl;
      cout << (r6 && b1) << endl;
      cout << (r7 && b1) << endl;
      cout << (r8 && b1) << endl;
      cout << (r9 && b1) << endl;
      cout << (r10 && b1) << endl;
      cout << (r11 && b1) << endl;
      cout << (r12 && b1) << endl;
      cout << (r13 && b1) << endl;
      cout << (r14 && b1) << endl;
      cout << (r15 && b1) << endl;
      cout << (r16 && b1) << endl;
      cout << (r17 && b1) << endl;
      cout << (r18 && b1) << endl;
      cout << (r19 && b1) << endl;
      cout << (r20 && b1) << endl;

      cout << endl;

      //            x       y        angle
      Ray2D r21={ 2.0f, 2.0f-kEps*2, -90.0f}; // bottom Down  270
      Ray2D r22={ 2.0f-kEps*2, 6.0f, 180.0f}; // Left   Left  180
      Ray2D r23={ 7.0f, 6.0f+kEps*2, 90.0f};  // Top    Up    90
      Ray2D r24={ 7.0f+kEps*2, 2.0f, 0.0f};   // Right  Right 0

      cout << (r21 && b1) << endl;
      cout << (r22 && b1) << endl;
      cout << (r23 && b1) << endl;
      cout << (r24 && b1) << endl;

      break;
    }
  // move
    case 3:
    {
    // point
      Point2D p2 = { 1.2f, 2.4f };
      Point2D p3 = p2;
      Point2D p4;
      p4 = p2;
      // move constructor
      cout << "move constructor" << endl;
      cout << p2 << endl;
      Point2D p5 = std::move(p2);
      cout << p2 << endl;
      cout << p5 << endl << endl;
      // move
      cout << "move" << endl;
      cout << p2 << endl;
      cout << p3 << endl;
      p2 = std::move(p3);
      cout << p2 << endl;
      cout << p3 << endl << endl;
      // assignment
      cout << "assignment" << endl;
      cout << p2 << endl;
      cout << p3 << endl;
      p3 = p2;
      cout << p2 << endl;
      cout << p3 << endl << endl << endl;

    // box
      Box2D b1 = { {1.2f, 2.4f}, {3.6f, 4.8f} };
      Box2D b2 = b1;
      Box2D b3 = { -5.6f, 7.8f }; // точка по факту левая верхняя и {0;0} будет правой нижней // fixed
      Box2D b4;
      b4 = b3;
      cout << "boxes" << endl;
      cout << b1 << endl;
      cout << b2 << endl;
      cout << b3 << endl;
      cout << b4 << endl << endl;
      // move constructor
      cout << "move constructor" << endl;
      cout << b2 << endl;
      Box2D b5 = std::move(b2);
      cout << b2 << endl;
      cout << b5 << endl << endl;
      // move
      cout << "move" << endl;
      cout << b2 << endl;
      cout << b3 << endl;
      b2 = std::move(b3);
      cout << b2 << endl;
      cout << b3 << endl << endl;
      // assignment
      cout << "assignment" << endl;
      cout << b2 << endl;
      cout << b3 << endl;
      b3 = b2;
      cout << b2 << endl;
      cout << b3 << endl << endl << endl;

      // add tests mistakes in box
      Box2D b6 = { 0.0f, 0.0f, -5.6f, 7.8f };
      Box2D b7 = { 0.0f, 0.0f, 5.6f, -7.8f };
      Box2D b8 = { 0.0f, 0.0f, 5.6f, 7.8f };
      Box2D b9 = { 0.0f, 0.0f, -5.6f, -7.8f };
      Box2D b10 = { -5.5f, 7.7f, -5.6f, 7.8f };
      cout << b6 << endl;
      cout << b7 << endl;
      cout << b8 << endl;
      cout << b9 << endl;
      cout << b10 << endl;
      cout << "additional test for boxes" << endl;
      cout << "bottom - " << b6.bottom() << "    left   - " << b6.left() << endl;
      cout << "top    - " << b6.top() << "  right  - " << b6.right()  << endl;
      cout << "bottom - " << b7.bottom() << " left   - " << b7.left() << endl;
      cout << "top    - " << b7.top() << "    right  - " << b7.right()  << endl;
      cout << "bottom - " << b8.bottom() << "    left   - " << b8.left() << endl;
      cout << "top    - " << b8.top() << "  right  - " << b8.right()  << endl;
      cout << "bottom - " << b9.bottom() << " left   - " << b9.left() << endl;
      cout << "top    - " << b9.top() << "    right  - " << b9.right()  << endl;
      cout << "bottom - " << b10.bottom() << "  left   - " << b10.left() << endl;
      cout << "top    - " << b10.top() << "  right  - " << b10.right()  << endl;
      cout << endl;

    // ray
      Ray2D r1 = { {1.2f, 2.4f}, 180.0f };
      Ray2D r2 = r1;
      Ray2D r3 = { -5.6f, 7.8f, 45.0f };
      Ray2D r4;
      r4 = r3;
      cout << "rays" << endl;
      cout << r1 << endl;
      cout << r2 << endl;
      cout << r3 << endl;
      cout << r4 << endl << endl;
      // move constructor
      cout << "move constructor" << endl;
      cout << r2 << endl;
      Ray2D r5 = std::move(r2);
      cout << r2 << endl;
      cout << r5 << endl << endl;
      // move
      cout << "move" << endl;
      cout << r2 << endl;
      cout << r3 << endl;
      r2 = std::move(r3);
      cout << r2 << endl;
      cout << r3 << endl << endl;
      // assignment
      cout << "assignment" << endl;
      cout << r2 << endl;
      cout << r3 << endl;
      r3 = r2;
      cout << r2 << endl;
      cout << r3 << endl << endl << endl;

      break;
    }
    default:
    {
      cout << "default" << endl;

      break;
    }
  }

  return 0;
}

