#pragma once

#include <QString>

// default english text initialization
// window
static QString WINDOW_TITLE       = "Invaders Reincarnation";
static QString WINDOW_ICON_FOLDER = "data/images/alien.png";


// dialogs
static QString DIALOG_ON_SUBMIT_GAME_SAVE      = "Do you want to save the current state of the game before closing?";
static QString DIALOG_ON_SUBMIT_SETTINGS_LEAVE = "Do you want to save the current settings of the game before back to the main menu?";


// main menu
  // button text
static QString MENU_BT_NEW_GAME      = "New game";
static QString MENU_BT_LOAD_GAME     = "Load game";
static QString MENU_BT_CONTINUE_GAME = "Continue game";
static QString MENU_BT_SAVE_GAME     = "Save game";
static QString MENU_BT_TO_SETTINGS   = "Settings";
static QString MENU_BT_EXIT          = "Exit";
  // button tooltip text
static QString MENU_BTTT_NEW_GAME = "Start new game";
static QString MENU_BTTT_LOAD_GAME = "Load game from the save file";
static QString MENU_BTTT_CONTINUE_GAME = "Continue current game";
static QString MENU_BTTT_SAVE_GAME = "Save current game state to the file";
static QString MENU_BTTT_TO_SETTINGS = "Move to the settings";
static QString MENU_BTTT_EXIT = "Close program";


// settings
  // button text
static QString SETTINGS_BT_TO_MENU = "Menu";
static QString SETTINGS_BT_SAVE    = "Save settings";
static QString SETTINGS_BT_LOAD    = "Load settings";
  // button tooltip text
static QString SETTINGS_BTTT_TO_MENU = "Back to the main menu";
static QString SETTINGS_BTTT_SAVE    = "Save settings to data/settings";
static QString SETTINGS_BTTT_LOAD    = "Load settings from data/settings";
  // labels
static QString SETTINGS_LC_COMMENT        = "_________________Control buttons:_________________";
static QString SETTINGS_LC_GUN_MOVE_LEFT  = "Gun move left button---";
static QString SETTINGS_LC_GUN_MOVE_RIGHT = "Gun move right button-";
static QString SETTINGS_LC_GUN_SHOOT      = "Button to gun shoot-----";
static QString SETTINGS_LC_GAME_PAUSE     = "Game pause---------------";
static QString SETTINGS_LGP_COMMENT         = "____________________Game:_____________________";
static QString SETTINGS_LGP_ALIENS_COUNT    = "Count of aliens = ";
static QString SETTINGS_LGP_OBSTACLES_COUNT = "Count of obstacles = ";
static QString SETTINGS_LGP_OBSTACLE_REDRAW = "Redraw obstacles only at first level";
static QString SETTINGS_LGP_GUN_START_LIVES = "Start gun lives count = ";
static QString SETTINGS_LGP_GUN_ADD_LIVE    = "Add one life to gun at every level";
static QString SETTINGS_LW_COMMENT  = "______________________Main:_______________________";
static QString SETTINGS_LW_SIZE     = "Window size";
static QString SETTINGS_LW_STATE    = "Window state";
static QString SETTINGS_LW_LANGUAGE = "Language:";
  // Window state box
static QString SETTINGS_WSB_FULLSCREEN = "Full screen";
static QString SETTINGS_WSB_MINWINDOW = "Minimized window";
static QString SETTINGS_WSB_MAXWINDOW = "Maximized window";
  // Language box
static QString SETTINGS_LB_EN = "English";
static QString SETTINGS_LB_RU = "Русский";
