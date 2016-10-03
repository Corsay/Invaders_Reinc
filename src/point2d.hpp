#pragma once

#include <cmath>
#include <initializer_list>
#include <functional>
#include <ostream>

float const kEps = 1e-5;

class Point2D
{
public:
  // Разрешаем конструирование по умолчанию.
  Point2D() = default;

  // Конструктор копирования.
  Point2D(Point2D const & obj)
    : m_x(obj.m_x), m_y(obj.m_y)
  {}

  // Конструктор с параметрами.
  Point2D(float const x, float const y)
    : m_x(x), m_y(y)
  {}

  // Конструктор перемещения
  Point2D(Point2D && obj)
  {
    std::swap(m_x, obj.x());
    std::swap(m_y, obj.y());
  }

  // Getters
  inline float & x() { return m_x; }
  inline float & y() { return m_y; }
  inline float const & x() const { return m_x; }
  inline float const & y() const { return m_y; }

  // Конструктор со списком инициализации.
  Point2D(std::initializer_list<float> const & lst)
  {
    float * vals[] = { &m_x, &m_y };
    int const count = sizeof(vals) / sizeof(vals[0]);
    auto it = lst.begin();
    for (int i = 0; i < count && it != lst.end(); i++, ++it)
      *vals[i] = *it;
  }

  // Оператор присваивания.
  Point2D & operator = (Point2D const & obj)
  {
    if (this == &obj) return *this;
    m_x = obj.m_x;
    m_y = obj.m_y;
    return *this;
  }

  // Оператор перемещения
  Point2D & operator = (Point2D && obj)
  {
    if (this == &obj) return *this;
    std::swap(m_x, obj.x());
    std::swap(m_y, obj.y());
    return *this;
  }

  // Logical operators
  // Оператор логического равенства.
  bool operator == (Point2D const & obj) const
  {
    return EqualWithEps(m_x, obj.m_x) && EqualWithEps(m_y, obj.m_y);
  }

  // Оператор логического неравенства.
  bool operator != (Point2D const & obj) const
  {
    return !operator==(obj);
  }

  // Оператор меньше.
  bool operator < (Point2D const & obj) const
  {
    if (m_x != obj.m_x) return m_x < obj.m_x;
    return m_y < obj.m_y;
  }

  bool operator > (Point2D const & obj) const
  {
    if (m_x != obj.m_x) return m_x > obj.m_x;
    return m_y > obj.m_y;
  }

  bool operator <= (Point2D const & obj) const
    {
      return m_x <= obj.m_x+kEps && m_y <= obj.m_y+kEps;
    }

  bool operator >= (Point2D const & obj) const
  {
    return m_x >= obj.m_x-kEps && m_y >= obj.m_y-kEps;
  }

  // Сложение.
  Point2D operator + (Point2D const & obj) const
  {
    return { m_x + obj.m_x, m_y + obj.m_y };
  }

  // Вычитание.
  Point2D operator - (Point2D const & obj) const
  {
    return { m_x - obj.m_x, m_y - obj.m_y };
  }

  // Математическое отрицание.
  Point2D operator - ()
  {
    return { -m_x, -m_y };
  }

  // Умножение на число.
  Point2D operator * (float scale)
  {
    return { m_x * scale, m_y * scale };
  }

  // Деление на число.
  Point2D operator / (float scale)
  {
    //TODO: обработать деление на 0.
    return { m_x / scale, m_y / scale };
  }

  Point2D & operator += (Point2D const & obj)
  {
    m_x += obj.m_x;
    m_y += obj.m_y;
    return *this;
  }

  Point2D & operator -= (Point2D const & obj)
  {
    m_x -= obj.m_x;
    m_y -= obj.m_y;
    return *this;
  }

  Point2D & operator *= (float scale)
  {
    m_x *= scale;
    m_y *= scale;
    return *this;
  }

  Point2D & operator /= (float scale)
  {
    //TODO: обработать деление на 0.
    m_x /= scale;
    m_y /= scale;
    return *this;
  }

  void HorizontalShift(float shift)
  {
    m_x += shift;
  }
  void VerticalShift(float shift)
  {
    m_y += shift;
  }

  // Переопределение оператора [].
  float operator [] (unsigned int index) const
  {
    if (index >= 2) return 0.0f;
    return index == 0 ? m_x : m_y;
  }

  // Добавим внутреннюю сущность для вычисления хэша.
  struct Hash
  {
    size_t operator()(Point2D const & p) const
    {
      auto hasher = std::hash<float>();
      return (hasher(p.x()) ^ (hasher(p.y()) << 1));
    }
  };

  // Переопределение оператора <<
  friend std::ostream & operator << (std::ostream & os, Point2D const & obj)
  {
    os << "Point2D {" << obj.x() << ", " << obj.y() << "}";
    return os;
  }

private:

  bool EqualWithEps(float v1, float v2) const
  {
    return fabs(v1 - v2) < kEps;
  }

  float m_x = 0.0f, m_y = 0.0f;
};
