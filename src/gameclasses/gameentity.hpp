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

  GameEntity2D(Box2D const & newBox)
    :m_box(newBox)
  {}

  // Getters
  inline Box2D const GetBox() const { return m_box; }
  inline GameEntity2D GetEntity() const { return GameEntity2D { m_box }; }
  // Setters
  inline void SetBox(Box2D const & newBox) { m_box = newBox; }
  inline void SetEntity(GameEntity2D const & newEntity)
  {
    m_box = newEntity.m_box;
  }

  // Logical operators
  bool operator == (GameEntity2D const & obj)
  {
    return obj.GetBox() == GetBox();
  }

private:
  Box2D m_box; // safe field.
};
