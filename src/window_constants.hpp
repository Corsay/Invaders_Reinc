#pragma once

#include <QString>
#include <QKeySequence>

// window
static QString WINDOW_ICON_FOLDER = "data/images/aliens/alienRaider.png";

// dialogs
  // Menu
static QString DIALOG_ON_SUBMIT_CLOSE          = "Are you really want to close program?";
static QString DIALOG_ON_SUBMIT_BREAK          = "Are you really want to break current game?";
static QString DIALOG_ON_SUBMIT_SETTINGS_LEAVE = "Do you want to save the current settings of the game before back to the main menu?";
static QString DIALOG_ON_SETTINGS_LOADED       = "Succesfull load settings.";
static QString DIALOG_ON_SETTINGS_LOAD_ERROR   = "Error then try to load settings.";
static QString ADDITION_DIALOG_TEXT            = "\n\n Click to back to settings.";
static QString DIALOG_TEXT_SETTINGS_SAVE       = "\n Click:\n Yes - to save settings and go to the main menu;\n No - to go to the main menu without saving;\n Abort - to abort action. ";
static QString DIALOG_TEXT_CLOSE               = "\n Click:\n Yes - to accept;\n No - to abort action. ";
static QString DIALOG_BUTTON_YES               = "Yes";
static QString DIALOG_BUTTON_NO                = "No";
static QString DIALOG_BUTTON_ABORT             = "Abort";
static QString DIALOG_BUTTON_SAVE              = "Save";
  // records
static QString DIALOG_ON_SAVE_RECORD           = "Input you name and click: \n 'Save' - to accept you record \n 'Abort' - to continue without saving you rate";
static QString DIALOG_ON_SAVE_RECORD_ERROR     = "\n Name are important to save record!";
static QString DIALOG_ON_SAVE_RECORD_INPUT_NAME= "Name:";
static QString RECORD_MESSAGE                  = "RECORDS:";
static QString RECORD_NO_MESSAGE               = "NO RECORDS! BE FIRST ;)";
const int MAX_COUNT_RECORDS = 5;
  // Game
static QString GAME_RESULT                     = "You rezult: ";
static QString GAME_OVER                       = "Game over. Gun shooted.";
static QString GAME_OVER_ADDITIONAL            = "Press Enter to go to the game scores!";
static QString GAME_CURRENT_RESULT             = "You current rezult: ";
static QString GAME_PRE_NEXT_LEVEL             = "Aliens destroyed! You win! Level ";
static QString GAME_NEXT_ADDITIONAL            = "Press Enter to go to the next level!";
static QString GAME_USE_CHEATS_MSG             = "You are used cheat code on this level";
static QString GAME_NEXT_ALIEN_MODIF           = "Next Level Aliens Modifications:";
static QString GAME_NEXT_ALIEN_MODIF_FAST_MOVE = "Little faster move";
static QString GAME_NEXT_ALIEN_MODIF_FAST_SHOOT= "Little faster shoot";
static QString GAME_NEXT_ALIEN_MODIF_SPEC_LIFE = "One more life to aliens";

// For key change
enum KeyTypes
{
  KeyMoveLeft,
  KeyMoveRight,
  KeyShoot,
  KeyPause
};
