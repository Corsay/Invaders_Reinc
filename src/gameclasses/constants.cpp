#include "logger.hpp"
#include "constants.hpp"

std::string onlyFile(std::string longName)
{
  auto it = longName.find_last_of('\\');
  return longName.erase(0, it + 1);
}
SimpleLogger & logger = SimpleLogger::Instance();

// Game parameters management
// (need to send it as param to space2d)
// ALIEN
size_t ALIEN_COUNT       = 55;
size_t  ALIEN_SHOOT_SPEED = 100;   // one shoot every 100 frames
// GUN
size_t GUN_LIVES_START           = 3;
bool   GUN_LIVES_INC_EVERY_LEVEL = true;
size_t  GUN_SHOOT_SPEED_DEFAULT   = 55;
size_t  GUN_SHOOT_SPEED           = 55;   // one shoot every 55 frames
bool   GUN_CAN_SHOOT             = true;
// OBSTACLE
size_t OBSTACLE_COUNT              = 4;
bool   OBSTACLE_REDRAW_EVERY_LEVEL = false;
// SHIP
bool   SHIP_STARTED = false;
// GAME SPACE
float  GAME_PADDING_LEFT = 15;
float  GAME_PADDING_RIGHT = 15;
float  GAME_PADDING_TOP = 30;
float  GAME_PADDING_BOTTOM = 50;
// GAME
bool   GAME_STARTED = false;
// BONUSES
bool   BONUS_GOD = false;

// const (setted value)
// DEFAULT
float DEFAULT_HEALTH = 50.0f;
float DEFAULT_SPEED = 0.5f;
// ALIEN
float ALIEN_HEALTH_START      = 50.0f;
float ALIEN_SPEED_SHOOT_START = 1.2f;
float ALIEN_WIDTH             = 45.0f;
float ALIEN_HEIGHT            = 35.0f;
float ALIEN_BOX_LEFT            = 100.0f;
float ALIEN_BOX_TOP             = 400.0f;
float ALIEN_HORIZONTAL_DISTANCE = 12.0f;
float ALIEN_VERTICAL_DISTANCE   = 5.0f;
float ALIENT_HORIZONTAL_STEP    = 10.0f;
float ALIENT_VERTICAL_STEP      = 20.0f;
// GUN
float GUN_HEALTH_START      = 50.0f;
float GUN_SPEED_SHOOT_START = 2.0f;
float GUN_START_X           = 100.0f;
float GUN_START_Y           = 100.0f;
float GUN_WIDTH             = 70.0f;
float GUN_HEIGHT            = 50.0f;
// OBSTACLE
float OBSTACLE_BOX_LEFT     = GAME_PADDING_LEFT + 1.0f;
float OBSTACLE_BOX_BOTTOM   = 170.0f;
float OBSTACLE_WIDTH        = 80.0f;
float OBSTACLE_HEIGHT       = 50.0f;
float OBSTACLE_TOTAL_HEALTH = 250.0f;
float OBSTACLE_DISTANCE     = 20.0f;
int OBSTACLE_COUNT_VERTICAL_PART   = 4;
int OBSTACLE_COUNT_HORIZONTAL_PART = 5;
// BULLET
float BULLET_DAMAGE_START = 50.0f;
float BULLET_SPEED_START  = 5.0f;
float BULLET_WIDTH        = 10.0f;
float BULLET_HEIGHT       = 25.0f;
// SHIP
float SHIP_HEALTH_START   = 50.0f;
float SHIP_SPEED_START    = 5.0f;
float SHIP_WIDTH        = 60.0f;
float SHIP_HEIGHT       = 30.0f;
// GAME
float LAST_WINDOW_VERTICAL_SIZE = 600.0f;
float LAST_WINDOW_HORIZONTAL_SIZE = 800.0f;

void ChangeConstants(float w, float h)
{
  float wk = w / LAST_WINDOW_HORIZONTAL_SIZE;
  float hk = h / LAST_WINDOW_VERTICAL_SIZE;

  GAME_PADDING_LEFT *= wk;
  GAME_PADDING_RIGHT *= wk;
  GAME_PADDING_TOP *= hk;
  GAME_PADDING_BOTTOM *= hk;

  DEFAULT_SPEED *= wk;

  ALIEN_WIDTH             *= wk;
  ALIEN_HEIGHT            *= hk;
  ALIEN_BOX_LEFT            *= wk;
  ALIEN_BOX_TOP             *= hk;
  ALIEN_HORIZONTAL_DISTANCE *= wk;
  ALIEN_VERTICAL_DISTANCE   *= hk;
  ALIENT_HORIZONTAL_STEP    *= wk;
  ALIENT_VERTICAL_STEP      *= hk;

  GUN_START_X           *= wk;
  GUN_START_Y           *= hk;
  GUN_WIDTH             *= wk;
  GUN_HEIGHT            *= hk;

  OBSTACLE_BOX_LEFT     *= wk;
  OBSTACLE_BOX_BOTTOM   *= hk;
  OBSTACLE_WIDTH        *= wk;
  OBSTACLE_HEIGHT       *= hk;
  OBSTACLE_DISTANCE     *= wk;

  BULLET_WIDTH        *= wk;
  BULLET_HEIGHT       *= hk;

  SHIP_WIDTH        *= wk;
  SHIP_HEIGHT       *= hk;

  LAST_WINDOW_VERTICAL_SIZE = h;
  LAST_WINDOW_HORIZONTAL_SIZE = w;
}
