#pragma once

#include <QString>
#include <QKeySequence>

// window
static QString WINDOW_ICON_FOLDER = "data/images/aliens/alienRaider.png";

// dialogs
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


// for key change
enum KeyTypes
{
  KeyMoveLeft,
  KeyMoveRight,
  KeyShoot,
  KeyPause
};
