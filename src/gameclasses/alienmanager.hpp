#pragma once

#include "alien.hpp"
#include <vector>

class Alien2DManager
{
public:
  // constructor.
  Alien2DManager()
  {
    CreateAlienMatrix(5, 11); // initialize default matrix
  }

  // destructor.
  ~Alien2DManager() = default;

  // Constructors with parameters.
  Alien2DManager(int const countRow, int const countColumn)
  {
    CreateAlienMatrix(countRow, countColumn);
  }

  // no copy constructor and assignment operator
  Alien2DManager(Alien2DManager const & obj) = delete;
  void operator = (Alien2DManager const & obj) = delete;

  // Getters
  inline int const GetLiveAliensCount() const { return m_liveAliensCount; }
  inline int const GetCountOfRows() const     { return m_aliens.size(); }
  inline int const GetCountOfColumn() const   { return m_aliens[0].size(); }

  // Setters
  inline void SetliveAliensCount(int new_liveAliensCount) { m_liveAliensCount = new_liveAliensCount; }

  // Capabilities
  bool AliensMove(Box2D const & border)
  {
    static short stepSign = -1;
    //отслеживать достижение границ
    //при достижении границы сменить знак и сдвинуться вниз

    for(int i = 0; i < m_aliens.size(); i++)
      for(int j = 0; j < m_aliens[i].size(); j++)
      {
        m_aliens[i][j]->HorizontalShift(stepSign * ALIENT_HORIZONTAL_STEP);
      }

    return true;
  }

  Alien2D * GetShooter(Box2D const & gunBorder)
  {
    // chosing by AI(Artificial intelligence) who will be shoot
    return m_aliens[0][0];  // default
  }
private:

  void CreateAlienMatrix(int const countRow, int const countColumn)
  {
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
            ALIEN_BOX_LEFT + j * (AlIEN_WIDTH + ALIEN_HORIZONTAL_DISTANCE),
            ALIEN_BOX_TOP + i * (ALIEN_HEIGHT + ALIEN_VERTICAL_DISTANCE)
          },
          Point2D
          {
            ALIEN_BOX_LEFT + j * (AlIEN_WIDTH + ALIEN_HORIZONTAL_DISTANCE) + AlIEN_WIDTH,
            ALIEN_BOX_TOP + i * (ALIEN_HEIGHT + ALIEN_VERTICAL_DISTANCE) + ALIEN_HEIGHT,
          },
          ALIEN_HEALTH_START,
          ALIEN_SPEED_SHOOT_START
        );
    }
  }

  std::vector< std::vector<Alien2D *> > m_aliens;      // matrix of Aliens
  // m_liveAliensCount == 0 - level passed
  // -> destroy AlienManager
  int m_liveAliensCount = 5;
};
