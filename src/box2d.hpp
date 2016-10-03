#pragma once

#include "point2d.hpp"

class Box2D
{
public:
  // Allow default constructor.
  Box2D() = default;

  // Constructors with parameters.
  Box2D(Point2D left_bottom, Point2D right_top)
    : m_left_bottom(left_bottom), m_right_top(right_top)
  {
    Swap();
  }

  Box2D(float x1, float y1, float x2, float y2)
    : m_left_bottom(x1, y1), m_right_top(x2, y2)
  {
    Swap();
  }

  // Constructor with initialization list.
  Box2D(std::initializer_list<Point2D> const & lst)
  {
    Point2D * vals[] = { &m_left_bottom, &m_right_top };
    int const count = sizeof(vals) / sizeof(vals[0]);
    auto it = lst.begin();
    for (int i = 0; i < count && it != lst.end(); i++, ++it)
      *vals[i] = *it;
    Swap();
  }

  Box2D(std::initializer_list<float> const& lst)
  {
    float *vals[] = { &m_left_bottom.x(), &m_left_bottom.y(), &m_right_top.x(), &m_right_top.y() };
    auto it = lst.begin();
    // writing coord's
    for (int i=0; i<4 && it!=lst.end(); i++, ++it)
        *vals[i] = *it;
    Swap();
  }

  // Copy constructor
  Box2D(Box2D const & obj)
    : m_left_bottom(obj.m_left_bottom), m_right_top(obj.m_right_top)
  {}

  // Move constructor
  Box2D(Box2D && obj)
  {
    std::swap(m_left_bottom, obj.left_bottom());
    std::swap(m_right_top, obj.right_top());
  }

  // Getters
  inline Point2D & left_bottom() { return m_left_bottom; }
  inline Point2D & right_top() { return m_right_top; }
  inline Point2D const & left_bottom() const { return m_left_bottom; }
  inline Point2D const & right_top() const   { return m_right_top; }
  inline float const left() const   { return left_bottom().x(); } // x min
  inline float const right() const  { return right_top().x(); }   // x max
  inline float const top() const    { return right_top().y(); }   // y max
  inline float const bottom() const { return left_bottom().y(); } // y min

  // Logical operators
  bool operator == (Box2D const & obj) const
  {
    return (m_left_bottom == obj.left_bottom() && m_right_top == obj.right_top());
  }

  bool operator != (Box2D const & obj) const
  {
    return !operator==(obj);
  }

  bool operator < (Box2D const & obj) const
  {      
    return Rectangle_square() < obj.Rectangle_square();
  }

  // Assignment operator.
  Box2D & operator = (Box2D const & obj)
  {
    if (this == &obj) return *this;
    m_left_bottom = obj.m_left_bottom;
    m_right_top = obj.m_right_top;
    return *this;
  }

  // Move operator
  Box2D & operator = (Box2D && obj)
  {
    if (this == &obj) return *this;
    std::swap(m_left_bottom, obj.left_bottom());
    std::swap(m_right_top, obj.right_top());
    return *this;
  }

  // Math operations
  Box2D operator + (Box2D const & obj) const
  {
      return
      {
          m_left_bottom + obj.m_left_bottom,
          m_right_top + obj.m_right_top
      };
  }

  Box2D operator - (Box2D const & obj) const
  {
    return
    {
        m_left_bottom - obj.m_left_bottom,
        m_right_top - obj.m_right_top
    };
  }

  Box2D operator - ()
  {
    return
    {
        -m_left_bottom,
        -m_right_top
    };
  }

  Box2D operator * (float scale)
  {
    return
    {
        m_left_bottom * scale,
        m_right_top * scale
    };
  }

  Box2D operator / (float scale)
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

  // Capabilities
  Point2D Get_center() const
  {
    Point2D p = {(m_left_bottom.x() + m_right_top.x()) / 2 , (m_left_bottom.y() + m_right_top.y())/2 };
    return p;
  }

  // Check_intersection
  bool operator &&(Box2D const & obj) const
  {
    return !( top() < obj.bottom() || bottom() > obj.top() || right() < obj.left() || left() > obj.right() );
  }
  bool operator &&(Point2D const & P) const
  {
    return !( P.y() < bottom() || P.y() > top() || right() < P.x() || left() > P.x() );
  }

  void HorizontalShift(float shift)
  {
    m_left_bottom.x() += shift;
    m_right_top.x() += shift;
  }
  void VerticalShift(float shift)
  {
    m_left_bottom.y() += shift;
    m_right_top.y() += shift;
  }

  // Redefinition
  Point2D operator [] (unsigned int index) const
  {
    if (index >= 2) return {0.0f,0.0f};
    return index == 0 ? m_left_bottom : m_right_top;
  }

  friend std::ostream & operator << (std::ostream & os, Box2D const & obj)
  {
    os << "Box2D {" << obj.left_bottom() << ", " << obj.right_top() << "}";
    return os;
  }

  // add hash function
  struct Hash
  {
    size_t operator()(Box2D const & p) const
    {
      Point2D::Hash hasher;
      return (hasher(p.left_bottom()) ^ (hasher(p.right_top()) << 1));
    }
  };

private:

  void Swap()
  {  
    if (m_left_bottom > m_right_top) std::swap(m_left_bottom, m_right_top);

    if (left() > right() || bottom() > top())
    {
       std::swap(m_left_bottom.y(), m_right_top.y());
    }
  }

  double Rectangle_square () const
  {
      double rez = sqrt( powf(right() - left(), 2) * powf(top() - bottom(), 2) );
      return rez;
  }

  Point2D m_left_bottom = {0.0f, 0.0f}, m_right_top = {0.0f, 0.0f};
};
