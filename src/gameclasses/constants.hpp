#pragma once
#include "logger.hpp"
extern SimpleLogger & logger;

std::string onlyFile(std::string);
void changeConstants(float w, float h);

#define WHERE "File: " << onlyFile( __FILE__ ) << " Function: " << __FUNCTION__ << " Line:" << __LINE__

// Game parameters management
// extern (need to send it as param to space2d)
// ALIEN
extern size_t ALIEN_COUNT;
// GUN
extern size_t GUN_LIVES_START;
extern bool   GUN_LIVES_INC_EVERY_LEVEL;
// OBSTACLE
extern size_t OBSTACLE_COUNT;
extern bool   OBSTACLE_REDRAW_EVERY_LEVEL;
// GAME SPACE
extern float  GAME_PADDING_LEFT;
extern float  GAME_PADDING_RIGHT;
extern float  GAME_PADDING_TOP;
extern float  GAME_PADDING_BOTTOM;

// const (setted value)
// DEFAULT
extern float DEFAULT_HEALTH; // median alien = 50,  gun = 50,  bullet(damage health) = 50, box_part = 50
extern float DEFAULT_SPEED;   // (much of aliens) alien = 0.5, gun = 2.0, bullet(fly speed) = 5.0
// ALIEN
extern float ALIEN_HEALTH_START;
extern float ALIEN_HEALTH_INC;
extern float ALIEN_SPEED_SHOOT_START;
extern float ALIEN_SPEED_SHOOT_INC;
extern float AlIEN_WIDTH;
extern float ALIEN_HEIGHT;
extern float ALIEN_BOX_LEFT;  // left border of aliensMatrix
extern float ALIEN_BOX_TOP;   // top border
extern float ALIEN_HORIZONTAL_DISTANCE;
extern float ALIEN_VERTICAL_DISTANCE;
extern float ALIENT_HORIZONTAL_STEP;
extern float ALIENT_VERTICAL_STEP;
// GUN
extern float GUN_HEALTH_START;
extern float GUN_HEALTH_INC;
extern float GUN_SPEED_SHOOT_START ;
extern float GUN_SPEED_SHOOT_INC   ;
extern float GUN_LEFT_LIMIT        ;
extern float GUN_RIGHT_LIMIT       ;
extern float GUN_STEP              ;
extern float GUN_START_X           ;
extern float GUN_START_Y           ;
extern float GUN_WIDTH             ;
extern float GUN_HEIGHT            ;
// OBSTACLE
extern float OBSTACLE_BOX_LEFT     ;      // +
extern float OBSTACLE_BOX_RIGHT    ;      // +
extern float OBSTACLE_BOX_BOTTOM   ;     // +
extern float OBSTACLE_WIDTH        ;    // +
extern float OBSTACLE_HEIGHT       ;    // +
extern float OBSTACLE_PART_WIDTH   ;
extern float OBSTACLE_PART_HEIGHT  ;
extern float OBSTACLE_TOTAL_HEALTH ;
extern float OBSTACLE_DISTANCE     ;     // +
// BULLET
extern float BULLET_DAMAGE_START;
extern float BULLET_DAMAGE_INC  ;
extern float BULLET_SPEED_START ;
extern float BULLET_SPEED_INC   ;
extern float BULLET_WIDTH       ;
extern float BULLET_HEIGHT      ;

extern float LAST_WINDOW_VERTICAL_SIZE;
extern float LAST_WINDOW_HORIZONTAL_SIZE;
