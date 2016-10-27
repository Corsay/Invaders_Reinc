#pragma once
#include "gameclasses/logger.hpp"
extern SimpleLogger & logger;
std::string onlyFile(std::string);
#define WHERE "File: " << onlyFile( __FILE__ ) << " Function: " << __FUNCTION__ << " Line:" << __LINE__

// Game parameters management
// for this time, later changed
const float DEFAULT_HEALTH = 50.0f; // median alien = 50,  gun = 50,  bullet(damage health) = 50, box_part = 50
const float DEFAULT_SPEED = 0.5f;   // (much of aliens) alien = 0.5, gun = 2.0, bullet(fly speed) = 5.0


const float ALIEN_HEALTH_START      = 50.0f;
const float ALIEN_HEALTH_INC        = 50.0f;
const float ALIEN_SPEED_SHOOT_START = 1.2f;
const float ALIEN_SPEED_SHOOT_INC   = 0.5f;
const float AlIEN_WIDTH             = 50.0f;
const float ALIEN_HEIGHT            = 40.0f;

const float ALIEN_BOX_LEFT            = 100.0f;  // left border of aliensMatrix
const float ALIEN_BOX_TOP             = 80.0f;   // top border
const float ALIEN_HORIZONTAL_DISTANCE = 20.0f;
const float ALIEN_VERTICAL_DISTANCE   = 20.0f;
const float ALIENT_HORIZONTAL_STEP    = 15.0f;


const size_t GUN_LIVES_START       = 3;
const float  GUN_HEALTH_START      = 50.0f;
const float  GUN_HEALTH_INC        = 50.0f;
const float  GUN_SPEED_SHOOT_START = 2.0f;
const float  GUN_SPEED_SHOOT_INC   = 0.7f;
const float  GUN_LEFT_LIMIT        = 10.0f;
const float  GUN_RIGHT_LIMIT       = 600.0f;
const float  GUN_STEP              = 20.0f;


const float OBSTACLE_BOX_LEFT     = 100.0f;
const float OBSTACLE_BOX_BOTTOM   = 80.0f;
const float OBSTACLE_WIDTH        = 100.0f;
const float OBSTACLE_HEIGHT       = 100.0f;
const float OBSTACLE_PART_WIDTH   = 10.0f;
const float OBSTACLE_PART_HEIGHT  = 10.0f;
const float OBSTACLE_TOTAL_HEALTH = 250.0f;


const float BULLET_DAMAGE_START = 50.0f;
const float BULLET_DAMAGE_INC   = 50.0f;
const float BULLET_SPEED_START  = 5.0f;
const float BULLET_SPEED_INC    = 1.0f;
const float BULLET_WIDTH        = 10.0f;
const float BULLET_HEIGHT       = 25.0f;



