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
  {}

  Space2D(Point2D const & leftBottom, Point2D const & rightTop, int gunLives, int countOfAliens, int countOfObstacles)
    :GameEntity2D(leftBottom, rightTop)
  {
    float leftBottomX = rightTop.x() / 2 - GUN_WIDTH / 2,
          leftBottomY = GAME_PADDING_BOTTOM,
          rightTopX = leftBottomX + GUN_WIDTH,
          rightTopY = leftBottomY + GUN_HEIGHT;
    m_gun = Gun2D({leftBottomX, leftBottomY}, {rightTopX, rightTopY}, GUN_HEALTH_START, GUN_SPEED_SHOOT_START, gunLives);

    // доделать отправку в alien2Dmanager размеры матрицы пришельцев рассчитав их из общего количества пришельцев countOfAliens
    // 6 * 13 = 78
    m_alienManager = Alien2DManager(6, 13);
    // почему то не работает copy constructor
    //m_obstacleManager = Obstacle2DManager(countOfObstacles);
    m_obstacleManager.CreateObstacleVector(countOfObstacles);
    m_bulletManager = Bullet2DManager();
  }

  // Getters
  Gun2D const & GetGun() { return m_gun; }
  AlienMatrix const & GetAlienMatrix() const { return m_alienManager.GetAlienMatrix(); }
  ObstacleVector const & GetObstacleVector() const {return m_obstacleManager.GetObstacleVector(); }
  BulletList const & GetBulletFromGun() const {return m_bulletManager.GetBulletsFromGunList(); }
  BulletList const & GetBulletFromAlien() const {return m_bulletManager.GetBulletsFromAliensList(); }

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
    m_bulletManager.BulletsMove(top);
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
    bullet.SetUpdateHandler( [&](GameEntity2D const & ge){ std::cout << "the bullet from the gun hit in " << ge << std::endl; }  );
    m_bulletManager.NewBullet(bullet, GunType);
  }

  void AlienShoot()
  {
    Alien2D alien = m_alienManager.SelectShooter(m_gun.GetBox());
    Point2D start = alien.GetBox().GetCenter();
    start.SetY(alien.GetBox().top());
    Bullet2D bullet(
      Point2D {start.x() - BULLET_WIDTH / 2, start.y() - BULLET_HEIGHT / 2},
      Point2D {start.x() + BULLET_WIDTH / 2, start.y() + BULLET_HEIGHT / 2},
      BULLET_DAMAGE_START,
      BULLET_SPEED_START
    );
    bullet.SetUpdateHandler( [&](GameEntity2D const & ge){ std::cout << "the bullet from the aliens hit in " << ge << std::endl; }  );
    m_bulletManager.NewBullet(bullet, AlienType);
  }

  void CheckAllIntersections()
  {
    // check count of bullets in bulletManager
    BulletList & BulletFromGun = m_bulletManager.GetBulletsFromGunList();
    BulletList & BulletFromAlien = m_bulletManager.GetBulletsFromAliensList();

    for(auto it = BulletFromGun.begin(); it != BulletFromGun.end(); ++it)
      if( m_alienManager.CheckIntersection(*it) )
        BulletFromGun.erase(it);
      else if( m_obstacleManager.CheckIntersection(*it) )
        BulletFromGun.erase(it);

    for(auto it = BulletFromAlien.begin(); it != BulletFromAlien.end(); ++it)
      if( m_obstacleManager.CheckIntersection(*it) )
        BulletFromGun.erase(it);
      else if(m_gun.CheckIntersection(*it))
        BulletFromGun.erase(it);
  }

  unsigned int CheckGameState()
  {
    if (m_alienManager.GetLiveAliensCount() <= 0) return 1;     // all aliens defeated - level passed (increased)
    if (m_gun.GetHealth() <= 0) return 2;
    // gun dead once       - continue  (if gun_lives > 0)
    // gun dead last time  - game over (if gun_lives <= 0)

    return 0; // game continued
  }

  void GameStep()
  {
    CheckAllIntersections();
    //еще какие-то действия
  }

  void NewLvlPrepare(size_t const lvl)
  {
    throw std::runtime_error("Not released Space2D::NewLvlPrepare.");
    // configure space class fields for new lvl
  }

private:
  Gun2D m_gun;                         // one gun
  Alien2DManager m_alienManager;       // one alien manager
  Obstacle2DManager m_obstacleManager; // one obstacle manager
  Bullet2DManager m_bulletManager;     // one bullet manager
};
