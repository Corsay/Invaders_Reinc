#pragma once

#include "point2d.hpp"

float const kEps = 1e-5;

class Ray2D
{
public:
  // Разрешаем конструирование по умолчанию.
  Ray2D() = default;

  // Конструктор копирования.
  Ray2D(Ray2D const & obj)
    : m_x(obj.m_x), m_y(obj.m_y)
  {}

  // Конструктор с параметрами.
  Ray2D(float x, float y)
    : m_x(x), m_y(y)
  {}

  // Оператор логического равенства.
  bool operator == (Ray2D const & obj) const
  {
    return EqualWithEps(m_x, obj.m_x) && EqualWithEps(m_y, obj.m_y);
  }

  float & x() { return m_x; }
  float & y() { return m_y; }

  float const & x() const { return m_x; }
  float const & y() const { return m_y; }

  // Конструктор со списком инициализации.
  Ray2D(std::initializer_list<float> const & lst)
  {
    float * vals[] = { &m_x, &m_y };
    int const count = sizeof(vals) / sizeof(vals[0]);
    auto it = lst.begin();
    for (int i = 0; i < count && it != lst.end(); i++, ++it)
      *vals[i] = *it;
  }

  // Оператор присваивания.
  Ray2D & operator = (Ray2D const & obj)
  {
    if (this == &obj) return *this;
    m_x = obj.m_x;
    m_y = obj.m_y;
    return *this;
  }

  // Оператор логического неравенства.
  bool operator != (Ray2D const & obj) const
  {
    return !operator==(obj);
  }

  // Оператор меньше.
  bool operator < (Ray2D const & obj) const
  {
    if (m_x != obj.m_x) return m_x < obj.m_x;
    return m_y < obj.m_y;
  }

  // Сложение.
  Ray2D operator + (Ray2D const & obj) const
  {
    return { m_x + obj.m_x, m_y + obj.m_y };
  }

  // Вычитание.
  Ray2D operator - (Ray2D const & obj) const
  {
    return { m_x - obj.m_x, m_y - obj.m_y };
  }

  // Математическое отрицание.
  Ray2D operator - () const
  {
    return { -m_x, -m_y };
  }

  // Умножение на число.
  Ray2D operator * (float scale) const
  {
    return { m_x * scale, m_y * scale };
  }

  // Деление на число.
  Ray2D operator / (float scale) const
  {
    //TODO: обработать деление на 0.
    return { m_x / scale, m_y / scale };
  }

  Ray2D & operator += (Ray2D const & obj)
  {
    m_x += obj.m_x;
    m_y += obj.m_y;
    return *this;
  }

  Ray2D & operator -= (Ray2D const & obj)
  {
    m_x -= obj.m_x;
    m_y -= obj.m_y;
    return *this;
  }

  Ray2D & operator *= (float scale)
  {
    m_x *= scale;
    m_y *= scale;
    return *this;
  }

  Ray2D & operator /= (float scale)
  {
    //TODO: обработать деление на 0.
    m_x /= scale;
    m_y /= scale;
    return *this;
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
    size_t operator()(Ray2D const & p) const
    {
      auto hasher = std::hash<float>();
      return (hasher(p.x()) ^ (hasher(p.y()) << 1));
    }
  };

private:

  bool EqualWithEps(float v1, float v2) const
  {
    return fabs(v1 - v2) < kEps;
  }

  float m_x = 0.0f, m_y = 0.0f;
};

std::ostream & operator << (std::ostream & os, Ray2D const & obj)
{
  os << "Ray2D {" << obj.x() << ", " << obj.y() << "}";
  return os;
}
