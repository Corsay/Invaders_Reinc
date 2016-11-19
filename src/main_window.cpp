#include "main_window.hpp"

#include "game_widget.hpp"
#include "window_labels.hpp"
#include "constants.hpp"

#include <QFile>

#include <pugixml.hpp>
#include <json/json.h>
#include <json/writer.h>
#include <fstream>
#include <iostream>

// WINDOW
MainWindow::MainWindow()
{
  // window and widgets size
  m_size = QSize(800,600);

  // QStyle
  QFile styleFile("data/styles/default.qss");
  if (styleFile.open(QFile::ReadOnly))
  {
    m_style = QLatin1String(styleFile.readAll());
    std::cout << "style file opened" << std::endl;
  }
  else std::cout << "style file not opened" << std::endl;

  // QShortcuts
  m_shortcutGunMoveLeft = new QShortcut(this);
  connect(m_shortcutGunMoveLeft, SIGNAL(activated()), this, SLOT(ShortcutGunMoveLeft()));
  m_shortcutGunMoveLeft->setKey(Qt::Key_Left);
  m_shortcutGunMoveRight = new QShortcut(this);
  connect(m_shortcutGunMoveRight, SIGNAL(activated()), this, SLOT(ShortcutGunMoveRight()));
  m_shortcutGunMoveRight->setKey(Qt::Key_Right);
  m_shortcutGunShoot = new QShortcut(this);
  connect(m_shortcutGunShoot, SIGNAL(activated()), this, SLOT(ShortcutGunShoot()));
  m_shortcutGunShoot->setKey(Qt::Key_Up);
  m_shortcutGamePause = new QShortcut(this);
  connect(m_shortcutGamePause, SIGNAL(activated()), this, SLOT(ShortcutPause()));
  m_shortcutGamePause->setKey(Qt::Key_Escape);

  // Stacked widget
  m_widgetStacked = new QStackedWidget(this);

  // window settings
  this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
  this->setWindowIcon(QIcon(WINDOW_ICON_FOLDER));
  this->setMinimumSize(m_size);
  this->setWindowState(Qt::WindowState::WindowActive);
  this->setStyleSheet(m_style);
  this->setCentralWidget(m_widgetStacked);

  // FOR MAIN MENU
  // buttons
  m_pbMenuNewGame = new QPushButton();
  connect(m_pbMenuNewGame, SIGNAL(clicked(bool)), this, SLOT(NewGame()));
  m_pbMenuContinueGame = new QPushButton();
  connect(m_pbMenuContinueGame, SIGNAL(clicked(bool)), this, SLOT(ContinueOrLoadGame()));
  m_pbMenuSaveGame = new QPushButton();
  connect(m_pbMenuSaveGame, SIGNAL(clicked(bool)), this, SLOT(SaveGame()));
  m_pbToSet = new QPushButton();
  connect(m_pbToSet, SIGNAL(clicked(bool)), this, SLOT(CheckoutToSettings()));
  m_pbExit = new QPushButton();
  connect(m_pbExit, &QAbstractButton::clicked, [this]()
    {
      if (m_gameStarted) ShowDialog(DIALOG_ON_SUBMIT_GAME_SAVE, DialogTypes::OnSubmitGameSave);
      exit(0);
    });
  m_pbMenuNewGame->setIcon(QIcon("data/images/begin.ico"));
  m_pbExit->setObjectName("ExitButton");
  m_pbExit->setIcon(QIcon("data/images/end.ico"));

  // default button settings (game not started)
  ShowMenuItems();

  // fillers header and footer
  QWidget *topFiller = new QWidget;
  topFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  QWidget *bottomFiller = new QWidget;
  bottomFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  // layout
  m_layoutMenu = new QGridLayout;
  m_layoutMenu->addWidget(topFiller, 0, 0, 1, 3);
  m_layoutMenu->addWidget(m_pbMenuNewGame, 1, 1, 1, 1);
  m_layoutMenu->addWidget(m_pbMenuContinueGame, 2, 1, 1, 1);
  m_layoutMenu->addWidget(m_pbMenuSaveGame, 3, 1, 1, 1);
  m_layoutMenu->addWidget(m_pbToSet, 4, 1, 1, 1);
  m_layoutMenu->addWidget(m_pbExit, 6, 1, 1, 1);
  m_layoutMenu->addWidget(bottomFiller, 7, 0, 1, 3);

  // widget
  m_widgetMenu = new QWidget(m_widgetStacked);
  m_widgetMenu->setMinimumSize(m_size);
  m_widgetMenu->setLayout(m_layoutMenu);

  // FOR SETTINGS
  // buttons
  m_pbToMenu = new QPushButton();
  connect(m_pbToMenu, SIGNAL(clicked(bool)), this, SLOT(CheckoutToMenu()));
  m_pbSaveSettings = new QPushButton();
  connect(m_pbSaveSettings, SIGNAL(clicked(bool)), this, SLOT(SaveSettings()));
  m_pbLoadSettings = new QPushButton();
  connect(m_pbLoadSettings, SIGNAL(clicked(bool)), this, SLOT(LoadSettings()));

  // QLabels
  m_lControlComment = new QLabel();
  m_lControlGunMoveLeft = new QLabel();
  m_lControlGunMoveRight = new QLabel();
  m_lControlGunShoot = new QLabel();
  m_lControlGamePause = new QLabel();

  m_lGameParamComment = new QLabel();
  m_lGPAliensCount = new QLabel();
  m_lGPObstacleCount = new QLabel();
  m_lGPObstacleRedraw = new QLabel();
  m_lGPGunStartLives = new QLabel();
  m_lGPGunAddLive = new QLabel();

  m_lWindowComment = new QLabel();
  m_lWindowSize = new QLabel();
  m_lWindowState = new QLabel();
  m_lLanguage = new QLabel();

  // Work with Values and Keys
    // Control
  m_kseGunMoveLeft = new QKeySequenceEdit(m_shortcutGunMoveLeft->key());
  connect(m_kseGunMoveLeft, SIGNAL(keySequenceChanged(QKeySequence)), this, SLOT(ChangeShortcutGunMoveLeft(QKeySequence)));
  m_kseGunMoveRight = new QKeySequenceEdit(m_shortcutGunMoveRight->key());
  connect(m_kseGunMoveRight, SIGNAL(keySequenceChanged(QKeySequence)), this, SLOT(ChangeShortcutGunMoveRight(QKeySequence)));
  m_kseGunShoot = new QKeySequenceEdit(m_shortcutGunShoot->key());
  connect(m_kseGunShoot, SIGNAL(keySequenceChanged(QKeySequence)), this, SLOT(ChangeShortcutGunShoot(QKeySequence)));
  m_kseGamePause = new QKeySequenceEdit(m_shortcutGamePause->key());
  connect(m_kseGamePause, SIGNAL(keySequenceChanged(QKeySequence)), this, SLOT(ChangeShortcutGamePause(QKeySequence)));
    // Game parameters
  m_slGPAliensCount = new QSlider(Qt::Horizontal);
  m_slGPAliensCount->setRange(25, 200);
  m_slGPAliensCount->setValue(55);
  m_slGPAliensCount->setPageStep(1);
  connect(m_slGPAliensCount, SIGNAL(valueChanged(int)), this, SLOT(ChangeAliensCount(int)));

  m_slGPObstacleCount = new QSlider(Qt::Horizontal);
  m_slGPObstacleCount->setRange(0, 6);
  m_slGPObstacleCount->setValue(4);
  m_slGPObstacleCount->setPageStep(1);
  connect(m_slGPObstacleCount, SIGNAL(valueChanged(int)), this, SLOT(ChangeObstacleCount(int)));

  m_slGPGunStartLives = new QSlider(Qt::Horizontal);
  m_slGPGunStartLives->setRange(1, 5);
  m_slGPGunStartLives->setValue(3);
  m_slGPGunStartLives->setPageStep(1);
  connect(m_slGPGunStartLives, SIGNAL(valueChanged(int)), this, SLOT(ChangeGunStartLives(int)));

  m_chbGPObstacleRedraw = new QCheckBox;
  m_chbGPObstacleRedraw->setChecked(false);
  connect(m_chbGPObstacleRedraw, SIGNAL(clicked(bool)), this, SLOT(ChangeObstacleRedrawState(bool)));

  m_chbGPGunAddLive = new QCheckBox;
  m_chbGPGunAddLive->setChecked(true);
  connect(m_chbGPGunAddLive, SIGNAL(clicked(bool)), this, SLOT(ChangeGunAddLiveState(bool)));
    // Main
  m_cbWindowState = new QComboBox();
  connect(m_cbWindowState, SIGNAL(activated(int)), this, SLOT(ChangeWindowState(int)));

  m_cbWindowSize = new QComboBox();
  m_cbWindowSize->addItem("800x600", GameResolutionTypes::Size800x600);
  m_cbWindowSize->addItem("1024x768", GameResolutionTypes::Size1024x768);
  m_cbWindowSize->addItem("1280x720", GameResolutionTypes::Size1280x720);
  m_cbWindowSize->addItem("1280x1024", GameResolutionTypes::Size1280x1024);
  m_cbWindowSize->addItem("1360x768", GameResolutionTypes::Size1360x768);
  m_cbWindowSize->addItem("1366x768", GameResolutionTypes::Size1366x768);
  m_cbWindowSize->addItem("1400x1050", GameResolutionTypes::Size1400x1050);
  m_cbWindowSize->addItem("1440x900", GameResolutionTypes::Size1440x900);
  m_cbWindowSize->addItem("1600x900", GameResolutionTypes::Size1600x900);
  m_cbWindowSize->addItem("1680x1050", GameResolutionTypes::Size1680x1050);
  m_cbWindowSize->addItem("1920x1080", GameResolutionTypes::Size1920x1080);
  m_cbWindowSize->setCurrentIndex(GameResolutionTypes::Size800x600);
  connect(m_cbWindowSize, SIGNAL(activated(int)), this, SLOT(ChangeResolution(int)));

  m_cbLanguage = new QComboBox();
  m_cbLanguage->addItem("English", GameLanguages::English);
  m_cbLanguage->addItem("Russian", GameLanguages::Russian);
  m_cbLanguage->setCurrentIndex(GameLanguages::English);
  connect(m_cbLanguage, SIGNAL(activated(int)), this, SLOT(ChangeLanguage(int)));

  // QHBoxLayouts
    // control
  QHBoxLayout * hbControlGunMoveLeft = new QHBoxLayout;
  hbControlGunMoveLeft->addWidget(m_lControlGunMoveLeft);
  hbControlGunMoveLeft->addWidget(m_kseGunMoveLeft);
  QHBoxLayout * hbControlGunMoveRight = new QHBoxLayout;
  hbControlGunMoveRight->addWidget(m_lControlGunMoveRight);
  hbControlGunMoveRight->addWidget(m_kseGunMoveRight);
  QHBoxLayout * hbControlGunShoot = new QHBoxLayout;
  hbControlGunShoot->addWidget(m_lControlGunShoot);
  hbControlGunShoot->addWidget(m_kseGunShoot);
  QHBoxLayout * hbControlPause = new QHBoxLayout;
  hbControlPause->addWidget(m_lControlGamePause);
  hbControlPause->addWidget(m_kseGamePause);
    // game param
  QHBoxLayout * hbGPAlienCount = new QHBoxLayout;
  hbGPAlienCount->addWidget(m_lGPAliensCount);
  hbGPAlienCount->addWidget(m_slGPAliensCount);
  QHBoxLayout * hbGPObstacleCount = new QHBoxLayout;
  hbGPObstacleCount->addWidget(m_lGPObstacleCount);
  hbGPObstacleCount->addWidget(m_slGPObstacleCount);
  QHBoxLayout * hbGPObstacleRedraw = new QHBoxLayout;
  hbGPObstacleRedraw->addWidget(m_lGPObstacleRedraw);
  hbGPObstacleRedraw->addWidget(m_chbGPObstacleRedraw);
  QHBoxLayout * hbGPGunStartLives = new QHBoxLayout;
  hbGPGunStartLives->addWidget(m_lGPGunStartLives);
  hbGPGunStartLives->addWidget(m_slGPGunStartLives);
  QHBoxLayout * hbGPGunAddLive = new QHBoxLayout;
  hbGPGunAddLive->addWidget(m_lGPGunAddLive);
  hbGPGunAddLive->addWidget(m_chbGPGunAddLive);
    // window
  QHBoxLayout * hbWindowSize = new QHBoxLayout;
  hbWindowSize->addWidget(m_lWindowSize);
  hbWindowSize->addWidget(m_cbWindowSize);
  QHBoxLayout * hbWindowState = new QHBoxLayout;
  hbWindowState->addWidget(m_lWindowState);
  hbWindowState->addWidget(m_cbWindowState);
  QHBoxLayout * hbLanguage = new QHBoxLayout;
  hbLanguage->addWidget(m_lLanguage);
  hbLanguage->addWidget(m_cbLanguage);

  // layout
  m_layoutSettings = new QGridLayout;
  m_layoutSettings->addWidget(m_pbToMenu, 0, 0);
    // control
  m_layoutSettings->addWidget(m_lControlComment, 2, 0, 1, 2);
  m_layoutSettings->addLayout(hbControlGunMoveLeft, 3, 0, 1, 2);
  m_layoutSettings->addLayout(hbControlGunMoveRight, 4, 0, 1, 2);
  m_layoutSettings->addLayout(hbControlGunShoot, 5, 0, 1, 2);
  m_layoutSettings->addLayout(hbControlPause, 6, 0, 1, 2);
    // game param
  m_layoutSettings->addWidget(m_lGameParamComment, 2, 2, 1, 2);
  m_layoutSettings->addLayout(hbGPAlienCount, 3, 2, 1, 2);
  m_layoutSettings->addLayout(hbGPObstacleCount, 4, 2, 1, 2);
  m_layoutSettings->addLayout(hbGPObstacleRedraw, 5, 2, 1, 2);
  m_layoutSettings->addLayout(hbGPGunStartLives, 6, 2, 1, 2);
  m_layoutSettings->addLayout(hbGPGunAddLive, 7, 2, 1, 2);
    // window
  m_layoutSettings->addWidget(m_lWindowComment, 8, 0, 1, 2);
  m_layoutSettings->addLayout(hbWindowSize, 9, 0, 1, 2);
  m_layoutSettings->addLayout(hbWindowState, 10, 0, 1, 2);
  m_layoutSettings->addLayout(hbLanguage, 11, 0, 1, 2);
    // buttons
  m_layoutSettings->addWidget(m_pbSaveSettings, 12, 0);
  m_layoutSettings->addWidget(m_pbLoadSettings, 12, 1);
  m_layoutSettings->addWidget(bottomFiller, 13, 0, 1, 4);

  // widget
  m_widgetSettings = new QWidget(m_widgetStacked);
  m_widgetSettings->setMinimumSize(m_size);
  m_widgetSettings->setLayout(m_layoutSettings);
  m_widgetSettings->hide();


  // GAME
  m_windowGame = new GameWindow(m_widgetStacked);
  // {TODO:}
  // glwidget
  //m_glWidget = new GLWidget(this, qRgb(20, 20, 50));   // Виджет игры (окно, задний фон) (наш класс наследуемый от QOpenGLWidget и QOpenGLFunctions)
  //m_timer = new QTimer(this);                          // таймер
  //m_timer->setInterval(10);                            // период работы таймера
  //setCentralWidget(m_glWidget);                        // Главный виджет текущего окна this->setCentralWidget
  //connect(m_timer, &QTimer::timeout, m_glWidget, static_cast<QWidgetVoidSlot>(&QWidget::update));
  //m_timer->start();                                    // запуск таймера
  //setFocusPolicy(Qt::StrongFocus);


  // fill stackedWidget
  m_widgetStacked->addWidget(m_widgetMenu);
  m_widgetStacked->addWidget(m_widgetSettings);
  m_widgetStacked->addWidget(m_windowGame);
  m_widgetStacked->setCurrentIndex(0);

  // load all user settings from file
  // {TODO:}
  // new shortcut keys
  // new m_size
  // new language

  // set new settings
    // shortcut
  // {TODO: shortcuts load}
  // m_shortcutGunMoveLeft->setKey(Qt::Key_Left);
  // m_shortcutGunMoveRight->setKey(Qt::Key_Right);
  // m_shortcutGunShoot->setKey(Qt::Key_Up);
  // m_shortcutGamePause->setKey(Qt::Key_Escape);
    // Translator
  m_translator.load("data/translations/en");
  qApp->installTranslator(&m_translator);
    // size
  Resize(m_size.width(),m_size.height());
      // menu layout
  m_layoutMenu->setMargin(20);
  m_layoutMenu->setColumnStretch(0, m_size.width()/100*30);
  m_layoutMenu->setColumnMinimumWidth(1, 225);
  m_layoutMenu->setColumnStretch(2, m_size.width()/100*30);
  m_layoutMenu->setRowStretch(0, m_size.height()/100*10);
  m_layoutMenu->setRowMinimumHeight(5, 36);
  m_layoutMenu->setRowStretch(7, m_size.height()/100*15);
      // settings layout
  m_layoutSettings->setMargin(20);
  m_layoutSettings->setColumnMinimumWidth(0, 140);
  m_layoutSettings->setColumnMinimumWidth(1, 140);
  m_layoutSettings->setColumnMinimumWidth(2, 140);
  m_layoutSettings->setColumnMinimumWidth(3, 140);
  m_layoutSettings->setColumnStretch(4, m_size.width()/100*30);
  m_layoutSettings->setRowMinimumHeight(1, 15);
  m_layoutSettings->setRowMinimumHeight(7, 15);
  m_layoutSettings->setRowMinimumHeight(12, 45);
  m_layoutSettings->setRowStretch(13, m_size.height()/100*15);
    // language
  SetTextsForCurLang();
}

