#pragma once

#include "box2d.hpp"

float constexpr RAD=3.141592f/180.0f;
enum Direction{UP, DOWN};

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
      m_origin.x(*it);
      it++;

      if(it!=lst.end())
      {
          m_origin.y(*it);
          it++;
      }

      if(it!=lst.end())
      {
        m_direction= *it-int(*it/360.0f)*360.0f;
        if(m_direction<0.0f)
          m_direction+=360.0f;
      }
    }

    float const X(){return m_origin.x();}
    float const Y(){return m_origin.y();}
    float const direction(){return m_direction;}
    Point2D const origin(){return m_origin;}
    void X(float x){m_origin.x(x);}
    void Y(float y){m_origin.y(y);}
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
      float b=m_origin.y()-k*m_origin.x();
      float coord=0.0f;

      //right
      coord=k*Box.right()+b;
      if(coord<=Box.top()+kEps && coord>=Box.bottom()-kEps && checkPoint(Box.right(), coord))
        return true;
      //left
      coord=k*Box.left()+b;
      if(coord<=Box.top()+kEps && coord>=Box.bottom()-kEps && checkPoint(Box.left(), coord))
        return true;
      //top
      coord=float((Box.top()-b))/k;
      if(fabs(coord)<kEps)
          coord=0;
      if(coord<=Box.right()+kEps && coord>=Box.left()-kEps && checkPoint(coord, Box.top()))
        return true;

      return false;
    }
    bool operator &&(Point2D& point)
    {
      float k=tan(m_direction*RAD);
      float b=m_origin.y()-k*m_origin.x();

      float coord=k*point.x()+b;

      if(abs(coord-point.y())<kEps)
        return true;
      return false;
    }

    float operator [] (unsigned int i) const
    {
      switch(i)
      {
        case 0:
          return m_origin.x();
          break;
        case 1:
          return m_origin.y();
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
    bool checkPoint(float x, float y)
    {
        if(m_direction<=180.0f && y<m_origin.y())
            return false;

        if(m_direction>180 && y>=m_origin.y())
            return false;

        if((m_direction<=90 || m_direction>=270) && x<m_origin.x())
            return false;

        if(m_direction>90 && m_direction<270 && x>=m_origin.x())
            return false;

        return true;
    }
    Point2D m_origin={0.0f, 0.0f};
    float m_direction=0.0f;

};

