#pragma once

#include "point2d.hpp"

class Box2D
{
public:
  // Разрешаем конструирование по умолчанию.
  Box2D() = default;

  // Конструктор копирования.
  Box2D(Box2D const & obj)
    : m_left_bottom(obj.m_left_bottom), m_right_top(obj.m_right_top)
  {}

  // Конструктор с параметрами.
  Box2D(Point2D left_bottom, Point2D right_top)
    : m_left_bottom(left_bottom), m_right_top(right_top)
  {}


  // Оператор логического равенства.
  bool operator == (Box2D const & obj) const
  {
    return (m_left_bottom == obj.left_bottom() && m_right_top == obj.right_top());
  }

  // get
  Point2D & left_bottom() { return m_left_bottom; }
  Point2D & right_top() { return m_right_top; }

  Point2D const & left_bottom() const { return m_left_bottom; }
  Point2D const & right_top() const { return m_right_top; }

  // get center
  Point2D get_center()
  {
    Point2D p = {(m_left_bottom.x() + m_right_top.x()) / 2 , (m_left_bottom.y() + m_right_top.y())/2 };
    return p;
  }

  // check of intersection boxes
  bool check_intersection (Box2D const & obj)
  {
    //        y2               oy1          y1                 oy2          x2               ox1          x1                 ox2
    return !( right_top()[1] < obj[0][1] || left_bottom()[1] > obj[1][1] || right_top()[0] < obj[0][0] || left_bottom()[0] > obj[1][0] );
  }

  // Конструктор со списком инициализации.
  Box2D(std::initializer_list<Point2D> const & lst)
  {
    Point2D * vals[] = { &m_left_bottom, &m_right_top };
    int const count = sizeof(vals) / sizeof(vals[0]);
    auto it = lst.begin();
    for (int i = 0; i < count && it != lst.end(); i++, ++it)
      *vals[i] = *it;
  }

  // Оператор присваивания.
  Box2D & operator = (Box2D const & obj)
  {
    if (this == &obj) return *this;
    m_left_bottom = obj.m_left_bottom;
    m_right_top = obj.m_right_top;
    return *this;
  }

  // Оператор логического неравенства.
  bool operator != (Box2D const & obj) const
  {
    return !operator==(obj);
  }

  // Оператор меньше.
  bool operator < (Box2D const & obj) const
  {      
    // square of first
    float s1 = sqrt( powf(right_top()[0] - left_bottom()[0], 2) * powf(right_top()[1] - left_bottom()[1], 2) );
    // square of second
    float s2 = sqrt( powf(obj[1][0] - obj[0][0], 2) * powf(obj[1][1] - obj[0][1], 2) );

    return s1 < s2;
  }

  // Сложение.
  Box2D operator + (Box2D const & obj) const
  {
      return
      {
          m_left_bottom + obj.m_left_bottom,
          m_right_top + obj.m_right_top
      };
  }

  // Вычитание.
  Box2D operator - (Box2D const & obj) const
  {
    return
    {
        m_left_bottom - obj.m_left_bottom,
        m_right_top - obj.m_right_top
    };
  }

  // Математическое отрицание.
  Box2D operator - () const
  {
    return
    {
        -m_left_bottom,
        -m_right_top
    };
  }

  // Умножение на число.
  Box2D operator * (float scale) const
  {
    return
    {
        m_left_bottom * scale,
        m_right_top * scale
    };
  }

  // Деление на число.
  Box2D operator / (float scale) const
  {
    //TODO: обработать деление на 0.
    return
    {
        m_left_bottom / scale,
        m_right_top / scale
    };
  }

  Box2D & operator += (Box2D const & obj)
  {
    m_left_bottom += obj.left_bottom();
    m_right_top += obj.right_top();
    return *this;
  }

  Box2D & operator -= (Box2D const & obj)
  {
    m_left_bottom -= obj.left_bottom();
    m_right_top -= obj.right_top();
    return *this;
  }

  Box2D & operator *= (float scale)
  {
    m_left_bottom *= scale;
    m_right_top *= scale;
    return *this;
  }

  Box2D & operator /= (float scale)
  {
    //TODO: обработать деление на 0.
    m_left_bottom /= scale;
    m_right_top /= scale;
    return *this;
  }

  // Переопределение оператора [].
  Point2D operator [] (unsigned int index) const
  {
    if (index >= 2) return {0.0f,0.0f};
    return index == 0 ? m_left_bottom : m_right_top;
  }

  // Добавим внутреннюю сущность для вычисления хэша.
  struct Hash
  {
    size_t operator()(Box2D const & p) const
    {
      Point2D::Hash hasher;
      return (hasher(p.left_bottom()) ^ (hasher(p.right_top()) << 1));
    }
  };

  // Переопределение оператора <<
  friend std::ostream & operator << (std::ostream & os, Box2D const & obj)
  {
    os << "Box2D {" << obj.left_bottom() << ", " << obj.right_top() << "}";
    return os;
  }

private:

  Point2D m_left_bottom = {0.0f,0.0f}, m_right_top = {0.0f,0.0f};
};
