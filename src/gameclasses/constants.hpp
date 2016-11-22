#pragma once
#include "logger.hpp"
extern SimpleLogger & logger;
std::string onlyFile(std::string);
#define WHERE "File: " << onlyFile( __FILE__ ) << " Function: " << __FUNCTION__ << " Line:" << __LINE__

// Game parameters management
// static (need to send it as param to space2d)
// ALIEN
static size_t ALIEN_COUNT = 55;
// GUN
static size_t GUN_LIVES_START           = 3;
static bool   GUN_LIVES_INC_EVERY_LEVEL = true;
// OBSTACLE
static size_t OBSTACLE_COUNT              = 4;
static bool   OBSTACLE_REDRAW_EVERY_LEVEL = false;
// GAME SPACE
static float  GAME_PADDING_LEFT = 15;
static float  GAME_PADDING_RIGHT = 15;
static float  GAME_PADDING_TOP = 30;
static float  GAME_PADDING_BOTTOM = 30;

// const (setted value)
// DEFAULT
const float DEFAULT_HEALTH = 50.0f; // median alien = 50,  gun = 50,  bullet(damage health) = 50, box_part = 50
const float DEFAULT_SPEED = 0.5f;   // (much of aliens) alien = 0.5, gun = 2.0, bullet(fly speed) = 5.0
// ALIEN
const float ALIEN_HEALTH_START      = 50.0f;
const float ALIEN_HEALTH_INC        = 50.0f;
const float ALIEN_SPEED_SHOOT_START = 1.2f;
const float ALIEN_SPEED_SHOOT_INC   = 0.5f;
const float AlIEN_WIDTH             = 50.0f;
const float ALIEN_HEIGHT            = 40.0f;
const float ALIEN_BOX_LEFT            = 100.0f;  // left border of aliensMatrix
const float ALIEN_BOX_TOP             = 500.0f;   // top border
const float ALIEN_HORIZONTAL_DISTANCE = 20.0f;
const float ALIEN_VERTICAL_DISTANCE   = 20.0f;
const float ALIENT_HORIZONTAL_STEP    = 15.0f;
// GUN
const float GUN_HEALTH_START      = 50.0f;
const float GUN_HEALTH_INC        = 50.0f;
const float GUN_SPEED_SHOOT_START = 2.0f;
const float GUN_SPEED_SHOOT_INC   = 0.7f;
const float GUN_LEFT_LIMIT        = 10.0f;
const float GUN_RIGHT_LIMIT       = 600.0f;
const float GUN_STEP              = 20.0f;
const float GUN_START_X           = 400.0f;
const float GUN_START_Y           = 100.0f;
const float GUN_WIDTH             = 70.0f;
const float GUN_HEIGHT            = 50.0f;
// OBSTACLE
const float OBSTACLE_BOX_LEFT     = GAME_PADDING_LEFT + 80.0f;      // +
const float OBSTACLE_BOX_RIGHT    = GAME_PADDING_LEFT + 80.0f;      // +
const float OBSTACLE_BOX_BOTTOM   = 170.0f;     // +
const float OBSTACLE_WIDTH        = 100.0f;     // +
const float OBSTACLE_HEIGHT       = 100.0f;     // +
const float OBSTACLE_PART_WIDTH   = 100.0f;
const float OBSTACLE_PART_HEIGHT  = 100.0f;
const float OBSTACLE_TOTAL_HEALTH = 250.0f;
const float OBSTACLE_DISTANCE     = 100.0f;     // +
// BULLET
const float BULLET_DAMAGE_START = 50.0f;
const float BULLET_DAMAGE_INC   = 50.0f;
const float BULLET_SPEED_START  = 5.0f;
const float BULLET_SPEED_INC    = 1.0f;
const float BULLET_WIDTH        = 10.0f;
const float BULLET_HEIGHT       = 25.0f;