// Деструктор
MainWindow::~MainWindow()
{

}

// Смещение окна в центр экрана
void MainWindow::MoveWindowToCenter()
{
  QRect frect = frameGeometry();
  frect.moveCenter(QDesktopWidget().availableGeometry().center());
  move(frect.topLeft());
}

// Предлагает сохранить игру -> вызывает SaveGame в случае подтверждения пользователем
void MainWindow::ShowDialog(QString const & msg, DialogTypes type)
{
  std::cout << msg.toStdString() << std::endl;
}

void MainWindow::Resize(size_t w, size_t h)
{
  m_size.setWidth(w);
  m_size.setHeight(h);

  this->setMinimumSize(m_size);
  this->resize(m_size);
  MoveWindowToCenter();
}


void MainWindow::SetTextsForCurLang()
{
  // WINDOW
  this->setWindowTitle(QMainWindow::tr("Invaders Reincarnation"));
  // MENU
    // button
  m_pbMenuNewGame->setText(QPushButton::tr("New game"));
  m_pbMenuNewGame->setToolTip(QPushButton::tr("Start new game"));
  if (m_gameStarted)
  {
    m_pbMenuContinueGame->setText(QPushButton::tr("Continue game"));
    m_pbMenuContinueGame->setToolTip(QPushButton::tr("Continue current game"));
  }
  else
  {
    m_pbMenuContinueGame->setText(QPushButton::tr("Load game"));
    m_pbMenuContinueGame->setToolTip(QPushButton::tr("Load game from the save file"));
  }
  m_pbMenuSaveGame->setText(QPushButton::tr("Save game"));
  m_pbMenuSaveGame->setToolTip(QPushButton::tr("Save current game state to the file"));
  m_pbToSet->setText(QPushButton::tr("Settings"));
  m_pbToSet->setToolTip(QPushButton::tr("Move to the settings"));
  m_pbExit->setText(QPushButton::tr("Exit"));
  m_pbExit->setToolTip(QPushButton::tr("Close program"));
  // SETTINGS
    // button
  m_pbToMenu->setText(QPushButton::tr("Menu"));
  m_pbToMenu->setToolTip(QPushButton::tr("Back to the main menu"));
  m_pbSaveSettings->setText(QPushButton::tr("Save settings"));
  m_pbSaveSettings->setToolTip(QPushButton::tr("Save settings to data/settings"));
  m_pbLoadSettings->setText(QPushButton::tr("Load settings"));
  m_pbLoadSettings->setToolTip(QPushButton::tr("Load settings from data/settings"));
    // label
  m_lControlComment->setText(QLabel::tr("_________________Control buttons:_________________"));
  m_lControlGunMoveLeft->setText(QLabel::tr("Gun move left button---"));
  m_lControlGunMoveRight->setText(QLabel::tr("Gun move right button-"));
  m_lControlGunShoot->setText(QLabel::tr("Button to gun shoot-----"));
  m_lControlGamePause->setText(QLabel::tr("Game pause---------------"));
  m_lGameParamComment->setText(QLabel::tr("____________________Game:_____________________"));
  m_lGPAliensCount->setText(QLabel::tr("Count of aliens = ") + QString::number(m_slGPAliensCount->value()));
  m_lGPObstacleCount->setText(QLabel::tr("Count of obstacles = ") + QString::number(m_slGPObstacleCount->value()));
  m_lGPObstacleRedraw->setText(QLabel::tr("Redraw obstacles only at first level"));
  m_lGPGunStartLives->setText(QLabel::tr("Start gun lives count = ") + QString::number(m_slGPGunStartLives->value()));
  m_lGPGunAddLive->setText(QLabel::tr("Add one life to gun at every level"));
  m_lWindowComment->setText(QLabel::tr("______________________Main:_______________________"));
  m_lWindowSize->setText(QLabel::tr("Window size"));
  m_lWindowState->setText(QLabel::tr("Window state"));
  m_lLanguage->setText(QLabel::tr("Language:"));
    // combo box
      // Win state
  m_cbWindowState->clear();
  m_cbWindowState->addItem(QComboBox::tr("Full screen"), GameWindowStateTypes::FullScreen);
  m_cbWindowState->addItem(QComboBox::tr("Minimized window"), GameWindowStateTypes::MinimizedWindow);
  m_cbWindowState->addItem(QComboBox::tr("Maximized window"), GameWindowStateTypes::MaximizedWindow);
  if (windowState() == Qt::WindowState::WindowMaximized) m_cbWindowState->setCurrentIndex(GameWindowStateTypes::MaximizedWindow);
  else if(windowState() == Qt::WindowState::WindowFullScreen) m_cbWindowState->setCurrentIndex(GameWindowStateTypes::FullScreen);
  else m_cbWindowState->setCurrentIndex(GameWindowStateTypes::MinimizedWindow);
      // language

    // DIALOGS
  DIALOG_ON_SUBMIT_GAME_SAVE      = QObject::tr("Do you want to save the current state of the game before closing?");
  DIALOG_ON_SUBMIT_SETTINGS_LEAVE = QObject::tr("Do you want to save the current settings of the game before back to the main menu?");
}

