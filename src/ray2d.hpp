#pragma once

#include "box2d.hpp"


float constexpr RAD=M_PI/180.0f;

class Ray2D
{
public:
  // Allow default constructor.
  Ray2D() = default;

  // Constructor with parameters.
  Ray2D(Point2D const origin, float const direction)
    :m_origin(origin),
     m_direction(direction)
  {
    CorrectDirectionAngle();
  }
  Ray2D(float const originX, float const originY, float const direction)
    :m_origin(originX, originY),
     m_direction(direction)
  {
    CorrectDirectionAngle();
  }

  // Constructor with initialization list.
  Ray2D(std::initializer_list<float> const & lst)
  {
    auto it = lst.begin();
    m_origin.x() = *it;
    it++;
    if(it != lst.end())
    {
        m_origin.y() = *it;
        it++;
    }
    if(it != lst.end())
    {
      m_direction = *it;
      CorrectDirectionAngle();
    }
  }

  // Copy constructor
  Ray2D(Ray2D const & obj)
    : m_origin(obj.m_origin), m_direction(obj.m_direction)
  {}

  // Move constructor
  Ray2D(Ray2D && obj)
  {
    std::swap(m_origin, obj.origin());
    std::swap(m_direction, obj.direction());
  }

  // Getters
  inline Point2D & origin() { return m_origin; }
  inline float const x() const { return m_origin.x(); }
  inline float const y() const { return m_origin.y(); }
  inline float & direction() { return m_direction; }
  inline Point2D const & origin() const { return m_origin; }
  inline float const & direction() const { return m_direction; }

  // Setters
  void setDirection(float direction)
  {
    m_direction = direction;
    CorrectDirectionAngle();
  }
  void setOrigin(Point2D const & origin){ m_origin = origin; }

  // Assignment operator.
  Ray2D & operator = (Ray2D const & obj)
  {
    if (this == &obj) return *this;
    m_origin = obj.m_origin;
    m_direction = obj.m_direction;
    return *this;
  }

  // Move operator
  Ray2D & operator = (Ray2D && obj)
  {
    if (this == &obj) return *this;
    std::swap(m_origin, obj.origin());
    std::swap(m_direction, obj.direction());
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

  // reverse ray direction
  Ray2D operator - ()
  {
    m_direction -= 180.0f;
    CorrectDirectionAngle();
    return { m_origin, m_direction };
  }

  // Capabilities
  bool operator &&(Box2D const & box) const
  {
    if(box && m_origin)
        return true;

    float k = tan(m_direction * RAD);
    float b = m_origin.y() - k * m_origin.x();
    float coord = 0.0f;
    //right
    coord = k * box.right() + b;
    if(coord <= box.top() + kEps && coord >= box.bottom() - kEps && CheckPoint(box.right(), coord))
      return true;
    //left
    coord = k * box.left() + b;
    if(coord <= box.top() + kEps && coord >= box.bottom() - kEps && CheckPoint(box.left(), coord))
      return true;

    //top
    coord = float((box.top() - b)) / k;
    if(fabs(coord) < kEps)
        coord = 0;
    if(coord <=(box.right() + kEps) && coord >=(box.left() - kEps) && CheckPoint(coord, box.top()))
      return true;

    return false;
  }

  bool operator &&(Point2D const & point) const
  {
    float k = tan(m_direction * RAD);
    float b = m_origin.y() - k * m_origin.x();

    float coord = k * point.x() + b;

    if(fabs(coord - point.y()) < kEps && CheckPoint(point.x(), coord))
      return true;
    return false;
  }

  void VerticalShift(float shift) { m_origin.VerticalShift(shift); }
  void HorizontalShift(float shift) { m_origin.HorizontalShift(shift); }
  void DirectionShiftAngle(float shift_angle)
  {
    m_direction += shift_angle;
    CorrectDirectionAngle();
  }

  // Redefinition
  float operator [] (unsigned int index) const
  {
    if (index >= 3) return 0.0f;
    return index == 0 ? m_origin.x() : index == 1 ? m_origin.y() : m_direction;
  }

  friend std::ostream & operator << (std::ostream & os, Ray2D const & obj)
  {
    os << "Ray2D {" << obj.origin() << ", " << obj.direction() << "}";
    return os;
  }

private:

  void CorrectDirectionAngle()
  {
    m_direction = m_direction - int(m_direction / 360.0f) * 360.0f; // direction%360
    if (m_direction < 0.0f)
      m_direction += 360.0f;
  }

  bool CheckPoint(float const x, float const y) const
  {
    if(m_direction <= 180.0f && y < m_origin.y()-kEps)
      return false;
    if(m_direction > 180 && y >= m_origin.y()+kEps)
      return false;
    if((m_direction <= 90 || m_direction>=270) && x < m_origin.x()-kEps)
      return false;
    if(m_direction > 90 && m_direction < 270 && x >= m_origin.x()+kEps)
      return false;
    return true;
  }

  Point2D m_origin = {0.0f, 0.0f};
  float m_direction = 90.0f;
};
