#pragma once

#include <QMainWindow>
#include <QDesktopWidget>
#include <QApplication>

#include <QGridLayout>
#include <QHBoxLayout>

#include <QComboBox>
#include <QLabel>
#include <QShortcut>

#include <QPushButton>
#include <QLineEdit>

/*
#include <QSlider>
#include <QProgressBar>
#include <QSpinBox>

#include <QGroupBox>
#include <QTabWidget>
*/

//#include <QTimer>
//#include <QOpenGLWidget>

enum DialogTypes
{
  OnClose,
  OnBackToMainFromSettings
};
enum GameWindowStateTypes
{
  FullScreen,
  MinimizedWindow,
  MaximizedWindow
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

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow();
  ~MainWindow();

protected:
  //void mousePressEvent(QMouseEvent * e) override;
  //void mouseReleaseEvent(QMouseEvent * e) override;

  void MoveWindowToCenter();
  void ShowMenuItems();

  void ShowDialog(QString const & msg, DialogTypes type);
  void Resize(size_t w, size_t h);

private slots:
  void LoadSettings();
  void SaveSettings();
  // shortcuts
  void ShortcutGunMoveLeft();
  void ShortcutGunMoveRight();
  void ShortcutGunShoot();
  void ShortcutPause();
  // menu
  void NewGame();
  void ContinueOrLoadGame();
  void SaveGame();
  void CheckoutToSettings();
  // settings
  void CheckoutToMenu();
  void ChangeResolution(int state);
  void ChangeWindowState(int state);

private:
  int L2D(size_t px) const { return px * devicePixelRatio(); }

  bool m_gameStarted = false;
  bool m_settingsChanged = false;
  QPushButton * m_pbMenuNewGame = nullptr;
  QPushButton * m_pbMenuContinueGame = nullptr;
  QPushButton * m_pbMenuSaveGame = nullptr;
  QPushButton * m_pbExit = nullptr;
  QPushButton * m_pbToSet = nullptr;
  QPushButton * m_pbToMenu = nullptr;
  QPushButton * m_pbSaveSettings = nullptr;
  QPushButton * m_pbLoadSettings = nullptr;

  QComboBox * m_cbWindowSize = nullptr;

  QShortcut * m_shortcutGunMoveLeft = nullptr;
  QShortcut * m_shortcutGunMoveRight = nullptr;
  QShortcut * m_shortcutGunShoot = nullptr;
  QShortcut * m_shortcutGamePause = nullptr;

  QGridLayout * m_layoutMenu = nullptr;
  QGridLayout * m_layoutSettings = nullptr;

  QWidget * m_widgetMenu = nullptr;
  QWidget * m_widgetSettings = nullptr;

  QWidget * m_widgetCurrent = nullptr;      // for show and hide
  QSize m_size;
  QPalette m_palette;

  //QTimer * m_timer = nullptr;
  //QOpenGLWidget * m_glWidget = nullptr;
};