// SHORTCUTS
// shortcuts  slots
void MainWindow::ShortcutGunMoveLeft()
{
  std::cout << "Not Implemented" << std::endl;
}

void MainWindow::ShortcutGunMoveRight()
{
  std::cout << "Not full relased" << std::endl;
}

void MainWindow::ShortcutGunShoot()
{
  std::cout << "Not full relased" << std::endl;
}

void MainWindow::ShortcutPause()
{
  // set game pause
  std::cout << "Not full relased" << std::endl;

  if (m_widgetStacked->currentIndex() != 0) CheckoutToMenu();
}


// MENU
// check current game state and show needed buttons in main menu
void MainWindow::ShowMenuItems()
{
  if (m_gameStarted)
  {
    m_pbMenuNewGame->hide();
    m_pbMenuContinueGame->setText(QPushButton::tr("Continue game"));
    m_pbMenuContinueGame->setToolTip(QPushButton::tr("Continue current game"));
    m_pbMenuSaveGame->show();
  }
  else
  {
    m_pbMenuNewGame->show();
    m_pbMenuContinueGame->setText(QPushButton::tr("Load game"));
    m_pbMenuContinueGame->setToolTip(QPushButton::tr("Load game from the save file"));
    m_pbMenuSaveGame->hide();
  }
}

