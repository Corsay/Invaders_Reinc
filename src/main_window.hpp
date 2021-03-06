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
#include <QDialog>
#include <QLineEdit>
#include "window_constants.hpp"
#include "game_window.hpp"

#include <QSoundEffect>

class GameWindow;

enum DialogTypes
{
  OnSubmitClose,
  OnSubmitSettingsLeave,
  OnSettingsLoaded,
  OnSettingsLoadError,
  OnSaveRecord
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

using RecordsVect = std::vector<std::vector<QString>>;

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow();
  ~MainWindow();
  void InterfaceAddRecord();

  void InitSound();
  void SetVolume();

protected:
  // MENU
  void ShowMenuItems();
  // settings /load
  void WriteJson();
  bool ReadJson();
  void WriteXml();
  bool ReadXml();
  // WINDOW
  void MoveWindowToCenter();
  void ShowDialog(QString const & msg, DialogTypes type);
  void Resize(size_t w, size_t h);
  void SetTextsForCurLang();
  void SetSize(int state);
  void ResizeQGridLayouts();
  // RECORDS
  void CreateRecordTable();
  void WriteJsonRecord(RecordsVect & rezults);
  bool ReadJsonRecords(RecordsVect & rezults);
  void SaveRecord(QString const & name);

private slots:
  // SHORTCUTS
  void ShortcutPause();
  // MENU
  void NewGame();
  void ContinueGame();
  void CheckoutToSettings();
  // SETTINGS
  // buttons
  void CheckoutToMenu();
  void CheckoutToRecords();
  void LoadSettings();
  void SaveSettings();
  void SetDefaultSettings();
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
  // sound
  void ChangeSoundMenuVolume(int state);
  void ChangeSoundGameVolume(int state);
  void ChangeSoundMenuOn(bool state);
  void ChangeSoundGameOn(bool state);

private:
  // SHORTCUTS
  QShortcut * m_shortcutGamePause = nullptr;
  // MENU
  bool m_gameStarted = false;
  QPushButton * m_pbMenuNewGame = nullptr;
  QPushButton * m_pbMenuContinueGame = nullptr;
  QPushButton * m_pbMenuRecord = nullptr;
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
  QPushButton * m_pbSetDefault = nullptr;
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
  QLabel * m_lSoundComment = nullptr;
  QLabel * m_lSMainOn = nullptr;
  QLabel * m_lSMainVolume = nullptr;
  QLabel * m_lSGameOn = nullptr;
  QLabel * m_lSGameVolume = nullptr;
    // keysequenceedit
  QKeySequenceEdit * m_kseGunMoveLeft = nullptr;
  QKeySequenceEdit * m_kseGunMoveRight = nullptr;
  QKeySequenceEdit * m_kseGunShoot = nullptr;
  QKeySequenceEdit * m_kseGamePause = nullptr;
    // slider
  QSlider * m_slGPAliensCount = nullptr;
  QSlider * m_slGPObstacleCount = nullptr;
  QSlider * m_slGPGunStartLives = nullptr;
      // sound
  QSlider * m_slSMenuVolume = nullptr;
  QSlider * m_slSGameVolume = nullptr;
    // checkbox
  QCheckBox * m_chbGPObstacleRedraw = nullptr;
  QCheckBox * m_chbGPGunAddLive = nullptr;
      // sound
  QCheckBox * m_chbSMenuOn = nullptr;
  QCheckBox * m_chbSGameOn = nullptr;
    // combobox
  QComboBox * m_cbWindowState = nullptr;
  QComboBox * m_cbWindowSize = nullptr;
  QComboBox * m_cbLanguage = nullptr;
    // gridlayout
  QGridLayout * m_layoutSettings = nullptr;
    // widget
  QWidget * m_widgetSettings = nullptr;
  QWidget * m_widgetRecords = nullptr;
  // GAME
  GameWindow * m_windowGame = nullptr;
  // WINDOW  
  QStackedWidget * m_widgetStacked = nullptr;
  QTranslator m_translator;
  QSize m_size;
  QString m_style;
  // SOUND
  QSoundEffect * m_soundButtonClick = nullptr;
  // RECORDS
    // buttons
  QPushButton * m_pbToMenuFromRecords = nullptr;
    // label
  QLabel * m_table = nullptr;
    // QVBoxLayout
  QVBoxLayout * m_recordsVLayout = nullptr;
  RecordsVect recordsArray;
};
