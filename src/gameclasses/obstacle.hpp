#pragma once

#include "lifegameentity.hpp"
#include "bullet.hpp"
#include <vector>

using BoxVector = std::vector<LifeGameEntity2D *>; // Alias
using BoxMatrix = std::vector<BoxVector>;          // Alias

class Obstacle2D final : public LifeGameEntity2D
{
public:
  // constructor.
  Obstacle2D()
  {
    SetEntity(GameEntity2D{Box2D(Point2D(OBSTACLE_BOX_LEFT, OBSTACLE_BOX_BOTTOM), Point2D(OBSTACLE_BOX_LEFT + OBSTACLE_WIDTH, OBSTACLE_BOX_BOTTOM + OBSTACLE_HEIGHT))});
    FillBoxMatrix(Point2D{OBSTACLE_BOX_LEFT, OBSTACLE_BOX_BOTTOM}, Point2D{OBSTACLE_BOX_LEFT + OBSTACLE_WIDTH, OBSTACLE_BOX_BOTTOM + OBSTACLE_HEIGHT}, OBSTACLE_TOTAL_HEALTH);
    SetHealth(OBSTACLE_TOTAL_HEALTH);
  }

  // Destructor.
  ~Obstacle2D() = default;

  // Constructors with parameters.
  Obstacle2D(Point2D const & leftBottom, Point2D const & rightTop, float totalHealth = OBSTACLE_TOTAL_HEALTH)
    :LifeGameEntity2D(leftBottom, rightTop, totalHealth)
  {
    FillBoxMatrix(leftBottom, rightTop, totalHealth);
  }

  // copy constructor
  Obstacle2D(Obstacle2D const & obj)
  {
    m_boxes = obj.GetBoxMatrix();
    SetHealth(obj.GetHealth());
  }

  // assignment operator
  Obstacle2D & operator = (Obstacle2D const & obj)
  {
    if (this == &obj) return *this;
    m_boxes = obj.GetBoxMatrix();
    SetHealth(obj.GetHealth());
    return *this;
  }


  // for Factory
  inline EntitiesTypes GetEntityType() override { return EntitiesTypes::ObstacleType; }
  std::unique_ptr<GameEntity2D> Create() override
  {
    return std::unique_ptr<GameEntity2D>(new Obstacle2D());
  }


  // Getters
  inline BoxMatrix const & GetBoxMatrix() const          { return m_boxes; }
  inline BoxMatrix & GetBoxMatrix()                      { return m_boxes; }
  inline size_t const GetCountOfRows() const             { return m_boxes.size(); }
  inline size_t const GetCountOfColumn() const           { return m_boxes[0].size(); }


  // Capabilities
  bool CheckIntersection(Bullet2D const & bul)
  {
    if (! (bul.GetBox() && this->GetBox()) )
      return false;

    for (size_t i = 0; i < m_boxes.size(); ++i)
    {
      for(size_t j = 0; j < m_boxes[i].size(); ++j)
      {
        if(m_boxes[i][j] != nullptr)
        {
          if(m_boxes[i][j]->GetBox() && bul.GetBox())
          {
            this->SetHealth(this->GetHealth() - bul.GetHealth());

            if (m_boxes[i][j]->GetHealth() <= bul.GetHealth())
            {
              delete m_boxes[i][j];
              m_boxes[i][j] = nullptr;
            }
            else
              m_boxes[i][j]->SetHealth(m_boxes[i][j]->GetHealth() - bul.GetHealth());

            return true;
          }
        }
      }
    }
    return false;
  }


  // Redefinition
  friend std::ostream & operator << (std::ostream & os, Obstacle2D & obj)
  {
    os << "OBSTACLE{"
       << obj.GetBox().leftBottom()
       << ", " << obj.GetBox().rightTop()
       << ", " << obj.GetHealth()
       << "}";
    return os;
  }

private:
  void FillBoxMatrix(Point2D const & ld, Point2D const & rt, float totalHealth)
  {
    float countRow = OBSTACLE_COUNT_VERTICAL_PART, countColumn = OBSTACLE_COUNT_HORIZONTAL_PART;
    float partWidth = (rt.x() - ld.x()) / countColumn, partHeight = (rt.y() - ld.y()) / countRow;
    float healthOfPart = totalHealth / (countRow * countColumn);

    m_boxes.reserve(countRow);
    for (size_t i = 0; i < countRow; ++i)
    {
      BoxVector tempBoxVect;
      tempBoxVect.reserve(countColumn);
      for(size_t j = 0; j < countColumn; ++j)
      {
        if (ObstacleView[i][j])
        {
          tempBoxVect.push_back
          (
           new LifeGameEntity2D{
              Box2D
              {
                Point2D
                {
                  ld.x() + j * partWidth,
                  ld.y() + i * partHeight
                },
                Point2D
                {
                  ld.x() + ( j + 1 ) * partWidth + 1,
                  ld.y() + ( i + 1 ) * partHeight + 1
                }
              },
              healthOfPart
            }
          );
        }
        else
        {
          totalHealth -= healthOfPart;
          tempBoxVect.push_back(nullptr);
        }
      }
      m_boxes.push_back(tempBoxVect);
    }
  }

  BoxMatrix m_boxes;  // matrix of LifeGameEntityes
  std::vector<std::vector<bool>> ObstacleView =  // pattern for generate obstacle 4x5
  {
    std::vector<bool>{1, 0, 0, 0, 1},
    std::vector<bool>{1, 1, 0, 1, 1},
    std::vector<bool>{1, 1, 1, 1, 1},
    std::vector<bool>{0, 1, 1, 1, 0}
  };
};