// menu button slots
void MainWindow::NewGame()
{
  // flag set change menu
  m_gameStarted = true;
  ShowMenuItems();
  m_widgetStacked->setCurrentIndex(2);
}

void MainWindow::ContinueOrLoadGame()
{
  if (m_gameStarted) // Continue game
  {
    // go to the game widget
    // activate timer

    std::cout << "Not full relased" << std::endl;
  }
  else               // Load game
  {
    // flag set change menu
    m_gameStarted = true;
    ShowMenuItems();

    std::cout << "Not full relased" << std::endl;
  }
}

void MainWindow::SaveGame()
{
  std::cout << "Not full relased" << std::endl;
}

void MainWindow::CheckoutToSettings()
{
  m_widgetStacked->setCurrentIndex(1);
}


// SETTINGS
// settings button slots
void MainWindow::CheckoutToMenu()
{
  m_widgetStacked->setCurrentIndex(0);

  if (m_settingsChanged) ShowDialog(DIALOG_ON_SUBMIT_SETTINGS_LEAVE, DialogTypes::OnSubmitSettingsLeave);
}

// save/load settings
void MainWindow::WriteJson()
{
  Json::Value settings;
  Json::Value resolutions(Json::arrayValue);
  resolutions.append(Json::Value("800x600"));
  resolutions.append(Json::Value("1024x768"));
  resolutions.append(Json::Value("1280x1024"));

  auto & root = settings["settings"];
  root["resolution"] = resolutions;
  root["aliensCount"] = 100;
  root["bulletsCount"] = 200;

  root["entities"]["gun"]["health"] = 50;
  root["entities"]["alien"]["health"] = 20;
  root["entities"]["obstacle"]["health"] = 15;

  std::ofstream settingsFile;
  settingsFile.open("settings.json");
  if (settingsFile.is_open())
  {
    Json::StyledWriter styledWriter;
    settingsFile << styledWriter.write(settings);
    settingsFile.close();
  }
}

