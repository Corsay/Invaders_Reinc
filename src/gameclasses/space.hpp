#pragma once

#include <chrono>
#include <ctime>

using ChronoClock = std::chrono::time_point<std::chrono::system_clock>;

#include "ship.hpp"
#include "gun.hpp"
#include "alienmanager.hpp"
#include "bulletmanager.hpp"
#include "obstaclemanager.hpp"

#include <QSoundEffect>

const int BOOM_SIZE = 25;

struct BoomElement
{
  Point2D m_place;
  int m_timer;
  BoomElement(Point2D const & p)
  {
    m_place = p;
    m_timer = BOOM_TIMER;
  }
  int GetWidth()
  {
    return int(BOOM_SIZE + BOOM_SIZE * sin(m_timer * M_PI / BOOM_TIMER));
  }
  int GetHeigth()
  {
    return int(BOOM_SIZE + BOOM_SIZE * sin(m_timer * M_PI / BOOM_TIMER));
  }
};

typedef std::list<BoomElement> BoomList;

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

    timeAlienMove = std::chrono::system_clock::now();
    timeAlienShoot = std::chrono::system_clock::now();
    timeGunShoot = std::chrono::system_clock::now();
    timeShipStart = std::chrono::system_clock::now();
    ftimeAlienMove = 0.0f;
    ftimeAlienShoot = 0.0f;
    ftimeGunShoot = 0.0f;
    ftimeShipStart = 0.0f;

    ALIEN_MOVE_SPEED_TIMER = ALIEN_MOVE_SPEED_TIMER_DEFAULT;

    m_ship = nullptr;
    if( (LAST_WINDOW_HORIZONTAL_SIZE - (GAME_PADDING_LEFT + GAME_PADDING_RIGHT) - 100)
        / (ALIEN_WIDTH + ALIEN_HORIZONTAL_DISTANCE) < ALIEN_COUNT / 5)
    {
      ALIEN_HORIZONTAL_DISTANCE = 0;
      if( (LAST_WINDOW_HORIZONTAL_SIZE - (GAME_PADDING_LEFT + GAME_PADDING_RIGHT) - 100) / ALIEN_WIDTH  < ALIEN_COUNT / 5)
      {
          ALIEN_WIDTH = (LAST_WINDOW_HORIZONTAL_SIZE - (GAME_PADDING_LEFT + GAME_PADDING_RIGHT) - 100) / (ALIEN_COUNT / 5);
      }
    }
    m_alienManager = new Alien2DManager(5, ALIEN_COUNT / 5);
    m_bulletManager = new Bullet2DManager();
    m_obstacleManager = new Obstacle2DManager(OBSTACLE_COUNT);
    srand(time(0));
    OffBonuses();
    InitSound();
  }

  void InitSound()
  {
    m_soundGunShoot = new QSoundEffect();
    m_soundGunShoot->setSource(QUrl::fromLocalFile("data/audio/shoot_gun.wav"));

    m_soundAlienShoot = new QSoundEffect();
    m_soundAlienShoot->setSource(QUrl::fromLocalFile("data/audio/shoot_alien.wav"));

    m_soundBoom = new QSoundEffect();
    m_soundBoom->setSource(QUrl::fromLocalFile("data/audio/boom.wav"));

    SetVolume();
  }

  void SetVolume()
  {
    m_soundGunShoot->setVolume(SOUND_GAME_VOLUME);
    m_soundAlienShoot->setVolume(SOUND_GAME_VOLUME);
    m_soundBoom->setVolume(SOUND_GAME_VOLUME);
  }

  // Getters
  Ship2D * GetShip() { return m_ship; }
  Gun2D & GetGun() { return *m_gun; }
  Obstacle2DManager & GetObstacleManager() { return *m_obstacleManager; }
  AlienMatrix const & GetAlienMatrix() const { return m_alienManager->GetAlienMatrix(); }
  ObstacleVector const & GetObstacleVector() const {return m_obstacleManager->GetObstacleVector(); }
  BulletList const & GetBulletFromGun() const {return m_bulletManager->GetBulletsFromGunList(); }
  BulletList const & GetBulletFromAlien() const {return m_bulletManager->GetBulletsFromAliensList(); }
  BoomList & GetBoomList() { return m_boomList; }


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
    if (SOUND_GAME_ON) m_soundGunShoot->play();

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
    if (SOUND_GAME_ON) m_soundAlienShoot->play();

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

        if (BONUS_X2) rate *= 2;
        if (BONUS_ANTI_X2) rate /= 2;
        m_gun->SetRate(m_gun->GetRate() + rate);

        if (SOUND_GAME_ON) m_soundBoom->play();
        m_boomList.push_back( BoomElement (Point2D { it->GetBox().GetCenter().x(), it->GetBox().top()} ) );
      }
      else if (m_obstacleManager->CheckIntersection(*it))
      {
        itList.push_back(it);

        if (SOUND_GAME_ON) m_soundBoom->play();
        m_boomList.push_back( BoomElement (Point2D { it->GetBox().GetCenter().x(), it->GetBox().top()} ) );
      }
      else if (m_ship != nullptr && m_ship->CheckIntersection(*it))
      {
        delete m_ship;
        m_ship = nullptr;
        itList.push_back(it);

        // work with bonuses
        if (BONUS_ADD_LIVE)
        {
          m_gun->SetLives(m_gun->GetLives() + 1);
        }
        if (BONUS_HEAL_OBSTACLES)
        {
          m_obstacleManager->clear();
          delete m_obstacleManager;
          m_obstacleManager = new Obstacle2DManager(OBSTACLE_COUNT);
        }
        if (BONUS_HIT_ALL_ALIENS)
        {
          m_alienManager->clear();
          return;
        }

        if (SOUND_GAME_ON) m_soundBoom->play();
        m_boomList.push_back( BoomElement (Point2D { it->GetBox().GetCenter().x(), it->GetBox().top()} ) );
      }
      else
      {
        for (auto it2 = bulletFromAlien.begin(); it2 != bulletFromAlien.end(); ++it2)
        {
          if((*it).GetBox() && it2->GetBox())
          {
            itList.push_back(it);
            itList2.push_back(it2);

            if (SOUND_GAME_ON) m_soundBoom->play();
            m_boomList.push_back( BoomElement (Point2D { it->GetBox().GetCenter().x(), it->GetBox().top()} ) );
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
      {
        itList.push_back(it);

        if (SOUND_GAME_ON) m_soundBoom->play();
        m_boomList.push_back( BoomElement (Point2D { it->GetBox().GetCenter().x(), it->GetBox().bottom()} ) );
      }
      else if(m_gun->CheckIntersection(*it))
      {
        itList.push_back(it);

        if (SOUND_GAME_ON) m_soundBoom->play();
        m_boomList.push_back( BoomElement (Point2D { it->GetBox().GetCenter().x(), it->GetBox().bottom()} ) );
      }
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

  void OffBonuses()
  {
    // +
    BONUS_X2             = false;
    BONUS_ADD_LIVE       = false;
    BONUS_GUN_FAST_SHOOT = false;
    BONUS_LAZER          = false;
    BONUS_HEAL_OBSTACLES = false;
    BONUS_HIT_ALL_ALIENS = false;
    BONUS_GOD            = false;
    // -
    BONUS_ANTI_X2          = false;
    BONUS_ALIEN_FAST_SHOOT = false;
    BONUS_HIT_OBSTACLES    = false;

    // and set start level param
    GUN_SHOOT_SPEED = GUN_SHOOT_SPEED_DEFAULT;
    ALIEN_SHOOT_SPEED = ALIEN_SHOOT_SPEED_DEFAULT;
    SHIP_STARTED = false;
  }

  void NewLvlPrepare(int const lvl)
  {
    OffBonuses();

    ALIEN_MOVE_SPEED_TIMER = ALIEN_MOVE_SPEED_TIMER_DEFAULT - (lvl * ALIEN_MOVE_SPEED_TIMER_INC);
    if (ALIEN_MOVE_SPEED_TIMER < ALIEN_MOVE_SPEED_TIMER_MIN) ALIEN_MOVE_SPEED_TIMER = ALIEN_MOVE_SPEED_TIMER_MIN;

    delete m_alienManager;
    m_alienManager = nullptr;
    delete m_bulletManager;
    m_bulletManager = nullptr;
    delete m_ship;
    m_ship = nullptr;

    m_alienManager = new Alien2DManager(5, ALIEN_COUNT / 5);
    m_bulletManager = new Bullet2DManager();
    if (GUN_LIVES_INC_EVERY_LEVEL && m_gun->GetLives() < 10) m_gun->SetLives(m_gun->GetLives() + 1);
    if (OBSTACLE_REDRAW_EVERY_LEVEL)
    {
      m_obstacleManager->clear();
      delete m_obstacleManager;
      m_obstacleManager = new Obstacle2DManager(OBSTACLE_COUNT);
    }

    timeAlienMove = std::chrono::system_clock::now();
    timeAlienShoot = std::chrono::system_clock::now();
    timeGunShoot = std::chrono::system_clock::now();
    timeShipStart = std::chrono::system_clock::now();
    ftimeAlienMove = 0.0f;
    ftimeAlienShoot = 0.0f;
    ftimeGunShoot = 0.0f;
    ftimeShipStart = 0.0f;
  }

  void GameStep()
  {
    // fix timer if used pause (if function GameStep not call more then 0.5 seconds)
    if (std::chrono::duration<float>(std::chrono::system_clock::now() - timeAlienShoot).count() >= 0.5)
    {
      timeAlienMove = std::chrono::system_clock::now();
      timeAlienShoot = std::chrono::system_clock::now();
      timeGunShoot = std::chrono::system_clock::now();
      timeShipStart = std::chrono::system_clock::now();
    }

    // time
    ftimeAlienMove += std::chrono::duration<float>(std::chrono::system_clock::now() - timeAlienMove).count();
    timeAlienMove = std::chrono::system_clock::now();
    ftimeAlienShoot += std::chrono::duration<float>(std::chrono::system_clock::now() - timeAlienShoot).count();
    timeAlienShoot = std::chrono::system_clock::now();
    ftimeGunShoot += std::chrono::duration<float>(std::chrono::system_clock::now() - timeGunShoot).count();
    timeGunShoot = std::chrono::system_clock::now();

    // ship activity
    if (m_ship == nullptr)
    {
      if (SHIP_STARTED == false)
      {
        ftimeShipStart += std::chrono::duration<float>(std::chrono::system_clock::now() - timeShipStart).count();
        timeShipStart = std::chrono::system_clock::now();

        if (ftimeShipStart >= rand() % 20 + 20)
        {
          SHIP_STARTED = true;
          srand(time(0));
          if(rand() % 2)
            m_ship = new Ship2D(Point2D{-SHIP_WIDTH, this->GetBox().top() - SHIP_HEIGHT - 5}, Point2D{0, this->GetBox().top()}, 1);
          else
            m_ship = new Ship2D(Point2D{LAST_WINDOW_HORIZONTAL_SIZE, this->GetBox().top() - SHIP_HEIGHT - 5}, Point2D{LAST_WINDOW_HORIZONTAL_SIZE + SHIP_WIDTH, this->GetBox().top() - 5}, -1);

          ftimeShipStart = 0.0f;
        }
      }
    }
    else
    {
      m_ship->MoveShip();

      if(!(m_ship->GetBox() && this->GetBox()))
      {
        m_ship->RandomNegativeBonus();

        // antibonus
        if (BONUS_HIT_OBSTACLES)
        {
          m_obstacleManager->clear();
        }

        delete m_ship;
        m_ship = nullptr;
      }
    }

    // gun shoot delay
    if (ftimeGunShoot >= GUN_SHOOT_SPEED || GUN_CAN_SHOOT)
    {
      GUN_CAN_SHOOT = true;
      ftimeGunShoot = 0.0f;
    }

    // Bullets activity
    BulletsMove(this->GetBox().GetHeight());

    // alien activity
    // alien shoot delay
    if (ftimeAlienShoot >= ALIEN_SHOOT_SPEED)
    {
      AlienShoot();
      ftimeAlienShoot = 0.0f;
    }

    if (ftimeAlienMove >= ALIEN_MOVE_SPEED_TIMER)
    {
      AliensMove();
      ftimeAlienMove = 0.0f;
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
  // sound
  QSoundEffect * m_soundGunShoot = nullptr;
  QSoundEffect * m_soundAlienShoot = nullptr;
  QSoundEffect * m_soundBoom = nullptr;

  // time
  float ftimeAlienMove = 0.0f;
  float ftimeAlienShoot = 0.0f;
  float ftimeGunShoot = 0.0f;
  float ftimeShipStart = 0.0f;
  ChronoClock timeAlienMove = std::chrono::system_clock::now();
  ChronoClock timeAlienShoot = std::chrono::system_clock::now();
  ChronoClock timeGunShoot = std::chrono::system_clock::now();
  ChronoClock timeShipStart = std::chrono::system_clock::now();
  // main
  Ship2D * m_ship = nullptr;                            // one ship
  Gun2D * m_gun = nullptr;                              // one gun
  Alien2DManager * m_alienManager = nullptr;            // one alien manager
  Obstacle2DManager * m_obstacleManager = nullptr;      // one obstacle manager
  Bullet2DManager * m_bulletManager = nullptr;          // one bullet manager
  BoomList m_boomList;
};
