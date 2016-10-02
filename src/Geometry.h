#pragma once
#include <iostream>
#include <initializer_list>
#include <cmath>

using namespace std;
float const kEps=0.00001f;
float constexpr RAD=3.141592f/180.0f;
enum Direction{UP, DOWN};

class Point2D;
class Box2D;
class Ray2D;
class Ray2D_G;

class Point2D
{
public:
  float m_x = 0.0f, m_y = 0.0f;// ну это действительно удобнее

  // Разрешаем конструирование по умолчанию.
  Point2D() = default;

  // Конструктор копирования.
  Point2D(Point2D const & obj)
    : m_x(obj.m_x), m_y(obj.m_y)
  {}

  // Конструктор с параметрами.
  Point2D(float x, float y)
    : m_x(x), m_y(y)
  {}

  // Getters
  float & x() { return m_x; }
  float & y() { return m_y; }
  float const & x() const { return m_x; }
  float const & y() const { return m_y; }

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
  bool operator <= (Point2D const & obj) const
  {
    return m_x <= obj.m_x+kEps && m_y <= obj.m_y+kEps;
  }
  bool operator >= (Point2D const & obj) const
  {
    return m_x >= obj.m_x-kEps && m_y >= obj.m_y-kEps;
  }
  bool operator < (Point2D const & obj) const
  {
    return m_x < obj.m_x+kEps && m_y < obj.m_y;
  }
  bool operator > (Point2D const & obj) const
  {
    return m_x>obj.m_x-kEps && m_y > obj.m_y-kEps;
  }

  Point2D operator + (Point2D const & obj) const
  {
    return { m_x + obj.m_x, m_y + obj.m_y };
  }
  Point2D operator - (Point2D const & obj) const
  {
    return { m_x - obj.m_x, m_y - obj.m_y };
  }
  Point2D operator - () const
  {
    return { -m_x, -m_y };
  }
  Point2D operator * (float scale) const
  {
    return { m_x * scale, m_y * scale };
  }
  Point2D operator / (float scale) const
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
    m_x+=shift;
  }
  void VerticalShift(float shift)
  {
    m_y+=shift;
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
      return (hasher(p.m_x) ^ (hasher(p.m_y) << 1));
    }
  };

  // Переопределение оператора <<
  friend std::ostream & operator << (std::ostream & os, Point2D const & obj)
  {
    os << "Point2D {" << obj.m_x << ", " << obj.m_y << "}";
    return os;
  }

private:
  bool EqualWithEps(float v1, float v2) const
  {
    return fabs(v1 - v2) < kEps;
  }
};

class Box2D
{
public:
  Box2D() = default;
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
  Box2D(std::initializer_list<Point2D> const & lst)
  {
    Point2D * vals[] = { &m_left_bottom, &m_right_top };
    int const count = sizeof(vals) / sizeof(vals[0]);
    auto it = lst.begin();
    for (int i = 0; i < count && it != lst.end(); i++, ++it)
      *vals[i] = *it;
    Swap();
  }
  Box2D(initializer_list<float> const& lst)
    {
      float *vals[] = { &m_left_bottom.m_x, &m_left_bottom.m_y, &m_right_top.m_x, &m_right_top.m_y };
      auto it = lst.begin();
       //запись координат
      for (int i=0; i<4 && it!=lst.end(); i++, ++it)
        *vals[i] = *it;
      Swap();
    }
  Box2D(Box2D const & obj)
    : m_left_bottom(obj.m_left_bottom), m_right_top(obj.m_right_top)
  {}

  // Getters
  Point2D & left_bottom() { return m_left_bottom; }
  Point2D & right_top() { return m_right_top; }
  Point2D const & left_bottom() const { return m_left_bottom; }
  Point2D const & right_top() const   { return m_right_top; }
  float const left() const   { return m_left_bottom.m_x; } // x min
  float const right() const  { return m_right_top.m_x; }   // x max
  float const top() const    { return m_right_top.m_y; }   // y max
  float const bottom() const { return m_left_bottom.m_y; } // y min

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
  Box2D operator - () const
  {
    return
    {
        -m_left_bottom,
        -m_right_top
    };
  }
  Box2D operator * (float scale) const
  {
    return
    {
        m_left_bottom * scale,
        m_right_top * scale
    };
  }
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
  void HorizontalShift(float shift)
  {
    m_left_bottom.m_x+=shift;
    m_right_top.m_x+=shift;
  }
  void VerticalShift(float shift)
  {
    m_left_bottom.m_y+=shift;
    m_right_top.m_y+=shift;
  }

  // Capabilities
  Point2D Get_center() const
  {
    Point2D p = {(m_left_bottom.m_x + m_right_top.m_x) / 2 , (m_left_bottom.m_y + m_right_top.m_y)/2 };
    return p;
  }

  bool operator &&(Box2D const & obj) const//проверка на пересечение
  {
    return !( top() < obj.bottom() || bottom() > obj.top() || right() < obj.left() || left() > obj.right() );
  }
  bool operator &&(Point2D const & P) const
  {
    return !( P.m_y < bottom() || P.m_y > top() || right() < P.m_x || left() > P.m_y );
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
  }

  double Rectangle_square () const
  {
      double rez = sqrt( powf(right() - left(), 2) * powf(top() - bottom(), 2) );
      return rez;
  }

  Point2D m_left_bottom = {0.0f, 0.0f}, m_right_top = {0.0f, 0.0f};
};

