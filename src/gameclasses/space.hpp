#pragma once

#include <thread>
#include <chrono>
#include <ctime>

using ChronoClock = std::chrono::time_point<std::chrono::system_clock>;

#include "ship.hpp"
#include "gun.hpp"
#include "alienmanager.hpp"
#include "bulletmanager.hpp"
#include "obstaclemanager.hpp"

class Space2D final : public GameEntity2D
{
public:
  // Destructor.
  ~Space2D() = default;

  // Constructors with parameters.
  Space2D(Point2D const & leftBottom, Point2D const & rightTop)
    :GameEntity2D(leftBottom, rightTop)
  {
    float leftBottomX = rightTop.x() / 2 - GUN_WIDTH / 2,
        leftBottomY = GAME_PADDING_BOTTOM,
        rightTopX = leftBottomX + GUN_WIDTH,
        rightTopY = leftBottomY + GUN_HEIGHT;
    m_gun = new Gun2D({leftBottomX, leftBottomY}, {rightTopX, rightTopY}, GUN_HEALTH_START, GUN_SPEED_SHOOT_START, GUN_LIVES_START);

    start = std::chrono::system_clock::now();
    m_ship = nullptr;

    m_alienManager = new Alien2DManager(5, ALIEN_COUNT / 5);
    m_bulletManager = new Bullet2DManager();
    m_obstacleManager = new Obstacle2DManager(OBSTACLE_COUNT);
  }

  // Getters
  Ship2D * GetShip() { return m_ship; }
  Gun2D & GetGun() { return *m_gun; }
  Obstacle2DManager & GetObstacleManager() { return *m_obstacleManager; }
  AlienMatrix const & GetAlienMatrix() const { return m_alienManager->GetAlienMatrix(); }
  ObstacleVector const & GetObstacleVector() const {return m_obstacleManager->GetObstacleVector(); }
  BulletList const & GetBulletFromGun() const {return m_bulletManager->GetBulletsFromGunList(); }
  BulletList const & GetBulletFromAlien() const {return m_bulletManager->GetBulletsFromAliensList(); }

  // Capabilities
  void SetGunPozition(float const x, float const y)
  {
    float leftBottomX = x - GUN_WIDTH / 2,
        leftBottomY = y - GUN_HEIGHT / 2,
        rightTopX = leftBottomX + GUN_WIDTH,
        rightTopY = leftBottomY + GUN_HEIGHT;
    m_gun->SetBox({{leftBottomX, leftBottomY},{rightTopX, rightTopY}});
  }

  void BulletsMove(float const & top)
  {
    m_bulletManager->BulletsMove(top);
  }

  void GunShoot()  // if add manager this code can be replaced, because later added keypress
  {
    Point2D start = m_gun->GetBox().GetCenter();
    start.SetY(m_gun->GetBox().top());
    Bullet2D bullet(
          Point2D {start.x() - BULLET_WIDTH / 2, start.y() - BULLET_HEIGHT / 2},
          Point2D {start.x() + BULLET_WIDTH / 2, start.y() + BULLET_HEIGHT / 2},
          BULLET_DAMAGE_START,
          BULLET_SPEED_START
          );
    bullet.SetUpdateHandler( [&](GameEntity2D const & ge){ logger << "the bullet from the gun hit in " << ge << std::endl; }  );
    m_bulletManager->NewBullet(bullet, GunType);
  }

  void AlienShoot()
  {
    Alien2D * alien = m_alienManager->SelectShooter(m_gun->GetBox());
    if (alien != nullptr)
    {
      Point2D start = alien->GetBox().GetCenter();
      start.SetY(alien->GetBox().bottom());
      Bullet2D bullet(
            Point2D {start.x() - BULLET_WIDTH / 2, start.y() - BULLET_HEIGHT / 2},
            Point2D {start.x() + BULLET_WIDTH / 2, start.y() + BULLET_HEIGHT / 2},
            BULLET_DAMAGE_START,
            BULLET_SPEED_START
            );
      bullet.SetUpdateHandler( [&](GameEntity2D const & ge){ logger << "the bullet from the aliens hit in " << ge << std::endl; }  );
      m_bulletManager->NewBullet(bullet, AlienType);
    }
  }

  void AliensMove()
  {
    m_alienManager->AliensMove();
  }

