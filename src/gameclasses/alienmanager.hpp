#pragma once

#include "alien.hpp"
#include <vector>

class Alien2DManager
{
public:
  // Allow default constructor.
  Alien2DManager() = default;

  // Constructors with parameters.
  Alien2DManager(int const countRow, int const countColumn, int const level)
  {
    // в зависимости от значения переменной level будут генерироваться разные волны пришельцев
    m_liveAliensCount = countRow * countColumn;

    m_aliens.reserve(countRow);
    for (int i = 0; i < countRow; i++)
    {
      m_aliens[i].reserve(countColumn);
      for(int j = 0; j < countColumn; j++)
        m_aliens[i][j] = new Alien2D
        (
          Point2D
          {
            ALIEN_BOX_LEFT+j*(AlIEN_WIDTH+ALIEN_HORIZONTAL_DISTANCE),
            ALIEN_BOX_TOP+i*(ALIEN_HEIGHT+ALIEN_VERTICAL_DISTANCE)
          },
          Point2D
          {
            ALIEN_BOX_LEFT+j*(AlIEN_WIDTH+ALIEN_HORIZONTAL_DISTANCE)+AlIEN_WIDTH,
            ALIEN_BOX_TOP+i*(ALIEN_HEIGHT+ALIEN_VERTICAL_DISTANCE)+ALIEN_HEIGHT,
          },
          ALIEN_HEALTH_START,
          ALIEN_SPEED_SHOOT_START
        );
    }
  }


  // Getters
  inline int const getliveAliensCount() const { return m_liveAliensCount; }
  inline int const getCountOfRows() const     { return m_aliens.size(); }
  inline int const getCountOfColumn() const   { return m_aliens[0].size(); }

  // Capabilities
  bool AliensMove(Box2D const & border)
  {
    static short stepSign = -1;
    //отслеживать достижение границ
    //при достижении границы сменить знак и сдвинуться вниз

    for(int i = 0; i < m_aliens.size(); i++)
      for(int j = 0; j < m_aliens[0].size(); j++)
        m_aliens->HorizontalShift(stepSign * ALIENT_HORIZONTAL_STEP);
  }

  Alien2D GetShooter(Box2D const & gunBorder)
  {
    // chosing by AI(Artificial intelligence) who will be shoot
    return m_aliens[0][0];  // default
  }

  // need to add function:
  // work with bulletManager
  // check intersection bullet with one of the m_aliens (as param it get Bullet2D(check its as Box2D && Box2D))
  // move aliens (standart moving or boss configuration moving)


  // Redefinition
  /*Alien2D * operator[](unsigned int i)
  {
    if (i <= m_aliens.size()) return m_aliens[i];
    return vector<Alien2D *>;
  }*/
private:

  std::vector< std::vector<Alien2D *> > m_aliens;      // matrix of Aliens
  // m_liveAliensCount == 0 - level passed
  // -> destroy AlienManager
  int m_liveAliensCount = 5;
};
