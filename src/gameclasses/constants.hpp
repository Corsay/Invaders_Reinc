#pragma once
#include "logger.hpp"
#include <vector>
#include <QString>
extern SimpleLogger & logger;

std::string onlyFile(std::string);
void ChangeConstants(float w, float h);

using namespace std;

#define WHERE "File: " << onlyFile( __FILE__ ) << " Function: " << __FUNCTION__ << " Line:" << __LINE__

// Game parameters management
// ALIEN
extern size_t ALIEN_COUNT;
const float  ALIEN_SHOOT_SPEED_DEFAULT = 1.5;
extern float  ALIEN_SHOOT_SPEED;
// GUN
extern size_t GUN_LIVES_START;
extern bool   GUN_LIVES_INC_EVERY_LEVEL;
const float   GUN_SHOOT_SPEED_DEFAULT = 0.8;
extern float  GUN_SHOOT_SPEED;
extern bool   GUN_CAN_SHOOT;
// OBSTACLE
extern size_t OBSTACLE_COUNT;
extern bool   OBSTACLE_REDRAW_EVERY_LEVEL;
// SHIP
extern bool   SHIP_STARTED;
// GAME SPACE
extern float  GAME_PADDING_LEFT;
extern float  GAME_PADDING_RIGHT;
extern float  GAME_PADDING_TOP;
extern float  GAME_PADDING_BOTTOM;
// GAME
extern bool   GAME_STARTED;
// BONUSES
// +
extern bool   BONUS_X2;
extern bool   BONUS_ADD_LIVE;
extern bool   BONUS_GUN_FAST_SHOOT;
extern float  BONUS_SPEED_GUN_FAST_SHOOT;
extern bool   BONUS_LAZER;
extern float  BONUS_SPEED_LAZER_SHOOT;
extern bool   BONUS_HEAL_OBSTACLES;
extern bool   BONUS_HIT_ALL_ALIENS;
extern bool   BONUS_GOD;
// -
extern bool   BONUS_ANTI_X2;
extern bool   BONUS_ALIEN_FAST_SHOOT;
extern float  BONUS_SPEED_ALIEN_FAST_SHOOT;
extern bool   BONUS_HIT_OBSTACLES;

extern std::vector<std::vector <QString>> recordsArray;
extern int GetMinimalRecord();

// const (setted value)
// DEFAULT
extern float DEFAULT_HEALTH; // median alien = 50,  gun = 50,  bullet(damage health) = 50, box_part = 50
extern float DEFAULT_SPEED;   // (much of aliens) alien = 0.5, gun = 2.0, bullet(fly speed) = 5.0
// ALIEN
extern float ALIEN_HEALTH_START;
extern float ALIEN_SPEED_SHOOT_START;
extern float ALIEN_WIDTH;
extern float ALIEN_HEIGHT;
extern float ALIEN_BOX_LEFT;  // left border of aliensMatrix
extern float ALIEN_BOX_TOP;   // top border
extern float ALIEN_HORIZONTAL_DISTANCE;
extern float ALIEN_VERTICAL_DISTANCE;
extern float ALIENT_HORIZONTAL_STEP;
extern float ALIENT_VERTICAL_STEP;
// GUN
extern float GUN_HEALTH_START;
extern float GUN_SPEED_SHOOT_START;
extern float GUN_START_X;
extern float GUN_START_Y;
extern float GUN_WIDTH;
extern float GUN_HEIGHT;
// OBSTACLE
extern float OBSTACLE_BOX_LEFT;
extern float OBSTACLE_BOX_BOTTOM;
extern float OBSTACLE_WIDTH;
extern float OBSTACLE_HEIGHT;
extern float OBSTACLE_TOTAL_HEALTH;
extern float OBSTACLE_DISTANCE;
extern int OBSTACLE_COUNT_VERTICAL_PART;
extern int OBSTACLE_COUNT_HORIZONTAL_PART;
// BULLET
extern float BULLET_DAMAGE_START;
extern float BULLET_SPEED_START;
extern float BULLET_WIDTH;
extern float BULLET_HEIGHT;
// SHIP
extern float SHIP_HEALTH_START;
extern float SHIP_SPEED_START;
extern float SHIP_WIDTH;
extern float SHIP_HEIGHT;
// GAME
extern float LAST_WINDOW_VERTICAL_SIZE;
extern float LAST_WINDOW_HORIZONTAL_SIZE;
const int BOOM_TIMER = 15;
extern int MAX_COUNT_RECORDS;