void MainWindow::ReadJson()
{
  Json::Value settings;
  std::ifstream file("settings.json");
  if (file.is_open())
  {
    file >> settings;
    file.close();
  }

  Json::Value & resolutions = settings["settings"]["resolution"];
  if (resolutions.isArray())
  {
    for (Json::Value::ArrayIndex i = 0; i < resolutions.size(); i++)
      std::cout << resolutions[i].asString() << std::endl;
  }
  std::cout << settings["settings"]["aliensCount"].asInt() << std::endl;
  std::cout << settings["settings"]["bulletsCount"].asInt() << std::endl;

  Json::Value & entities = settings["settings"]["entities"];
  std::cout << entities["gun"]["health"].asInt() << std::endl;
  std::cout << entities["alien"]["health"].asInt() << std::endl;
  std::cout << entities["obstacle"]["health"].asInt() << std::endl;
}

void MainWindow::WriteXml()
{
  pugi::xml_document doc;
  auto declarationNode = doc.append_child(pugi::node_declaration);
  declarationNode.append_attribute("version") = "1.0";
  declarationNode.append_attribute("encoding") = "UTF-8";

  auto root = doc.append_child("settings");
  pugi::xml_node resolutions = root.append_child("resolutions");
  resolutions.append_child("resolution").append_child(pugi::node_pcdata).set_value("800x600");
  resolutions.append_child("resolution").append_child(pugi::node_pcdata).set_value("1024x768");
  resolutions.append_child("resolution").append_child(pugi::node_pcdata).set_value("1280x1024");

  root.append_child("aliensCount").append_attribute("value").set_value(100);
  root.append_child("bulletsCount").append_attribute("value").set_value(200);

  pugi::xml_node entities = root.append_child("entities");
  entities.append_child("gun").append_attribute("health").set_value(50);
  entities.append_child("alien").append_attribute("health").set_value(20);
  entities.append_child("obstacle").append_attribute("health").set_value(15);

  doc.save_file("settings.xml", PUGIXML_TEXT("  "));
}

