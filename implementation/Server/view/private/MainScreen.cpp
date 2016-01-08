#include <QComboBox>
#include <QPushButton>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QEvent>

#include "view/MainScreen.hpp"
#include "view/CommandsManager.hpp"
#include <QDebug>

MainScreen::MainScreen(QWidget *parent)
: QMainWindow(parent)
, m_pUserCommands(nullptr)
, m_pFire(nullptr)
, m_pManageCommands(nullptr)
, m_pClientsList(nullptr)
, m_pCommandsManager(nullptr)
{
   createWidgets();

   QHBoxLayout *pButtonsAndComboBox = new QHBoxLayout();
   pButtonsAndComboBox->addWidget(m_pUserCommands, 3);
   pButtonsAndComboBox->addWidget(m_pFire, 2);
   pButtonsAndComboBox->addWidget(m_pManageCommands, 0);

   QGridLayout *pMainLayout = new QGridLayout();
   pMainLayout->addLayout(pButtonsAndComboBox, 0, 0, 1, 4);
   pMainLayout->addWidget(m_pClientsList, 0, 5, 10, 2);

   QWidget *centralWidget = new QWidget();
   centralWidget->setLayout(pMainLayout);
   setCentralWidget(centralWidget);

   connectSignalAndSlots();
   resetTexts();
   setMinimumSize(QSize(640,480)); //TODO get rid of the magic numbers
}

void MainScreen::buttonManageCommandsPressed()
{
   m_pCommandsManager->open();
}

bool MainScreen::event(QEvent *event)
{
   if (event->type() == QEvent::LanguageChange)
   {
      resetTexts();
   }
   return QMainWindow::event(event);
}

void MainScreen::createWidgets()
{
   m_pUserCommands = new QComboBox(this);
   m_pFire = new QPushButton(this);
   m_pManageCommands = new QPushButton(this);
   m_pClientsList = new QListWidget(this);
   m_pCommandsManager = new CommandsManager(this);
}

void MainScreen::connectSignalAndSlots()
{
   connect(m_pManageCommands, &QPushButton::clicked, this, &MainScreen::buttonManageCommandsPressed);
}

void MainScreen::resetTexts()
{
   int curListIndex = 0;

   m_pFire->setText(tr("Fire", "Fire command to clients"));
   m_pManageCommands->setText(tr("Manage commands", "Open user commands manager"));

   if(m_pUserCommands->count() > 0)
   {
      curListIndex = m_pUserCommands->currentIndex();
      m_pUserCommands->clear();
   }

   m_pUserCommands->setCurrentIndex(curListIndex);
   curListIndex = 0;
}