class Ray2D_G
{
  public:
    Ray2D_G()=default;
    Ray2D_G(Point2D& origin,  Direction direction)
      :m_origin(origin), m_direction(direction)
      {}
    Ray2D_G(float originX, float originY,  Direction direction)
      :m_origin(originX, originY), m_direction(direction)
      {}

    float const X(){return m_origin.m_x;}
    float const Y(){return m_origin.m_y;}
    Direction const direction(){return m_direction;}

    void X(float x){m_origin.m_x=x;}
    void Y(float y){m_origin.m_y=y;}
    void direction(Direction direction){m_direction=direction;}

    bool operator &&(Box2D& Box)
    {
        //если не может попасть теоретически
      if( (m_direction==UP && Box.top()<m_origin.m_y) || (m_direction==DOWN && Box.bottom()>m_origin.m_y) )
        return false;

      if(m_origin.m_x>Box.right() || m_origin.m_x<Box.left())
        return false;

      return true;
    }
  private:
    Point2D m_origin={0.0f, 0.0f};
    Direction m_direction=UP;

};

class Ray2D
{
  public:
    Ray2D()=default;
    Ray2D(Point2D& origin,  float direction)
      :m_origin(origin),
       m_direction(direction-int(direction/360.0f)*360.0f )//аналогично direction%360
      {
        if(direction<0.0f)
          direction+=360.0f;
      }
    Ray2D(float originX, float originY,  float direction)
      :m_origin(originX, originY),
       m_direction(direction-int(direction/360.0f)*360.0f )//аналогично direction%360
      {
        if(direction<0.0f)
          direction+=360.0f;
      }
    Ray2D(std::initializer_list<float> const & lst)
    {
      auto it=lst.begin();
      m_origin.m_x=*it;
      it++;

      if(it!=lst.end())
      {
          m_origin.m_y=*it;
          it++;
      }

      if(it!=lst.end())
      {
        m_direction= *it-int(*it/360.0f)*360.0f;
        if(m_direction<0.0f)
          m_direction+=360.0f;
      }
    }

    float const X(){return m_origin.m_x;}
    float const Y(){return m_origin.m_y;}
    float const direction(){return m_direction;}
    Point2D const origin(){return m_origin;}
    void X(float x){m_origin.m_x=x;}
    void Y(float y){m_origin.m_y=y;}
    void direction(float direction)
    {
      m_direction = direction-int(direction/360.0f)*360.0f;
      if(m_direction<0.0f)
        m_direction+=360.0f;
    }
    void origin(Point2D& origin){m_origin=origin;}

    bool operator ==(Ray2D const & Ray) const
    {
      return(m_origin==Ray.m_origin && fabs(m_direction-Ray.m_direction)<kEps);
    }
    bool operator !=(Ray2D const & Ray) const
    {
      return !(m_origin==Ray.m_origin && fabs(m_direction-Ray.m_direction)<kEps);
    }
    bool operator &&(Box2D& Box)
    {
      float k=tan(m_direction*RAD);
      float b=m_origin.m_y-k*m_origin.m_x;
      float coord=0.0f;

      Direction orient=UP;//1==луч идет влево, 0-вправо от точки
      if(m_direction>=180.0f)
        orient=DOWN;

      //right
      coord=k*Box.right()+b;
      if( ( (orient==UP && Box.top()+kEps>=m_origin.m_y) || (orient==DOWN && Box.bottom()-kEps<=m_origin.m_y))//отсекаем ненужную половину луча
          && coord<=Box.top()+kEps && coord>=Box.bottom()-kEps)
        return true;
      //left
      coord=k*Box.left()+b;
      if( ( (orient==UP && Box.top()+kEps>=m_origin.m_y) || (orient==DOWN && Box.bottom()-kEps<=m_origin.m_y))
          && coord<=Box.top()+kEps && coord>=Box.bottom()-kEps)
        return true;
      //top
      coord=float((Box.top()-b))/k;
      if( ( (orient==UP && Box.top()+kEps>=m_origin.m_y) || (orient==DOWN && Box.bottom()-kEps<=m_origin.m_y))
          && coord<=Box.right()+kEps && coord>=Box.left()-kEps)
        return true;

      return false;
    }
    bool operator &&(Point2D& point)
    {
      float k=tan(m_direction*RAD);
      float b=m_origin.m_y-k*m_origin.m_x;

      float coord=k*point.m_x+b;

      if(abs(coord-point.m_y)<kEps)
        return true;
      return false;
    }

    float operator [] (unsigned int i) const
    {
      switch(i)
      {
        case 0:
          return m_origin.m_x;
          break;
        case 1:
          return m_origin.m_y;
          break;
        case 2:
          return m_direction;
          break;
        default:
          return 0.0f;
      }
    }

    void VerticalShift(float shift){m_origin.VerticalShift(shift);}
    void HorizontalShift(float shift){m_origin.HorizontalShift(shift);}
    void DirectionShift(float shift)
    {
      m_direction+=shift;
      m_direction = m_direction-int(m_direction/360.0f)*360.0f;
      if(m_direction<0.0f)
        m_direction+=360.0f;
    }

    friend std::ostream& operator << (std::ostream & os, Ray2D const & obj)
    {
      os << "Ray2D {" << obj.m_origin << ", " << obj.m_direction << "}";
      return os;
    }
  private:
    Point2D m_origin={0.0f, 0.0f};
    float m_direction=UP;

};
