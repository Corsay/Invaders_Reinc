#include <iostream>
#include "main_window.hpp"

//#include "gl_widget.hpp"

//typedef void (QWidget::*QWidgetVoidSlot)();

MainWindow::MainWindow()
{
  // create all needed objects
  // try to load settings from file
  // else set default settings

  // CREATE ALL OBJECTS
  // window and widgets size
  m_size = QSize(800,600);

  // palette
  // qRgb(120, 120, 120)
  // qRgb(240, 240, 240)
  // qRgb(20, 20, 50)
  m_palette = QPalette(QColor(qRgb(20, 20, 50)));
  m_palette.setColor(QPalette::Window, QColor(qRgb(0, 0, 20)));          // фон
  m_palette.setColor(QPalette::WindowText, QColor(qRgb(200, 200, 200))); // цвет шрифт
  m_palette.setColor(QPalette::ButtonText, QColor(qRgb(240, 240, 240))); // цвет шрифт кнопок

  // QShortcuts
  m_shortcutGunMoveLeft = new QShortcut(this);
  m_shortcutGunMoveLeft->setKey(Qt::Key_Left);
  connect(m_shortcutGunMoveLeft, SIGNAL(activated()), this, SLOT(ShortcutGunMoveLeft()));
  m_shortcutGunMoveRight = new QShortcut(this);;
  m_shortcutGunMoveRight->setKey(Qt::Key_Right);
  connect(m_shortcutGunMoveRight, SIGNAL(activated()), this, SLOT(ShortcutGunMoveRight()));
  m_shortcutGunShoot = new QShortcut(this);
  m_shortcutGunShoot->setKey(Qt::Key_Up);
  connect(m_shortcutGunShoot, SIGNAL(activated()), this, SLOT(ShortcutGunShoot()));
  m_shortcutGamePause = new QShortcut(this);
  m_shortcutGamePause->setKey(Qt::Key_Escape);
  connect(m_shortcutGamePause, SIGNAL(activated()), this, SLOT(ShortcutPause()));

  // window settings
  QIcon * icon = new QIcon("data/alien.png");
  this->setWindowIcon(*icon);
  this->setWindowTitle("Invaders Reincarnation");
  this->setMinimumSize(m_size);
  this->setWindowIconText("IR");
  this->setWindowState(Qt::WindowState::WindowActive);
  this->setPalette(m_palette);


  // FOR MAIN MENU
  // buttons
  m_pbMenuNewGame = new QPushButton("New game");
  connect(m_pbMenuNewGame, SIGNAL(clicked(bool)), this, SLOT(NewGame()));
  m_pbMenuNewGame->setToolTip("Start new game");

  m_pbMenuContinueGame = new QPushButton("Load game");
  connect(m_pbMenuContinueGame, SIGNAL(clicked(bool)), this, SLOT(ContinueOrLoadGame()));

  m_pbMenuSaveGame = new QPushButton("Save game");
  connect(m_pbMenuSaveGame, SIGNAL(clicked(bool)), this, SLOT(SaveGame()));
  m_pbMenuSaveGame->setToolTip("Save current game state to the file");

  m_pbToSet = new QPushButton("Settings");
  connect(m_pbToSet, SIGNAL(clicked(bool)), this, SLOT(CheckoutToSettings()));
  m_pbToSet->setToolTip("Move to the settings");

  m_pbExit = new QPushButton("Exit");
  connect(m_pbExit, &QAbstractButton::clicked, [this]()
      {
        if (m_gameStarted) ShowDialog("Do you want to save the current state of the game before closing?", DialogTypes::OnClose);
        this->close();
      });
  m_pbExit->setToolTip("Close program");

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

  m_layoutMenu->setMargin(20);
  m_layoutMenu->setColumnStretch(0, m_size.width()/100*30);
  m_layoutMenu->setColumnMinimumWidth(1, 225);
  m_layoutMenu->setColumnStretch(2, m_size.width()/100*30);
  m_layoutMenu->setRowStretch(0, m_size.height()/100*10);
  m_layoutMenu->setRowMinimumHeight(5, 36);
  m_layoutMenu->setRowStretch(7, m_size.height()/100*15);

  // widget
  m_widgetMenu = new QWidget(this);
  m_widgetMenu->setMinimumSize(m_size);
  m_widgetMenu->setLayout(m_layoutMenu);
  m_widgetMenu->setPalette(m_palette);

  // set current widget
  setCentralWidget(m_widgetMenu);
  m_widgetCurrent = m_widgetMenu;


  // FOR SETTINGS
  // buttons
  m_pbToMenu = new QPushButton("Menu");
  m_pbToMenu->setToolTip("Back to the main menu");
  connect(m_pbToMenu, SIGNAL(clicked(bool)), this, SLOT(CheckoutToMenu()));

  m_pbSaveSettings = new QPushButton("Save settings");
  m_pbSaveSettings->setToolTip("Save settings to data/settings.bin");
  connect(m_pbSaveSettings, SIGNAL(clicked(bool)), this, SLOT(SaveSettings()));

  m_pbLoadSettings = new QPushButton("Load settings");
  m_pbLoadSettings->setToolTip("Load settings from data/settings.bin");
  connect(m_pbLoadSettings, SIGNAL(clicked(bool)), this, SLOT(LoadSettings()));

  // QLabels
  QLabel * lControlComment = new QLabel("Control buttons:");
  QLabel * lControlGunMoveLeft = new QLabel("Gun move left button");
  QLabel * lControlGunMoveRight = new QLabel("Gun move right button");
  QLabel * lControlGunShoot = new QLabel("Button to gun shoot");
  QLabel * lControlPause = new QLabel("Game pause");

  QLabel * lGameParamComment = new QLabel("Game:");
  QLabel * lGPAliensCount = new QLabel("Count of aliens");
  QLabel * lGPObstacleCount = new QLabel("Count of obstacles");
  QLabel * lGPObstacleRedraw = new QLabel("Redraw obstacles only at first level");
  QLabel * lGPGunStartLives = new QLabel("Start gun lives count");
  QLabel * lGPGunAddLive = new QLabel("Add one life to gun at every level");

  QLabel * lScreenComment = new QLabel("Main:");
  QLabel * lWindowSize = new QLabel("Window size");
  QLabel * lWindowState = new QLabel("Window state");  
  QLabel * lLanguage = new QLabel("Language:");

  // Work with Values and Keys
    // Control


    // Game
  QSlider * slGPAliensCount = new QSlider(Qt::Horizontal);
  slGPAliensCount->setRange(25, 200);
  slGPAliensCount->setValue(55);
  //connect(cbWindowState, SIGNAL(activated(int)), this, SLOT(ChangeWindowState(int)));

  QSlider * slGPObstacleCount = new QSlider(Qt::Horizontal);
  slGPObstacleCount->setRange(0, 6);
  slGPObstacleCount->setValue(4);
  //connect(cbWindowState, SIGNAL(activated(int)), this, SLOT(ChangeWindowState(int)));

  QCheckBox * chbGPObstacleRedraw = new QCheckBox;  // сменить цвет
  chbGPObstacleRedraw->setChecked(false);
  //connect(cbWindowState, SIGNAL(activated(int)), this, SLOT(ChangeWindowState(int)));

  QSlider * slGPGunStartLives = new QSlider(Qt::Horizontal);
  slGPGunStartLives->setRange(1, 5);
  slGPGunStartLives->setValue(3);
  //connect(cbWindowState, SIGNAL(activated(int)), this, SLOT(ChangeWindowState(int)));

  QCheckBox * chbGPGunAddLive = new QCheckBox;  // сменить цвет
  chbGPGunAddLive->setChecked(true);
  //connect(cbWindowState, SIGNAL(activated(int)), this, SLOT(ChangeWindowState(int)));

    // Main
  QComboBox * cbWindowState = new QComboBox();
  cbWindowState->addItem("Full screen", GameWindowStateTypes::FullScreen);
  cbWindowState->addItem("Minimized window", GameWindowStateTypes::MinimizedWindow);
  cbWindowState->addItem("Maximized window", GameWindowStateTypes::MaximizedWindow);
  cbWindowState->setCurrentIndex(GameWindowStateTypes::MinimizedWindow);
  connect(cbWindowState, SIGNAL(activated(int)), this, SLOT(ChangeWindowState(int)));

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

  QComboBox * cbLanguage = new QComboBox();
  cbLanguage->addItem("English", GameLanguages::English);
  cbLanguage->addItem("Russian", GameLanguages::Russian);
  cbLanguage->setCurrentIndex(GameLanguages::English);
  connect(cbLanguage, SIGNAL(activated(int)), this, SLOT(ChangeLanguage(int)));

  // QHBoxLayouts

  QHBoxLayout * hbControlGunMoveLeft = new QHBoxLayout;
  hbControlGunMoveLeft->addWidget(lControlGunMoveLeft);
  QHBoxLayout * hbControlGunMoveRight = new QHBoxLayout;
  hbControlGunMoveRight->addWidget(lControlGunMoveRight);
  QHBoxLayout * hbControlGunShoot = new QHBoxLayout;
  hbControlGunShoot->addWidget(lControlGunShoot);
  QHBoxLayout * hbControlPause = new QHBoxLayout;
  hbControlPause->addWidget(lControlPause);

  QHBoxLayout * hbGPAlienCount = new QHBoxLayout;
  hbGPAlienCount->addWidget(lGPAliensCount);
  hbGPAlienCount->addWidget(slGPAliensCount);
  QHBoxLayout * hbGPObstacleCount = new QHBoxLayout;
  hbGPObstacleCount->addWidget(lGPObstacleCount);
  hbGPObstacleCount->addWidget(slGPObstacleCount);
  QHBoxLayout * hbGPObstacleRedraw = new QHBoxLayout;
  hbGPObstacleRedraw->addWidget(lGPObstacleRedraw);
  hbGPObstacleRedraw->addWidget(chbGPObstacleRedraw);
  QHBoxLayout * hbGPGunStartLives = new QHBoxLayout;
  hbGPGunStartLives->addWidget(lGPGunStartLives);
  hbGPGunStartLives->addWidget(slGPGunStartLives);
  QHBoxLayout * hbGPGunAddLive = new QHBoxLayout;
  hbGPGunAddLive->addWidget(lGPGunAddLive);
  hbGPGunAddLive->addWidget(chbGPGunAddLive);

  QHBoxLayout * hbWindowSize = new QHBoxLayout;
  hbWindowSize->addWidget(lWindowSize);
  hbWindowSize->addWidget(m_cbWindowSize);
  QHBoxLayout * hbWindowState = new QHBoxLayout;
  hbWindowState->addWidget(lWindowState);
  hbWindowState->addWidget(cbWindowState);
  QHBoxLayout * hbLanguage = new QHBoxLayout;
  hbLanguage->addWidget(lLanguage);
  hbLanguage->addWidget(cbLanguage);

  // layout
  m_layoutSettings = new QGridLayout;
  m_layoutSettings->addWidget(m_pbToMenu, 0, 0);
  m_layoutSettings->addWidget(lControlComment, 2, 0, 1, 2);
  m_layoutSettings->addLayout(hbControlGunMoveLeft, 3, 0, 1, 2);
  m_layoutSettings->addLayout(hbControlGunMoveRight, 4, 0, 1, 2);
  m_layoutSettings->addLayout(hbControlGunShoot, 5, 0, 1, 2);
  m_layoutSettings->addLayout(hbControlPause, 6, 0, 1, 2);

  m_layoutSettings->addWidget(lGameParamComment, 2, 2, 1, 2);
  m_layoutSettings->addLayout(hbGPAlienCount, 3, 2, 1, 2);
  m_layoutSettings->addLayout(hbGPObstacleCount, 4, 2, 1, 2);
  m_layoutSettings->addLayout(hbGPObstacleRedraw, 5, 2, 1, 2);
  m_layoutSettings->addLayout(hbGPGunStartLives, 6, 2, 1, 2);
  m_layoutSettings->addLayout(hbGPGunAddLive, 7, 2, 1, 2);

  m_layoutSettings->addWidget(lScreenComment, 8, 0, 1, 2);
  m_layoutSettings->addLayout(hbWindowSize, 9, 0, 1, 2);
  m_layoutSettings->addLayout(hbWindowState, 10, 0, 1, 2);
  m_layoutSettings->addLayout(hbLanguage, 11, 0, 1, 2);
  m_layoutSettings->addWidget(m_pbSaveSettings, 12, 0);
  m_layoutSettings->addWidget(m_pbLoadSettings, 12, 1);
  m_layoutSettings->addWidget(bottomFiller, 13, 0, 1, 4);

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

  // widget
  m_widgetSettings = new QWidget(this);
  m_widgetSettings->setMinimumSize(m_size);
  m_widgetSettings->setLayout(m_layoutSettings);
  m_widgetSettings->setPalette(m_palette);
  m_widgetSettings->hide();


  // GAME
  // layout

  // glwidget
  //m_glWidget = new GLWidget(this, qRgb(20, 20, 50));   // Виджет игры (окно, задний фон) (наш класс наследуемый от QOpenGLWidget и QOpenGLFunctions)
  //m_timer = new QTimer(this);                          // таймер
  //m_timer->setInterval(10);                            // период работы таймера
  //setCentralWidget(m_glWidget);                        // Главный виджет текущего окна this->setCentralWidget
  //connect(m_timer, &QTimer::timeout, m_glWidget, static_cast<QWidgetVoidSlot>(&QWidget::update));
  //m_timer->start();                                    // запуск таймера

  setFocusPolicy(Qt::StrongFocus);

  // load all user settings from file
  LoadSettings();

  // set default settings
  Resize(800,600);
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

// отображение кнопок в соответствии с текущим состоянием игры
void MainWindow::ShowMenuItems()
{
  if (m_gameStarted) m_pbMenuNewGame->hide();
  else               m_pbMenuNewGame->show();

  if (m_gameStarted)
  {
    m_pbMenuContinueGame->setText("Continue game");
    m_pbMenuContinueGame->setToolTip("Continue current game");
  }
  else
  {
    m_pbMenuContinueGame->setText("Load game");
    m_pbMenuContinueGame->setToolTip("Load game from the save file");
  }

  if (m_gameStarted) m_pbMenuSaveGame->show();
  else               m_pbMenuSaveGame->hide();  
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


// Загрузка настроек из файла, с проверкой (и корректировкой под по-умолчанию)
void MainWindow::LoadSettings()
{
  // reset flag
  m_settingsChanged = false;

}

// Сохранение настроек в файл
void MainWindow::SaveSettings()
{
  // reset flag
  m_settingsChanged = false;

}


// shortcuts  slots
void MainWindow::ShortcutGunMoveLeft()
{

}

void MainWindow::ShortcutGunMoveRight()
{

}

void MainWindow::ShortcutGunShoot()
{

}

void MainWindow::ShortcutPause()
{
  // set game pause


  if (m_widgetCurrent != m_widgetMenu) CheckoutToMenu();
}


// menu button slots
void MainWindow::NewGame()
{
  // flag set change menu
  m_gameStarted = true;
  ShowMenuItems();


}

void MainWindow::ContinueOrLoadGame()
{
  if (m_gameStarted) // Continue game
  {

  }
  else               // Load game
  {
    // flag set change menu
    m_gameStarted = true;
    ShowMenuItems();


  }
}

void MainWindow::SaveGame()
{

}

void MainWindow::CheckoutToSettings()
{
  m_widgetCurrent->hide();
  m_widgetSettings->show();
  m_widgetCurrent = m_widgetSettings;
}

void MainWindow::CheckoutToMenu()
{
  m_widgetCurrent->hide();
  m_widgetMenu->show();
  m_widgetCurrent = m_widgetMenu;

  if (m_settingsChanged) ShowDialog("Do you want to save the current settings of the game before back to the main menu?", DialogTypes::OnBackToMainFromSettings);
}

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
  // set flag
  m_settingsChanged = true;
}

void MainWindow::ChangeWindowState(int state)
{
  if (state == GameWindowStateTypes::FullScreen)
  {
    this->showFullScreen(); //setWindowState(Qt::WindowState::WindowFullScreen);
    m_cbWindowSize->setDisabled(true);
    m_cbWindowSize->setStyleSheet("QComboBox { background-color : black; color : white; }");
  }
  else if (state == GameWindowStateTypes::MinimizedWindow)
  {
    setWindowState(Qt::WindowState::WindowActive);
    m_cbWindowSize->setDisabled(false);
    m_cbWindowSize->setStyleSheet("");
    m_cbWindowSize->setPalette(m_palette);
  }
  else
  {
    setWindowState(Qt::WindowState::WindowMaximized);
    m_cbWindowSize->setDisabled(true);
    m_cbWindowSize->setStyleSheet("QComboBox { background-color : black; color : white; }");
  }
  m_size.setWidth(this->width());
  m_size.setHeight(this->height());
  // set flag
  m_settingsChanged = true;
}

void MainWindow::ChangeLanguage(int state)
{
  switch (state)
  {
    case GameLanguages::English:
    {
      // for english localization
      break;
    }
    case GameLanguages::Russian:
    {
      // для русской локализации
      break;
    }
  }
  // set flag
  m_settingsChanged = true;
}
