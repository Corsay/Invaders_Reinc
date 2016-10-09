#pragma once

#include "gun.hpp"
#include "alienmanager.hpp"
#include "bulletmanager.hpp"
#include "obstacle.hpp"

class Space2D : public Box2D
{
public:
  // Allow default constructor.
  Space2D() = default;

  // Constructors with parameters.
  // need


  // Constructor with initialization list.
  // need or not (?!)


  // Copy constructor
  // can be useful


  // Move constructor
  // not need


  // Getters
  // all getters for new fields


  // Setters
  // all settsers for new fields


  // Logical operators
  // Not need


  // Assignment operator.
  // can be useful =


  // Move operator
  // not need


  // Math operations
  // don't know need or not (?!)


  // Capabilities

  // function for input processing:............
  // check m_gun state
  // check m_alienManager state
  // move gun (send command to function in gun)
  // move aliens (standart moving or boss configuration moving) (send command to function in alienManager)
  // move bullets (send command to function in bulletManager)

  /*
   * how can check bullets intersection with obstacle/gun/alien variant:
   send m_bulletManager (if it state return nullptr(zero bullets strated))
   too functions in m_obstacles (if it != nullptr) and m_alienManager (if it != nullptr) (if it == nullptr -> lvl passed)
  */

  // functions of frame update:...............
  // redraw


  // Redefinition
  // square brackets
private:

  // Box2D
  // leftBottom() - left bottom point of the gun
  // rightTop()   - right top point of the gun
  // left()       - left/right/top/bottom border of all game space, if one of the next objects leave space(like bullets), it destroy

  // m_gun == nullptr -> level failed (game over or restart level, because gun was destroyed by alien)
  // -> destroy Space
  Gun2D m_gun;                       // one gun
  // m_alienManager == nullptr -> level passed (go to the next level or game succesfull finished, because all aliens on current level destroyed)
  // -> destroy space
  Alien2DManager m_alienManager;     // one alien manager
  // m_bulletManager == nullptr -> incorrect work of the classes
  // -> destroyed only then destroyed space
  Bullet2DManager m_bulletManager;   // one bullet manager
  // m_obstacle == nullptr - destroyed all obstacles
  // -> nothing to do
  Obstacle2D m_obstacles;            // vector of obstacles
};
