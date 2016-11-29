#pragma once

#include "gameentity.hpp"
#include "gun.hpp"
#include "alienmanager.hpp"
#include "bulletmanager.hpp"
#include "obstaclemanager.hpp"

class Space2D final : public GameEntity2D
{
public:
  // Allow default constructor.
  Space2D() = default;

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
    m_gun = Gun2D({leftBottomX, leftBottomY}, {rightTopX, rightTopY}, GUN_HEALTH_START, GUN_SPEED_SHOOT_START, GUN_LIVES_START);

    m_alienManager = new Alien2DManager(5, ALIEN_COUNT / 5);
    m_bulletManager = new Bullet2DManager();
    m_obstacleManager.CreateObstacleVector(OBSTACLE_COUNT);
  }

  // Getters
  Gun2D & GetGun() { return m_gun; }
  Obstacle2DManager & GetObstacleManager() { return m_obstacleManager; }
  AlienMatrix const & GetAlienMatrix() const { return m_alienManager->GetAlienMatrix(); }
  ObstacleVector const & GetObstacleVector() const {return m_obstacleManager.GetObstacleVector(); }
  BulletList const & GetBulletFromGun() const {return m_bulletManager->GetBulletsFromGunList(); }
  BulletList const & GetBulletFromAlien() const {return m_bulletManager->GetBulletsFromAliensList(); }

  // Capabilities
  void SetGunPozition(float const x, float const y)
  {
    float leftBottomX = x - GUN_WIDTH / 2,
      leftBottomY = y - GUN_HEIGHT / 2,
      rightTopX = leftBottomX + GUN_WIDTH,
      rightTopY = leftBottomY + GUN_HEIGHT;
    m_gun.SetBox({{leftBottomX, leftBottomY},{rightTopX, rightTopY}});
  }

  void BulletsMove(float const & top)
  {
    m_bulletManager->BulletsMove(top);
  }

  void GunShoot()  // if add manager this code can be replaced, because later added keypress
  {
    Point2D start = m_gun.GetBox().GetCenter();
    start.SetY(m_gun.GetBox().top());
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
    Alien2D alien = Alien2D({0, 0}, {0, 0}); //m_alienManager->SelectShooter(m_gun.GetBox());
    Point2D start = alien.GetBox().GetCenter();
    start.SetY(alien.GetBox().bottom());
    Bullet2D bullet(
      Point2D {start.x() - BULLET_WIDTH / 2, start.y() - BULLET_HEIGHT / 2},
      Point2D {start.x() + BULLET_WIDTH / 2, start.y() + BULLET_HEIGHT / 2},
      BULLET_DAMAGE_START,
      BULLET_SPEED_START
    );
    bullet.SetUpdateHandler( [&](GameEntity2D const & ge){ logger << "the bullet from the aliens hit in " << ge << std::endl; }  );
    m_bulletManager->NewBullet(bullet, AlienType);
  }

  void AliensMove()
  {
    m_alienManager->AliensMove();
  }

  void CheckAllIntersections()
  {
    // check count of bullets in bulletManager
    BulletList & BulletFromGun = m_bulletManager->GetBulletsFromGunList();
    BulletList & BulletFromAlien = m_bulletManager->GetBulletsFromAliensList();

    // iterator for delete
    std::list<std::list<Bullet2D>::iterator> itList;

    for(auto it = BulletFromGun.begin(); it != BulletFromGun.end(); ++it)
    {
      static int rate = 0;
      if (m_alienManager->CheckIntersection(*it, &rate))
      {
        itList.push_back(it);
        m_gun.SetRate(m_gun.GetRate() + rate);
      }
      else if (m_obstacleManager.CheckIntersection(*it))
        itList.push_back(it);
    }

    // erase itList
    for(auto it = itList.begin(); it != itList.end(); ++it)
    {
      BulletFromGun.erase(*it);
    }
    itList.clear();

    for(auto it = BulletFromAlien.begin(); it != BulletFromAlien.end(); ++it)
    {
      if (m_obstacleManager.CheckIntersection(*it))
        itList.push_back(it);
      else if(m_gun.CheckIntersection(*it))
        itList.push_back(it);
    }

    // erase itList
    for(auto it = itList.begin(); it != itList.end(); ++it)
    {
      BulletFromAlien.erase(*it);
    }
    itList.clear();
  }

  unsigned int CheckGameState()
  {
    if (m_alienManager->GetLiveAliensCount() <= 0) return 1;     // all aliens defeated - level passed (increased)
    if (m_gun.GetLives() <= 0) return 2;

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
    if (GUN_LIVES_INC_EVERY_LEVEL && m_gun.GetLives() < 10) m_gun.SetLives(m_gun.GetLives() + 1);
    if (OBSTACLE_REDRAW_EVERY_LEVEL) m_obstacleManager.CreateObstacleVector(OBSTACLE_COUNT);
  }

private:
  Gun2D m_gun;                         // one gun
  Alien2DManager * m_alienManager;     // one alien manager
  Obstacle2DManager m_obstacleManager; // one obstacle manager
  Bullet2DManager * m_bulletManager;   // one bullet manager
};
