#pragma once

#include <QMainWindow>
#include <QDesktopWidget>
#include <QApplication>

#include <QGridLayout>
#include <QHBoxLayout>

#include <QComboBox>
#include <QLabel>

#include <QPushButton>

#include <QSlider>
#include <QProgressBar>
#include <QSpinBox>

#include <QGroupBox>
#include <QTabWidget>

//#include <QTimer>
//#include <QOpenGLWidget>

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow();
  ~MainWindow();


protected:
  void MoveWindowToCenter();
  void ShowMenuItems();

  void ShowDialog(QString const & msg);

private slots:
  void LoadSettings();
  void SaveSettings();
  // menu
  void NewGame();
  void ContinueOrLoadGame();
  void SaveGame();
  void CheckoutToSettings();
  // settings
  void CheckoutToMenu();

private:
  bool m_gameStarted = false;
  QPushButton * m_pbMenuNewGame = nullptr;
  QPushButton * m_pbMenuContinueGame = nullptr;
  QPushButton * m_pbMenuSaveGame = nullptr;
  QPushButton * m_pbExit = nullptr;
  QPushButton * m_pbToSet = nullptr;
  QPushButton * m_pbToMenu = nullptr;
  QPushButton * m_pbSaveSettings = nullptr;
  QPushButton * m_pbLoadSettings = nullptr;

  QHBoxLayout * m_controlGunMoveLeft = nullptr;
  QHBoxLayout * m_controlGunMoveRight = nullptr;
  QHBoxLayout * m_controlGunShoot = nullptr;
  QHBoxLayout * m_controlPause = nullptr;
  QHBoxLayout * m_resolution = nullptr;

  QGridLayout * m_layoutMenu = nullptr;
  QGridLayout * m_layoutSettings = nullptr;

  QWidget * m_widgetMenu = nullptr;
  QWidget * m_widgetSettings = nullptr;

  QWidget * m_widgetCurrent = nullptr;      // for show and hide
  QSize m_size;

  //QTimer * m_timer = nullptr;
  //QOpenGLWidget * m_glWidget = nullptr;
};
