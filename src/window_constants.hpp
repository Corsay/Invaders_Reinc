#pragma once

#include <QString>
#include <QKeySequence>

// window
static QString WINDOW_ICON_FOLDER = "data/images/alien.png";

// dialogs
static QString DIALOG_ON_SUBMIT_GAME_SAVE      = "Do you want to save the current state of the game before closing?";
static QString DIALOG_ON_SUBMIT_SETTINGS_LEAVE = "Do you want to save the current settings of the game before back to the main menu?";
static QString DIALOG_ON_SETTINGS_LOADED       = "Succesfull load settings.";
static QString DIALOG_ON_SETTINGS_LOAD_ERROR   = "Error then try to load settings.";
static QString ADDITION_DIALOG_TEXT = "\n\n Click to back to settings.";


// for key change
enum KeyTypes
{
  KeyMoveLeft,
  KeyMoveRight,
  KeyShoot,
  KeyPause
};
