#include <iostream>
#include <initializer_list>
#include <cmath>

using namespace std;
float const Eps=0.001f;
float constexpr RAD=3.141592f/180.0f;

class Point2D;
class Box2D;
class Ray2D;
class Ray2D_G;

class Point2D
{
public:
  float m_x = 0.0f, m_y = 0.0f;
//-----------------------------------------для удобства координаты открытые
  Point2D() = default;
  Point2D(Point2D const & obj)
    : m_x(obj.m_x), m_y(obj.m_y)
  {}
  Point2D(float x, float y)
    : m_x(x), m_y(y)
  {}
  Point2D(std::initializer_list<float> const & lst)
  {
    float * vals[] = { &m_x, &m_y };
    int const count = sizeof(vals) / sizeof(vals[0]);
    auto it = lst.begin();

    for (int i = 0; i < count && it != lst.end(); i++, ++it)
      *vals[i] = *it;
  }

  Point2D & operator = (Point2D const & obj)
  {
    if (this == &obj) return *this;
    m_x = obj.m_x;
    m_y = obj.m_y;
    return *this;
  }

  bool operator == (Point2D const & obj) const
  {
    return abs(m_x-obj.m_x)<Eps && abs(m_y-obj.m_y)<Eps;
  }
  bool operator != (Point2D const & obj) const
  {
    return !operator==(obj);
  }


  bool operator <= (Point2D const & obj) const
  {
    return m_x <= obj.m_x && m_y <= obj.m_y;
  }
  bool operator >= (Point2D const & obj) const
  {
    return m_x >= obj.m_x && m_y >= obj.m_y;
  }
  bool operator < (Point2D const & obj) const
  {
    return m_x < obj.m_x && m_y < obj.m_y;
  }
  bool operator > (Point2D const & obj) const
  {
    return m_x > obj.m_x && m_y > obj.m_y;
  }
};



class Box2D
{
  public:
    Box2D()=default;
    Box2D(Point2D& ld, Point2D& rt)
    {
      if(ld>rt)
        swap(m_ld, m_rt);

      if(ld<rt)
      {
        m_ld=ld;
        m_rt=rt;
      }
    }
    Box2D(initializer_list<float> const& lst)
    {
      Point2D ld{0.0f, 0.0f};
      Point2D rt{0.0f, 0.0f};

      float *vals[] = { &ld.m_x, &ld.m_y, &rt.m_x, &rt.m_y };
      auto it = lst.begin();
       //запись координат
      for (int i=0; i<4 && it!=lst.end(); i++, ++it)
        *vals[i] = *it;

        //если углы не в том порядке меняем
      if(ld>rt)
        swap(m_ld, m_rt);

      if(ld<rt)
      {
        m_ld=ld;
        m_rt=rt;
      }
    }
     //проверка на пересечение
    bool operator &&(Box2D& Box)
    {
      if(this->m_ld.m_x > Box.m_rt.m_x || this->m_rt.m_x < Box.m_ld.m_x || this->m_rt.m_y < Box.m_ld.m_y || this->m_ld.m_y > Box.m_rt.m_y) return false;
      return true;
    }
    /*bool operator &&(Ray2D& Ray){
        Box2D Box1={0.0f, 0.0f, 2.0f, 2.0f};
        Ray2D *Ray1=new Ray2D{1.0f, -1.0f, 135.0f};

        cout << (*Ray1&&Box1) << endl;
    }
    bool operator &&(Point2D &Point){return true;}*/

    inline float const left(){return m_ld.m_x;}
    inline float const right(){return m_rt.m_x;}
    inline float const top(){return m_rt.m_y;}
    inline float const bottom(){return m_ld.m_y;}

    bool left(float new_left)
    {
      if(new_left<(this->right()))
      {
        m_ld.m_x=new_left;
        return true;
      }
      return false;
    }
    bool right(float new_right)
    {
      if(new_right>(this->left()))
      {
        m_rt.m_x=new_right;
        return true;
      }
      return false;
    }
    bool top(float new_top)
    {
      if(new_top>(this->bottom()))
      {
        m_rt.m_y=new_top;
        return true;
      }
      return false;
    }
    bool bottom(float new_bottom)
    {
      if(new_bottom<(this->top()))
      {
        m_ld.m_y=new_bottom;
        return true;
      }
      return false;
    }

  private:
    Point2D m_ld={0.0f, 0.0f};//левый нижний угол
    Point2D m_rt={0.0f, 0.0f};//правый верхний угол
};

enum Direction{UP, DOWN};
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

    inline float const X(){return m_origin.m_x;}
    inline float const Y(){return m_origin.m_y;}
    inline Direction const direction(){return m_direction;}

    inline void X(float x){m_origin.m_x=x;}
    inline void Y(float y){m_origin.m_y=y;}
    inline void direction(Direction direction){m_direction=direction;}

    bool operator &&(Box2D& Box)
    {
        //если не может попасть теоретически
      if( (m_direction==UP && Box.top()<this->Y()) || (m_direction==DOWN && Box.bottom()>this->Y()) )
        return false;

      if(this->X()>Box.right() || this->X()<Box.left())
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

    inline float const X(){return m_origin.m_x;}
    inline float const Y(){return m_origin.m_y;}
    inline float const direction(){return m_direction;}

    inline void X(float x){m_origin.m_x=x;}
    inline void Y(float y){m_origin.m_y=y;}
    inline void direction(float direction)
    {
      m_direction = direction-int(direction/360.0f)*360.0f;
      if(m_direction<0.0f)
        m_direction+=360.0f;
    }

    bool operator &&(Box2D& Box)
    {
      float k=tan(m_direction*RAD);
      float b=m_origin.m_y-k*m_origin.m_x;
      float coord=0.0f;
      //right
      coord=k*Box.right()+b;
      if(coord<=Box.top()+Eps && coord>=Box.bottom()-Eps)
        return true;

      //left
      coord=k*Box.left()+b;
      if(coord<=Box.top()+Eps && coord>=Box.bottom()-Eps)
        return true;

      //top
      coord=float((Box.top()-b))/k;
      if(coord<=Box.right()+Eps && coord>=Box.left()-Eps)
        return true;

      //bottom
      coord=float((Box.bottom()-b))/k;
      if(coord<=Box.right()+Eps && coord>=Box.left()-Eps)
        return true;

      return false;
    }

    bool operator &&(Point2D& point)
    {
      float k=tan(m_direction*RAD);
      float b=m_origin.m_y-k*m_origin.m_x;

      float coord=k*point.m_x+b;

      if(abs(coord-point.m_y)<Eps)
        return true;
      return false;
    }
  private:
    Point2D m_origin={0.0f, 0.0f};
    float m_direction=UP;

};
