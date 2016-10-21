#pragma once

#include "point2d.hpp"

class Box2D
{
public:
  // Allow default constructor.
  Box2D() = default;

  // Default destructor.
  ~Box2D() = default;

  // Constructors with parameters.
  Box2D(Point2D const leftBottom, Point2D const rightTop)
    : m_leftBottom(leftBottom), m_rightTop(rightTop)
  {
    Swap();
  }

  Box2D(float const x1, float const y1, float const x2, float const y2)
    : m_leftBottom(x1, y1), m_rightTop(x2, y2)
  {
    Swap();
  }

  // Constructor with initialization list.
  Box2D(std::initializer_list<Point2D> const & lst)
  {
    Point2D * vals[] = { &m_leftBottom, &m_rightTop };
    int const count = sizeof(vals) / sizeof(vals[0]);
    auto it = lst.begin();
    for (int i = 0; i < count && it != lst.end(); i++, ++it)
      *vals[i] = *it;
    Swap();
  }

  Box2D(std::initializer_list<float> const & lst)
  {
    Point2D * vals[] = { &m_leftBottom, &m_rightTop };
    auto it = lst.begin();
    // writing coord's
    for (int i = 0; i < 2 && it != lst.end(); i++, ++it)
    {
      vals[i]->SetX(*it);
      it++;
      if (it != lst.end()) vals[i]->SetY(*it);
    }
    Swap();
  }

  // Copy constructor
  Box2D(Box2D const & obj)
    : m_leftBottom(obj.m_leftBottom), m_rightTop(obj.m_rightTop)
  {}

  // Move constructor
  Box2D(Box2D && obj)
  {
    m_leftBottom = std::move(obj.m_leftBottom);
    m_rightTop = std::move(obj.m_rightTop);
  }

  // Getters
  inline Box2D const GetBorder() const { return *this; }
  inline Point2D const & leftBottom() const { return m_leftBottom; }
  inline Point2D const & rightTop() const   { return m_rightTop; }
  inline float const left() const   { return m_leftBottom.x(); } // x min
  inline float const right() const  { return m_rightTop.x(); }   // x max
  inline float const top() const    { return m_rightTop.y(); }   // y max
  inline float const bottom() const { return m_leftBottom.y(); } // y min

  // Setters
  inline void SetBorder(Box2D const & box)
  {
    this->m_leftBottom = box.m_leftBottom;
    this->m_rightTop = box.m_rightTop;
  }

  // Logical operators
  bool operator == (Box2D const & obj) const
  {
    return (m_leftBottom == obj.leftBottom() && m_rightTop == obj.rightTop());
  }

  bool operator != (Box2D const & obj) const
  {
    return !operator==(obj);
  }

  bool operator < (Box2D const & obj) const
  {      
    return RectangleSquare() < obj.RectangleSquare();
  }

  // Assignment operator.
  Box2D & operator = (Box2D const & obj)
  {
    if (this == &obj) return *this;
    m_leftBottom = obj.m_leftBottom;
    m_rightTop = obj.m_rightTop;
    return *this;
  }

  // Move operator
  Box2D & operator = (Box2D && obj)
  {
    if (this == &obj) return *this;
    m_leftBottom = std::move(obj.m_leftBottom);
    m_rightTop = std::move(obj.m_rightTop);
    return *this;
  }

  // Math operations
  Box2D operator + (Box2D const & obj) const
  {
    return
    {
      m_leftBottom + obj.m_leftBottom,
      m_rightTop + obj.m_rightTop
    };
  }

  Box2D operator - (Box2D const & obj) const
  {
    return
    {
      m_leftBottom - obj.m_leftBottom,
      m_rightTop - obj.m_rightTop
    };
  }

  Box2D operator - ()
  {
    return
    {
      -m_leftBottom,
      -m_rightTop
    };
  }

  Box2D operator * (float scale)
  {
    return
    {
      m_leftBottom * scale,
      m_rightTop * scale
    };
  }

  Box2D operator / (float scale)
  {
    return
    {
      m_leftBottom / scale,
      m_rightTop / scale
    };
  }

  Box2D & operator += (Box2D const & obj)
  {
    m_leftBottom += obj.leftBottom();
    m_rightTop += obj.rightTop();
    return *this;
  }

  Box2D & operator -= (Box2D const & obj)
  {
    m_leftBottom -= obj.leftBottom();
    m_rightTop -= obj.rightTop();
    return *this;
  }

  Box2D & operator *= (float scale)
  {
    m_leftBottom *= scale;
    m_rightTop *= scale;
    return *this;
  }

  Box2D & operator /= (float scale)
  {
    m_leftBottom /= scale;
    m_rightTop /= scale;
    return *this;
  }

  // Capabilities
  Point2D GetCenter() const
  {
    Point2D p = {(m_leftBottom.x() + m_rightTop.x()) / 2 , (m_leftBottom.y() + m_rightTop.y())/2 };
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

  void HorizontalShift(float const shift)
  {
    m_leftBottom.SetX(m_leftBottom.x() + shift);
    m_rightTop.SetX(m_rightTop.x() + shift);
    Swap();
  }
  void VerticalShift(float const shift)
  {
    m_leftBottom.SetY(m_leftBottom.y() + shift);
    m_rightTop.SetY(m_rightTop.y() + shift);
    Swap();
  }

  // Redefinition
  Point2D operator [] (unsigned int index) const
  {
    if (index >= 2) return {0.0f,0.0f};
    return index == 0 ? m_leftBottom : m_rightTop;
  }

  friend std::ostream & operator << (std::ostream & os, Box2D const & obj)
  {
    os << "Box2D {" << obj.leftBottom() << ", " << obj.rightTop() << "}";
    return os;
  }

  // add hash function
  struct Hash
  {
    size_t operator()(Box2D const & p) const
    {
      Point2D::Hash hasher;
      return (hasher(p.leftBottom()) ^ (hasher(p.rightTop()) << 1));
    }
  };

private:

  void Swap()
  {  
    if (m_leftBottom > m_rightTop) m_leftBottom = std::move(m_rightTop);

    if (left() > right() || bottom() > top())
    {
      std::swap(m_leftBottom.y(), m_rightTop.y());
    }
  }

  double RectangleSquare() const
  {
    double ab = top() - bottom();
    double ac = right() - left();
    return ab * ac;
  }

  Point2D m_leftBottom = {0.0f, 0.0f}, m_rightTop = {0.0f, 0.0f};
};
