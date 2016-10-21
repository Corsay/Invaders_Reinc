#pragma once

#include "alien.hpp"
#include <vector>

using AlienVector = std::vector<Alien2D>;     // Alias
using AlienMatrix = std::vector<AlienVector>; // Alias

class Alien2DManager
{
public:
  // constructor.
  Alien2DManager()
  {
    CreateAlienMatrix(5, 11); // initialize default matrix
  }

  // Destructor.
  ~Alien2DManager() = default;

  // Constructors with parameters.
  Alien2DManager(size_t const countRow, size_t const countColumn)
  {
    CreateAlienMatrix(countRow, countColumn);
  }

  // no copy constructor
  Alien2DManager(Alien2DManager const & obj) = delete;

  // assignment operator (for next level reinit)
  Alien2DManager & operator = (Alien2DManager const & obj)
  {
    if (this == &obj) return *this;
    m_aliens = obj.GetAlienMatrix();
    m_liveAliensCount = obj.GetLiveAliensCount();
    return *this;
  }

  // Getters
  inline AlienMatrix const GetAlienMatrix() const { return m_aliens; }
  inline size_t const GetLiveAliensCount() const  { return m_liveAliensCount; }
  inline size_t const GetCountOfRows() const      { return m_aliens.size(); }
  inline size_t const GetCountOfColumn() const    { return m_aliens[0].size(); }

  // Setters
  inline void SetliveAliensCount(size_t newLiveAliensCount) { m_liveAliensCount = newLiveAliensCount; }

  // Capabilities
  void AliensMove(Box2D const & border)
  {
    throw std::runtime_error("Not released Alien2DManager::AliensMove.");
  }

  Alien2D SelectShooter(Box2D const & gunBorder)
  {
    // chosing by game AI(Artificial intelligence) who will be shoot
    return m_aliens[0][0];  // default
  }
private:

  void CreateAlienMatrix(size_t const countRow, size_t const countColumn)
  {
    m_liveAliensCount = countRow * countColumn;

    m_aliens.reserve(countRow);
    for (size_t i = 0; i < countRow; ++i)
    {
      std::vector<Alien2D> tempVect;
      tempVect.reserve(countColumn);
      for(size_t j = 0; j < countColumn; ++j)
      {
        tempVect.push_back
        (
          Alien2D
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
          )
        );
      }
      m_aliens.push_back(tempVect);
    }
  }

  AlienMatrix m_aliens;          // matrix of Aliens
  size_t m_liveAliensCount = 55; // count of live aliens
};
