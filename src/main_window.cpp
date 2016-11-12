#include <iostream>
#include "main_window.hpp"

//#include "gl_widget.hpp"

//typedef void (QWidget::*QWidgetVoidSlot)();

MainWindow::MainWindow()
{
  // load settings from file
  LoadSettings();
  MoveWindowToCenter();

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
        if (m_gameStarted) ShowDialog("Do you want to save the current state of the game before closing?");
        this->close();
      });
  m_pbExit->setToolTip("Close program");

  // default button settings (game not started)
  ShowMenuItems();

  // fillers
  QWidget *topFiller = new QWidget;
  topFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  QWidget *bottomFiller = new QWidget;
  bottomFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  // main menu layout
  m_layoutMenu = new QGridLayout;
  m_layoutMenu->addWidget(topFiller, 0, 0, 1, 3);
  m_layoutMenu->addWidget(m_pbMenuNewGame, 1, 1, 1, 1);
  m_layoutMenu->addWidget(m_pbMenuContinueGame, 2, 1, 1, 1);
  m_layoutMenu->addWidget(m_pbMenuSaveGame, 3, 1, 1, 1);
  m_layoutMenu->addWidget(m_pbToSet, 4, 1, 1, 1);
  m_layoutMenu->addWidget(m_pbExit, 5, 1, 1, 1);
  m_layoutMenu->addWidget(bottomFiller, 6, 0, 1, 3);

  m_layoutMenu->setMargin(20);
  m_layoutMenu->setColumnStretch(0, m_size.width()/100*30);
  m_layoutMenu->setColumnStretch(1, m_size.width()/100*40);
  m_layoutMenu->setColumnStretch(2, m_size.width()/100*30);
  m_layoutMenu->setRowStretch(0, m_size.height()/100*10);
  m_layoutMenu->setRowStretch(4, m_size.height()/100*5);
  m_layoutMenu->setRowStretch(6, m_size.height()/100*15);

  // widget
  m_widgetMenu = new QWidget(this);
  m_widgetMenu->setMinimumSize(m_size);
  m_widgetMenu->setLayout(m_layoutMenu);
  setCentralWidget(m_widgetMenu);
  // set current widget
  m_widgetCurrent = m_widgetMenu;


  // FOR SETTINGS
  // buttons
  m_pbToMenu = new QPushButton("Menu");
  m_pbToMenu->setToolTip("Click on this button to back to the main menu");
  connect(m_pbToMenu, SIGNAL(clicked(bool)), this, SLOT(CheckoutToMenu()));

  m_pbSaveSettings = new QPushButton("Save settings");
  m_pbSaveSettings->setToolTip("Click on this button to save settings to data/settings.bin");
  connect(m_pbSaveSettings, SIGNAL(clicked(bool)), this, SLOT(SaveSettings()));

  m_pbLoadSettings = new QPushButton("Load settings");
  m_pbLoadSettings->setToolTip("Click on this button to load settings from data/settings.bin");
  connect(m_pbLoadSettings, SIGNAL(clicked(bool)), this, SLOT(LoadSettings()));

  // QLabels
  QLabel * lControls = new QLabel;
  lControls->setText("Controls:");
  QLabel * lControlGunMoveLeft = new QLabel;
  lControlGunMoveLeft->setText("Button to gun move left: ");
  QLabel * lControlGunMoveRight = new QLabel;
  lControlGunMoveRight->setText("Button to gun move right:");
  QLabel * lControlGunShoot = new QLabel;
  lControlGunShoot->setText("Button to gun shoot:     ");
  QLabel * lControlPause = new QLabel;
  lControlPause->setText("Game pause:              ");
  QLabel * lResolution = new QLabel;
  lResolution->setText("Resolution:              ");

  // Work with Values and Keys
  // NOT RELEASED

  // QHBoxLayouts
  m_controlGunMoveLeft = new QHBoxLayout;
  m_controlGunMoveLeft->addWidget(lControlGunMoveLeft);

  m_controlGunMoveRight = new QHBoxLayout;
  m_controlGunMoveRight->addWidget(lControlGunMoveRight);

  m_controlGunShoot = new QHBoxLayout;
  m_controlGunShoot->addWidget(lControlGunShoot);

  m_controlPause = new QHBoxLayout;
  m_controlPause->addWidget(lControlPause);

  m_resolution = new QHBoxLayout;
  m_resolution->addWidget(lResolution);


  // layout
  m_layoutSettings = new QGridLayout;
  m_layoutSettings->addWidget(m_pbToMenu, 0, 0);
  //m_layoutSettings->addWidget(topFiller, 1, 0, 1, 3);
  m_layoutSettings->addLayout(m_controlGunMoveLeft, 2, 0, 1, 2);
  m_layoutSettings->addLayout(m_controlGunMoveRight, 3, 0, 1, 2);
  m_layoutSettings->addLayout(m_controlGunShoot, 4, 0, 1, 2);
  m_layoutSettings->addLayout(m_controlPause, 5, 0, 1, 2);
  m_layoutSettings->addLayout(m_resolution, 6, 0, 1, 2);
  m_layoutSettings->addWidget(m_pbSaveSettings, 7, 0);
  m_layoutSettings->addWidget(m_pbLoadSettings, 7, 1);
  m_layoutSettings->addWidget(bottomFiller, 8, 0, 1, 3);

  m_layoutSettings->setMargin(20);
  m_layoutSettings->setRowStretch(0, m_size.height()/100*10);

  m_layoutSettings->setRowStretch(8, m_size.height()/100*15);

  // widget
  m_widgetSettings = new QWidget(this);
  m_widgetSettings->setMinimumSize(m_size);
  m_widgetSettings->setLayout(m_layoutSettings);
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

  if (m_gameStarted) m_pbMenuContinueGame->setText("Continue game");
  else               m_pbMenuContinueGame->setText("Load game");

  if (m_gameStarted) m_pbMenuSaveGame->show();
  else               m_pbMenuSaveGame->hide();
}

// Предлагает сохранить игру -> вызывает SaveGame в случае подтверждения пользователем
void MainWindow::ShowDialog(QString const & msg)
{
  //std::cout << msg.toStdString() << std::endl;
}

// Загрузка настроек из файла, с проверкой (и корректировкой под по-умолчанию)
void MainWindow::LoadSettings()
{
  // from /data/settings.bin
  m_size = QSize(0,0);


  // default в случае ошибок и временно
  m_size.setWidth(800);
  m_size.setHeight(600);
}

// Сохранение настроек в файл
void MainWindow::SaveSettings()
{

}

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
}