void MainWindow::ReadXml()
{
  pugi::xml_document doc;
  pugi::xml_parse_result result = doc.load_file("settings.xml", pugi::parse_default | pugi::parse_declaration);
  if (result)
  {
    pugi::xml_node root = doc.document_element();
    pugi::xml_node resolutions = root.child("resolutions");
    if (!resolutions.empty())
    {
      for (pugi::xml_node const & resolution : resolutions.children())
        std::cout << resolution.child_value() << std::endl;
    }

    pugi::xml_node aliensCount = root.child("aliensCount");
    if (!aliensCount.empty())
      std::cout << aliensCount.attribute("value").as_int() << std::endl;

    pugi::xml_node bulletsCount = root.child("bulletsCount");
    if (!bulletsCount.empty())
      std::cout << bulletsCount.attribute("value").as_int() << std::endl;

    pugi::xml_node entities = root.child("entities");
    if (!entities.empty())
    {
      pugi::xml_node gun = entities.child("gun");
      if (!gun.empty())
        std::cout << gun.attribute("health").as_int() << std::endl;

      pugi::xml_node alien = entities.child("alien");
      if (!alien.empty())
        std::cout << alien.attribute("health").as_int() << std::endl;

      pugi::xml_node obstacle = entities.child("obstacle");
      if (!obstacle.empty())
        std::cout << obstacle.attribute("health").as_int() << std::endl;
    }
  }
}

