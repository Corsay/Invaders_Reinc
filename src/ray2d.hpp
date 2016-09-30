#pragma once

#include "box2d.hpp"

class Ray2D
{
public:
  // Allow default constructor.
  Ray2D() = default;

  // Constructor with parameters.
  Ray2D(Point2D origin, Direction direction)
    : m_origin(origin), m_direction(direction)
  {}

  // Constructor with initialization list.
  Ray2D(std::initializer_list<Point2D> const & lst)
  {
    float * vals[] = { &m_origin, &m_direction };
    int const count = sizeof(vals) / sizeof(vals[0]);
    auto it = lst.begin();
    for (int i = 0; i < count && it != lst.end(); i++, ++it)
      *vals[i] = *it;
  }

  // Copy constructor
  Ray2D(Ray2D const & obj)
    : m_origin(obj.m_origin), m_direction(obj.m_direction)
  {}

  // Getters
  Point2D & origin() { return m_origin; }
  Point2D & direction() { return m_direction; }
  Point2D const & origin() const { return m_origin; }
  Point2D const & direction() const { return m_direction; }

  // Assignment operator.
  Ray2D & operator = (Ray2D const & obj)
  {
    if (this == &obj) return *this;
    m_origin = obj.m_origin;
    m_direction = obj.m_direction;
    return *this;
  }

  // Logical operators
  bool operator == (Ray2D const & obj) const
  {
    return (m_origin == obj.m_origin && m_direction == obj.m_direction);
  }

  bool operator != (Ray2D const & obj) const
  {
    return !operator==(obj);
  }

  // Reverse direction of ray
  Ray2D operator - () const
  {
    return { m_origin, -m_direction };
  }

  // Redefinition
  Point2D operator [] (unsigned int index) const
  {
    if (index >= 2) return {0.0f, 0.0f};
    return index == 0 ? m_origin : m_direction;
  }

  friend std::ostream & operator << (std::ostream & os, Ray2D const & obj)
  {
    os << "Ray2D {" << obj.origin() << ", " << obj.direction() << "}";
    return os;
  }

  // add hash function
  struct Hash
  {
    size_t operator()(Ray2D const & p) const
    {
      Point2D::Hash hasher;
      return (hasher(p.m_origin) ^ (hasher(p.m_direction) << 1));
    }
  };

private:

  Point2D m_origin = {0.0f, 0.0f};
  Point2D m_direction = {0.0f, 1.0f};   // UP
};

