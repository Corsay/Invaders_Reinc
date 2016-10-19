#pragma once

#include "box2d.hpp"
#include "constants.hpp"

class GameEntity2D
{
public:
  // Allow default constructor.
  GameEntity2D() = default;

  // Destructor.
  ~GameEntity2D() = default;

  // Constructors with parameters.
  GameEntity2D(Point2D const & leftBottom, Point2D const & rightTop)
      :m_box( Box2D{ leftBottom, rightTop } )
  {}


  GameEntity2D(Box2D newBox)
    :m_box(newBox)
  {}

  // Getters
  inline Box2D GetBorder() const { return m_box; }
  // Setters
  inline void SetBorder(Box2D const newBox) { m_box = newBox; }

  bool operator == (GameEntity2D const & obj)
  {
    return obj.GetBorder() == m_box;
  }

  // Capabilities

protected:
  Box2D m_box = Box2D{ Point2D{0.0f, 0.0f}, Point2D{0.0f, 0.0f} };
};
