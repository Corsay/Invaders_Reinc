#pragma once

#include "geometry/box2d.hpp"
#include "constants.hpp"
#include "logger.hpp"
#include <memory>

enum EntitiesTypes{ GameEntityType, GunType, AlienType, BulletType, ObstacleType }; // enum

class GameEntity2D
{
public:
  // Allow default constructor.
  GameEntity2D() = default;

  // Destructor.
  virtual ~GameEntity2D() = default;

  // Constructors with parameters.
  GameEntity2D(Point2D const & leftBottom, Point2D const & rightTop)
    :m_box(Box2D{ leftBottom, rightTop } )
  {}

  GameEntity2D(Box2D const & newBox)
    :m_box(newBox)
  {}


  // For factory
  virtual inline EntitiesTypes GetEntityType() { return EntitiesTypes::GameEntityType; }
  virtual std::unique_ptr<GameEntity2D> Create()
  {
    return std::unique_ptr<GameEntity2D>(new GameEntity2D());
  }


  // Getters
  inline Box2D const GetBox() const { return m_box; }
  inline Box2D & GetBox() { return m_box; }
  inline GameEntity2D GetEntity() const { return *this; }

  // Setters
  inline void SetBox(Box2D const & newBox) { m_box = newBox; }
  inline void SetEntity(GameEntity2D const & newEntity)
  {
    m_box = newEntity.m_box;
  }


  // Logical operators
  bool operator == (GameEntity2D const & obj) const
  {
    return obj.GetBox() == GetBox();
  }


  // Redefinition
  friend std::ostream & operator << (std::ostream & os, GameEntity2D const & obj)
  {
    os << "GameEntity2D {" << obj.GetBox() << "}";
    return os;
  }

private:
  Box2D m_box;
};
