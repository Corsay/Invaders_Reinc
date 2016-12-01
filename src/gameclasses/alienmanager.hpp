#pragma once

#include <iostream>
#include "alien.hpp"
#include "gun.hpp"
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
    logger << "Create Matrix of alien 5*11" << std::endl;
    CreateAlienMatrix(5, 11); // initialize default matrix   
  }

  // Destructor.
  ~Alien2DManager() = default;

  // Constructors with parameters.
  Alien2DManager(size_t const countRow, size_t const countColumn)
  {
    logger << "Create Matrix of alien " << countRow << "*" << countColumn << std::endl;
    CreateAlienMatrix(countRow, countColumn);  
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
  inline Box2D const GetBox() const               { return m_border; }



  // Capabilities
  bool CheckIntersection(Bullet2D const & bul, int * rate)
  {
    for(int i = 0; i < m_aliens.size(); i++)
      for(int j = 0; j < m_aliens[0].size(); j++)
        if (m_aliens[i][j] != nullptr)
          if (m_aliens[i][j]->GetBox() && bul.GetBox())
          {
            bul.Inform(*m_aliens[i][j]);

            if(m_aliens[i][j]->GetHealth() <= bul.GetHealth())
            {
              *rate = m_aliens[i][j]->GetType();

              delete m_aliens[i][j];
              m_aliens[i][j] = nullptr;

              --m_liveAliensCount;
              if(m_liveAliensCount == 0)
                return true;

              if(BoxInColumn(j) == nullptr)
              {
                std::cout << "before " <<m_border << std::endl;
                DeleteColumn(j);
                if(j == 0)
                  m_border.SetLeft(m_border.left() + ALIEN_HORIZONTAL_DISTANCE + ALIEN_WIDTH);
                if(j == m_aliens[0].size() - 1)
                {
                  std::cout << "+";
                  m_border.SetRight(m_border.right() - ( ALIEN_HORIZONTAL_DISTANCE + ALIEN_WIDTH) );
                }
                std::cout << "after " << m_border << std::endl << std::endl;
              }

              if(BoxInLine(i) == nullptr)
              {
                m_aliens.erase(m_aliens.begin() + i);
                if(i == 0)
                  m_border.SetBottom(m_border.bottom() + ( ALIEN_VERTICAL_DISTANCE + ALIEN_HEIGHT ) );
              }


            }
            else  // ec heals
            {
              m_aliens[i][j]->SetHealth(m_aliens[i][j]->GetHealth() - bul.GetHealth());
            }
            return true;
          }
    return false;
  }

  bool CheckIntersection(Gun2D * gun)
  {
    int i, j;
    // get shooted alien position
    i = (gun->GetBox().top() - (m_border.bottom() + ALIEN_HEIGHT) + ALIEN_VERTICAL_DISTANCE) / (ALIEN_VERTICAL_DISTANCE + ALIEN_HEIGHT);
    j = (gun->GetBox().left() - m_border.left() + ALIEN_HORIZONTAL_DISTANCE) / (ALIEN_HORIZONTAL_DISTANCE + ALIEN_WIDTH);
    if (i >= 0 && j >= 0 && i < m_aliens.size() && j < m_aliens[i].size())
    {
      if (m_aliens[i][j] != nullptr)
      {
        if (m_aliens[i][j]->GetBox() && gun->GetBox())
        {
          if (!(gun->GetBox() && m_aliens[i][j]->GetBox()))
            return false;

          gun->SetRate(gun->GetRate() + m_aliens[i][j]->GetType());

          if (BONUS_GOD)
          {
            delete m_aliens[i][j];
            m_aliens[i][j] = nullptr;
            --m_liveAliensCount;
            return true;  // if god mode bonus
          }

          // if intersect
          gun->SetHealth(gun->GetHealth() - m_aliens[i][j]->GetHealth());
          if (gun->GetHealth() <= 0)
          {
            gun->SetLives(gun->GetLives() - 1);
            if (gun->GetLives() > 0) gun->SetHealth(GUN_HEALTH_START);
          }

          logger << *m_aliens[i][j] << std::endl << *gun << std::endl;

          delete m_aliens[i][j];
          m_aliens[i][j] = nullptr;
          --m_liveAliensCount;

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
    if (!last_is_down && (m_border.left() <= GAME_PADDING_LEFT ||
      m_border.right() >= (LAST_WINDOW_HORIZONTAL_SIZE - GAME_PADDING_RIGHT)))
    {
      down = true;
    }

    if(!down)
      m_border.HorizontalShift(direction * ALIENT_HORIZONTAL_STEP);
    else
      m_border.VerticalShift(-ALIENT_VERTICAL_STEP);

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
  Alien2D * SelectShooter(Box2D const & gunBorder)
  {
    srand(time(0));
    int j = rand() % m_aliens[0].size();
    for (int i = 0; i < m_aliens.size(); i++)
      if (m_aliens[i][j] != nullptr)
        return m_aliens[i][j];
    return nullptr;
  }

  void clear()
  {
    for (auto it = m_aliens.begin(); it != m_aliens.end(); ++it)
    {
      AlienVector vect = *it;
      for(auto it2 = vect.begin(); it2 != vect.end(); ++it2)
      {
        if ((*it2) != nullptr)
        {
          delete *it2;
          *it2 = nullptr;
        }
      }
      vect.clear();
    }
    m_aliens.clear();
  }

  void log()
  {
    logger << "____________________________" << std::endl;
    logger << "____________________________" << std::endl;
    logger << "____________________________" << std::endl;
    logger << "LOGING ALIEN MATRIX CREATION" << std::endl;
    logger << "____________________________" << std::endl;
    logger << m_liveAliensCount << std::endl;
    for (auto it = m_aliens.begin(); it != m_aliens.end(); ++it)
    {
      AlienVector vect = *it;
      for(auto it2 = vect.begin(); it2 != vect.end(); ++it2)
      {
        if ((*it2) != nullptr)
        {
          logger << (**it2) << std::endl;
        }
        else
        {
          logger << "nullptr" << std::endl;
        }
      }
      logger << std::endl;
    }
    logger << "________________________________" << std::endl;
    logger << "LOGING ALIEN MATRIX CREATION END" << std::endl;
    logger << "________________________________" << std::endl;
    logger << "________________________________" << std::endl;
    logger << "________________________________" << std::endl;
    logger << std::endl << std::endl << std::endl << std::endl;
  }

private:
  Box2D * BoxInColumn(int j)
  {
    for (int b = 0; b < m_aliens.size(); b++)
      if (m_aliens[b][j] != nullptr)
        return &(m_aliens[b][j]->GetBox());
    return nullptr;
  }

  Box2D * BoxInLine(int i)
  {
    for (int b = 0; b < m_aliens[0].size(); b++)
      if (m_aliens[i][b] != nullptr)
        return &(m_aliens[i][b]->GetBox());
    return nullptr;
  }

  void DeleteColumn(int j)
  {
    if(j < 0 || j > m_aliens.size() - 1)
      return;
    for(int k = 0; k < m_aliens.size(); k++)
      m_aliens[k].erase(m_aliens[k].begin() + j);
  }

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
    m_border = Box2D{ m_aliens[0][0]->GetBox().leftBottom(), m_aliens[m_aliens.size() - 1][m_aliens[0].size() - 1]->GetBox().rightTop() };

    log();
  }

  Box2D m_border;
  AlienMatrix m_aliens;          // matrix of Aliens
  size_t m_liveAliensCount = 55; // count of live aliens
};