// set default settings
void MainWindow::SetDefaultSettings()
{
  m_settingsChanged = true;

  std::cout << "Not full relased" << std::endl;
}

// load settings from file
void MainWindow::LoadSettings()
{
  m_settingsChanged = false;

  std::cout << "Not full relased" << std::endl;
}

// save settings to file
void MainWindow::SaveSettings()
{
  m_settingsChanged = false;

  std::cout << "Not full relased" << std::endl;
}

// settings controls
void MainWindow::ChangeShortcutGunMoveLeft(QKeySequence key)
{
  m_shortcutGunMoveLeft->setKey(key);
}

void MainWindow::ChangeShortcutGunMoveRight(QKeySequence key)
{
  m_shortcutGunMoveRight->setKey(key);
}

void MainWindow::ChangeShortcutGunShoot(QKeySequence key)
{
  m_shortcutGunShoot->setKey(key);
}

void MainWindow::ChangeShortcutGamePause(QKeySequence key)
{
  m_shortcutGamePause->setKey(key);
}

// settings game
void MainWindow::ChangeAliensCount(int state)
{
  ALIEN_COUNT = state;
  m_lGPAliensCount->setText(QLabel::tr("Count of aliens = ") + QString::number(state));
  m_settingsChanged = true;
}

void MainWindow::ChangeObstacleCount(int state)
{
  OBSTACLE_COUNT = state;
  m_lGPObstacleCount->setText(QLabel::tr("Count of obstacles = ") + QString::number(state));
  m_settingsChanged = true;
}
void MainWindow::ChangeGunStartLives(int state)
{
  GUN_LIVES_START = state;
  m_lGPGunStartLives->setText(QLabel::tr("Start gun lives count = ") + QString::number(state));
  m_settingsChanged = true;
}