  void CheckAllIntersections()
  {
    // check count of bullets in bulletManager
    BulletList & bulletFromGun = m_bulletManager->GetBulletsFromGunList();
    BulletList & bulletFromAlien = m_bulletManager->GetBulletsFromAliensList();
    if (m_obstacleManager->GetCountOObstacle() != 0)
    {
      if (m_alienManager->GetBox().bottom() <= m_obstacleManager->GetObstacleVector()[0]->GetBox().top() - 20)
      {
        m_obstacleManager->clear();
      }
    }
    if (m_alienManager->GetBox().bottom() <= GAME_PADDING_BOTTOM)
    {
      logger << "ALIEN IN BOTOOM POZITION" << std::endl << *m_gun << std::endl;
      m_gun->SetLives(0);      
      return;
    }

    // iterator for delete
    std::list<std::list<Bullet2D>::iterator> itList;
    std::list<std::list<Bullet2D>::iterator> itList2;

    for(auto it = bulletFromGun.begin(); it != bulletFromGun.end(); ++it)
    {
      static int rate = 0;
      if (m_alienManager->CheckIntersection(*it, &rate))
      {
        itList.push_back(it);
        m_gun->SetRate(m_gun->GetRate() + rate);
      }
      else if (m_obstacleManager->CheckIntersection(*it))
      {
        itList.push_back(it);
      }
      else
      {
        for (auto it2 = bulletFromAlien.begin(); it2 != bulletFromAlien.end(); ++it2)
        {
          if((*it).GetBox() && it2->GetBox())
          {
            itList.push_back(it);
            itList2.push_back(it2);
          }
        }
      }
    }

    // erase itList
    for(auto it = itList.begin(); it != itList.end(); ++it)
    {
      bulletFromGun.erase(*it);
    }
    itList.clear();

    for(auto it = itList2.begin(); it != itList2.end(); ++it)
    {
      bulletFromAlien.erase(*it);
    }
    itList2.clear();

    for(auto it = bulletFromAlien.begin(); it != bulletFromAlien.end() && m_gun->GetLives() > 0; ++it)
    {
      if (m_obstacleManager->CheckIntersection(*it))
        itList.push_back(it);
      else if(m_gun->CheckIntersection(*it))
        itList.push_back(it);
      else if (m_ship != nullptr)
        if(m_ship->CheckIntersection(*it))
          itList.push_back(it);
    }

    // erase itList
    for(auto it = itList.begin(); it != itList.end(); ++it)
    {
      bulletFromAlien.erase(*it);
    }
    itList.clear();

    // intersect gun with aliens
    if (m_gun->GetLives() <= 0) return;
    if (m_alienManager->CheckIntersection(m_gun))
    {
      m_alienManager->log();
    }
  }

  unsigned int CheckGameState()
  {
    if (m_gun->GetLives() <= 0) return 2;
    if (m_alienManager->GetLiveAliensCount() <= 0) return 1;     // all aliens defeated - level passed (increased)

    return 0; // game continued
  }

  void NewLvlPrepare(int const lvl)
  {
    delete m_alienManager;
    m_alienManager = nullptr;
    delete m_bulletManager;
    m_bulletManager = nullptr;

    m_alienManager = new Alien2DManager(5, ALIEN_COUNT / 5);
    m_bulletManager = new Bullet2DManager();
    if (GUN_LIVES_INC_EVERY_LEVEL && m_gun->GetLives() < 10) m_gun->SetLives(m_gun->GetLives() + 1);
    if (OBSTACLE_REDRAW_EVERY_LEVEL)
    {
      delete m_obstacleManager;
      m_obstacleManager = new Obstacle2DManager(OBSTACLE_COUNT);
    }

    start = std::chrono::system_clock::now();
  }

  void GameStep(int frame)
  {
    /*std::thread waitingAlienThread
    {
      [this]()
      {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        AlienShoot();
      }
    };
    std::thread waitingGunThread
    {
      [this]()
      {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        GUN_CAN_SHOOT = true;
      }
    };
    waitingAlienThread.join();
    waitingGunThread.join();*/

    // ship activity
    if (m_ship == nullptr)
    {
      /*
      typedef std::chrono::high_resolution_clock Time;
      typedef std::chrono::seconds ms;
      typedef std::chrono::duration<float> fsec;
      auto t0 = Time::now();
      auto t1 = Time::now();
      fsec fs = t1 - t0;
      ms d = std::chrono::duration_cast<ms>(fs);
      std::cout << fs.count() << "s\n";
      std::cout << d.count() << "ms\n";
      */

      //std::cout << std::chrono::duration<float>(std::chrono::system_clock::now() - start).count() << std::endl;
      //std::cout << std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - start).count() << std::endl;

      if (std::chrono::duration<float>(std::chrono::system_clock::now() - start).count() >= 5)
      {
        m_ship = new Ship2D(Point2D{0, this->GetBox().top() - SHIP_HEIGHT}, Point2D{SHIP_WIDTH, this->GetBox().top()});
      }
    }

    // gun shoot delay
    //if (!(frame % GUN_SHOOT_SPEED))
      GUN_CAN_SHOOT = true;

    // Bullets activity
    BulletsMove(this->GetBox().GetHeight());
    m_ship->MoveShip();

    // alien activity
    if(!(frame % ALIEN_SHOOT_SPEED))                // ALIEN SHOOT delay
      AlienShoot();
    static int int_timer;
    if(int_timer)
      int_timer--;
    else
    {
      AliensMove();
      int_timer = 30;
    }

    // check intersections
    CheckAllIntersections();
  }

  void clear()
  {
    m_alienManager->clear();
    m_obstacleManager->clear();
    m_bulletManager->clear();
  }

private:
  ChronoClock start = std::chrono::system_clock::now(); // start game time
  Ship2D * m_ship = nullptr;                            // one ship
  Gun2D * m_gun = nullptr;                              // one gun
  Alien2DManager * m_alienManager = nullptr;            // one alien manager
  Obstacle2DManager * m_obstacleManager = nullptr;      // one obstacle manager
  Bullet2DManager * m_bulletManager = nullptr;          // one bullet manager
};
