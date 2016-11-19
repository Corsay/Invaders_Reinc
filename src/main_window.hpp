#pragma once

#include <QMainWindow>
#include <QDesktopWidget>
#include <QApplication>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QComboBox>
#include <QLabel>
#include <QShortcut>
#include <QKeySequenceEdit>
#include <QPushButton>
#include <QCheckBox>
#include <QSlider>
#include <QTranslator>
#include <QStackedWidget>

//#include <QTimer>
//#include <QOpenGLWidget>
#include "gameclasses/space.hpp"

enum DialogTypes
{
  OnSubmitGameSave,
  OnSubmitSettingsLeave
};
enum GameResolutionTypes
{
  Size800x600,
  Size1024x768,
  Size1280x720,
  Size1280x1024,
  Size1360x768,
  Size1366x768,
  Size1400x1050,
  Size1440x900,
  Size1600x900,
  Size1680x1050,
  Size1920x1080
};
enum GameWindowStateTypes
{
  FullScreen,
  MinimizedWindow,
  MaximizedWindow
};
enum GameLanguages
{
  English,
  Russian
};

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QStackedWidget* w);
  ~MainWindow();

protected:
  // MENU
  void ShowMenuItems();
  // WINDOW
  void MoveWindowToCenter();
  void ShowDialog(QString const & msg, DialogTypes type);
  void Resize(size_t w, size_t h);
  void SetTextsForCurLang();

private slots:
  // SHORTCUTS
  void ShortcutGunMoveLeft();
  void ShortcutGunMoveRight();
  void ShortcutGunShoot();
  void ShortcutPause();
  // MENU
  void NewGame();
  void ContinueOrLoadGame();
  void SaveGame();
  void CheckoutToSettings();
  // SETTINGS
  // buttons
  void CheckoutToMenu();
  void LoadSettings();
  void SaveSettings();
  // control
  void ChangeShortcutGunMoveLeft(QKeySequence key);
  void ChangeShortcutGunMoveRight(QKeySequence key);
  void ChangeShortcutGunShoot(QKeySequence key);
  void ChangeShortcutGamePause(QKeySequence key);
  // game parameters
  void ChangeAliensCount(int state);
  void ChangeObstacleCount(int state);
  void ChangeGunStartLives(int state);
  void ChangeObstacleRedrawState(bool state);
  void ChangeGunAddLiveState(bool state);
  // main
  void ChangeResolution(int state);
  void ChangeWindowState(int state);
  void ChangeLanguage(int state);
  // GAME
  // {TODO}

private:
  // SHORTCUTS
  QShortcut * m_shortcutGunMoveLeft = nullptr;
  QShortcut * m_shortcutGunMoveRight = nullptr;
  QShortcut * m_shortcutGunShoot = nullptr;
  QShortcut * m_shortcutGamePause = nullptr;
  // MENU
  bool m_gameStarted = false;
  QPushButton * m_pbMenuNewGame = nullptr;
  QPushButton * m_pbMenuContinueGame = nullptr;
  QPushButton * m_pbMenuSaveGame = nullptr;
  QPushButton * m_pbToSet = nullptr;
  QPushButton * m_pbExit = nullptr;
  QGridLayout * m_layoutMenu = nullptr;
  QWidget * m_widgetMenu = nullptr;
  // SETTINGS
  bool m_settingsChanged = false;
    // button
  QPushButton * m_pbToMenu = nullptr;
  QPushButton * m_pbSaveSettings = nullptr;
  QPushButton * m_pbLoadSettings = nullptr;
    // label
  QLabel * m_lControlComment = nullptr;
  QLabel * m_lControlGunMoveLeft = nullptr;
  QLabel * m_lControlGunMoveRight = nullptr;
  QLabel * m_lControlGunShoot = nullptr;
  QLabel * m_lControlGamePause = nullptr;
  QLabel * m_lGameParamComment = nullptr;
  QLabel * m_lGPAliensCount = nullptr;
  QLabel * m_lGPObstacleCount = nullptr;
  QLabel * m_lGPObstacleRedraw = nullptr;
  QLabel * m_lGPGunStartLives = nullptr;
  QLabel * m_lGPGunAddLive = nullptr;
  QLabel * m_lWindowComment = nullptr;
  QLabel * m_lWindowSize = nullptr;
  QLabel * m_lWindowState = nullptr;
  QLabel * m_lLanguage = nullptr;
    // keysequenceedit
  QKeySequenceEdit * m_kseGunMoveLeft = nullptr;
  QKeySequenceEdit * m_kseGunMoveRight = nullptr;
  QKeySequenceEdit * m_kseGunShoot = nullptr;
  QKeySequenceEdit * m_kseGamePause = nullptr;
    // slider
  QSlider * m_slGPAliensCount = nullptr;
  QSlider * m_slGPObstacleCount = nullptr;
  QSlider * m_slGPGunStartLives = nullptr;
    // checkbox
  QCheckBox * m_chbGPObstacleRedraw = nullptr;
  QCheckBox * m_chbGPGunAddLive = nullptr;
    // combobox
  QComboBox * m_cbWindowState = nullptr;
  QComboBox * m_cbWindowSize = nullptr;
  QComboBox * m_cbLanguage = nullptr;
    // gridlayout
  QGridLayout * m_layoutSettings = nullptr;
    // widget
  QWidget * m_widgetSettings = nullptr;
  // GAME
  //QTimer * m_timer = nullptr;
  //QOpenGLWidget * m_glWidget = nullptr;
  // WINDOW
  QStackedWidget * m_widgetStacked = nullptr;
  QStackedWidget * m_mainStakedWidget = nullptr;
  QTranslator m_translator;
  QSize m_size;
  QString m_style;
};