void MainWindow::ChangeObstacleRedrawState(bool state)
{
  OBSTACLE_REDRAW_EVERY_LEVEL = state;
  m_settingsChanged = true;
}

void MainWindow::ChangeGunAddLiveState(bool state)
{
  GUN_LIVES_INC_EVERY_LEVEL = state;
  m_settingsChanged = true;
}

// settings main
void MainWindow::ChangeResolution(int state)
{
  size_t w = 800, h = 600;
  switch (state)
  {
    case Size1024x768: { w = 1024; h = 768; break; }
    case Size1280x720: { w = 1280; h = 720; break; }
    case Size1280x1024: { w = 1280; h = 1024; break; }
    case Size1360x768: { w = 1360; h = 768; break; }
    case Size1366x768: { w = 1366; h = 768; break; }
    case Size1400x1050: { w = 1400; h = 1050; break; }
    case Size1440x900: { w = 1440; h = 900; break; }
    case Size1600x900: { w = 1600; h = 900; break; }
    case Size1680x1050: { w = 1680; h = 1050; break; }
    case Size1920x1080: { w = 1920; h = 1080; break; }
  }
  Resize(w,h);
  m_settingsChanged = true;
}

void MainWindow::ChangeWindowState(int state)
{
  if (state == GameWindowStateTypes::FullScreen)
  {
    this->showFullScreen();
    m_cbWindowSize->setDisabled(true);
    m_cbWindowSize->setObjectName("NotActiveBox");
    m_cbWindowSize->setStyleSheet(m_style);
  }
  else if (state == GameWindowStateTypes::MinimizedWindow)
  {
    setWindowState(Qt::WindowState::WindowActive);
    m_cbWindowSize->setDisabled(false);
    m_cbWindowSize->setObjectName("");
    m_cbWindowSize->setStyleSheet(m_style);
  }
  else
  {
    setWindowState(Qt::WindowState::WindowMaximized);
    m_cbWindowSize->setDisabled(true);
    m_cbWindowSize->setObjectName("NotActiveBox");
    m_cbWindowSize->setStyleSheet(m_style);
  }
  m_size.setWidth(this->width());
  m_size.setHeight(this->height());
  m_settingsChanged = true;
}

void MainWindow::ChangeLanguage(int state)
{
  switch (state)
  {
    case GameLanguages::English:
    {
      m_translator.load("data/translations/en");
      qApp->installTranslator(&m_translator);
      SetTextsForCurLang();
      break;
    }
    case GameLanguages::Russian:
    {
      m_translator.load("data/translations/ru");
      qApp->installTranslator(&m_translator);
      SetTextsForCurLang();
      break;
    }
  }
  m_settingsChanged = true;
}
