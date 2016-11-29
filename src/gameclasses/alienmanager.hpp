#pragma once

#include <iostream>
#include "alien.hpp"
#include "bullet.hpp"
#include <vector>
using AlienVector = std::vector<Alien2D *>;     // Alias
using AlienMatrix = std::vector<AlienVector>;   // Alias

class Alien2DManager
{
public:
  // constructor.
  Alien2DManager()
  {
    CreateAlienMatrix(5, 11); // initialize default matrix
    logger << "Create Matrix of alien 5*11" << std::endl;
  }

  // Destructor.
  ~Alien2DManager() = default;

  // Constructors with parameters.
  Alien2DManager(size_t const countRow, size_t const countColumn)
  {
    CreateAlienMatrix(countRow, countColumn);
    logger << "Create Matrix of alien " << countRow << "*" << countColumn << std::endl;
  }

  // copy constructor
  Alien2DManager(Alien2DManager const & obj)
  {
    m_aliens = obj.GetAlienMatrix();
    m_liveAliensCount = obj.GetLiveAliensCount();
  }

  // assignment operator (for next level reinit)
  Alien2DManager & operator = (Alien2DManager const & obj)
  {
    if (this == &obj) return *this;
    m_aliens = obj.GetAlienMatrix();
    m_liveAliensCount = obj.GetLiveAliensCount();
    return *this;
  }


  // Getters
  inline AlienMatrix const & GetAlienMatrix() const { return m_aliens; }
  inline AlienMatrix & GetAlienMatrix()           { return m_aliens; }
  inline size_t const GetLiveAliensCount() const  { return m_liveAliensCount; }
  inline size_t const GetCountOfRows() const      { return m_aliens.size(); }
  inline size_t const GetCountOfColumn() const    { return m_aliens[0].size(); }

  // Capabilities
  bool CheckIntersection(Bullet2D const & bul, int * rate)
  {
    int i, j;
    // get shooted alien position
    i = (bul.GetBox().top() - m_alien00_top + ALIEN_VERTICAL_DISTANCE) / (ALIEN_VERTICAL_DISTANCE + ALIEN_HEIGHT);
    j = (bul.GetBox().left() - m_alien00_left + ALIEN_HORIZONTAL_DISTANCE) / (ALIEN_HORIZONTAL_DISTANCE + ALIEN_WIDTH);
    if (i < m_aliens.size() && j < m_aliens[i].size())
    {
      if (m_aliens[i][j] != nullptr)
      {
        if (m_aliens[i][j]->GetBox() && bul.GetBox())
        {
          bul.Inform(*m_aliens[i][j]);
          if(m_aliens[i][j]->GetHealth() <= bul.GetHealth())
          {
            *rate = m_aliens[i][j]->GetType();

            delete m_aliens[i][j];
            m_aliens[i][j] = nullptr;
            --m_liveAliensCount;
          }
          else  // ec heals
          {
            m_aliens[i][j]->SetHealth(m_aliens[i][j]->GetHealth() - bul.GetHealth());
          }
          return true;
        }
      }
    }
    return false;
  }

  void AliensMove()
  {
    static short direction = 1;
    static bool down = false, last_is_down = false;
    if (!last_is_down && (m_alien00_left < GAME_PADDING_LEFT ||
      m_alien00_left + this->GetCountOfColumn() * (ALIEN_WIDTH + ALIEN_HORIZONTAL_DISTANCE) - ALIEN_HORIZONTAL_DISTANCE
      > (LAST_WINDOW_HORIZONTAL_SIZE - GAME_PADDING_RIGHT)))
    down = true;

    if(!down)
      m_alien00_left += direction * ALIENT_HORIZONTAL_STEP;
    else
      m_alien00_top -= ALIENT_VERTICAL_STEP;

    for (size_t i = 0; i < m_aliens.size(); ++i)
    {
      for(size_t j = 0; j < m_aliens[i].size(); ++j)
      {
        if (m_aliens[i][j] != nullptr)
        {
          if(!down)
            m_aliens[i][j]->GetBox().HorizontalShift(direction * ALIENT_HORIZONTAL_STEP);
          else
            m_aliens[i][j]->GetBox().VerticalShift(-ALIENT_VERTICAL_STEP);
        }
      }
    }

    if(last_is_down)
      last_is_down = false;

    if(down)
    {
      last_is_down = true;
      direction *= -1;
    }

    down = false;
  }

  // chosing who will be shoot
  Alien2D SelectShooter(Box2D const & gunBorder)
  {
    size_t column = GetCountOfColumn() - 1;
    size_t row = 0;
    do
    {
      column = rand() % (GetCountOfColumn() - 1);
      row = 0;

      while (m_aliens[row][column] == nullptr && row != GetCountOfRows())
      {
        row++;
      }
    }
    while(m_aliens[row][column] == nullptr);

    return *m_aliens[row][column];  // default
  }

private:
  void CreateAlienMatrix(size_t const countRow, size_t const countColumn)
  {
    int curType;
    m_liveAliensCount = countRow * countColumn;

    m_aliens.reserve(countRow);
    for (size_t i = 0; i < countRow; ++i)
    {
      if (i < 2) curType = AlienTypes::Pirate;
      else if (i < 4) curType = AlienTypes::Raider;
      else if (i < 5) curType = AlienTypes::Bombardier;

      std::vector<Alien2D *> tempVect;
      tempVect.reserve(countColumn);
      for(size_t j = 0; j < countColumn; ++j)
      {
        tempVect.push_back
        (
          new Alien2D
          (
            Point2D
            {
              ALIEN_BOX_LEFT + j * (ALIEN_WIDTH + ALIEN_HORIZONTAL_DISTANCE),
              ALIEN_BOX_TOP + i * (ALIEN_HEIGHT + ALIEN_VERTICAL_DISTANCE)
            },
            Point2D
            {
              ALIEN_BOX_LEFT + j * (ALIEN_WIDTH + ALIEN_HORIZONTAL_DISTANCE) + ALIEN_WIDTH,
              ALIEN_BOX_TOP + i * (ALIEN_HEIGHT + ALIEN_VERTICAL_DISTANCE) + ALIEN_HEIGHT,
            },
            ALIEN_HEALTH_START,
            ALIEN_SPEED_SHOOT_START,
            curType
          )
        );
      }
      m_aliens.push_back(tempVect);
    }
    m_alienBottom = m_aliens[0][0]->GetBox().bottom();
    m_alien00_top = m_aliens[0][0]->GetBox().top();
    m_alien00_left = m_aliens[0][0]->GetBox().left();
  }

  float m_alienBottom;
  float m_alien00_top, m_alien00_left;
  AlienMatrix m_aliens;          // matrix of Aliens
  size_t m_liveAliensCount = 55; // count of live aliens
};
