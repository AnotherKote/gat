#include <QComboBox>
#include <QPushButton>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QEvent>
#include <model/ICommandsModel.hpp>
#include <model/IClientsModel.hpp>

#include "view/MainScreen.hpp"
#include "view/CommandsManager.hpp"
#include <QDebug>

MainScreen::MainScreen(ICommandsModel *model, IClientsModel *clientsModel, QWidget *parent)
: QMainWindow(parent)
, m_pUserCommands(nullptr)
, m_pFire(nullptr)
, m_pManageCommands(nullptr)
, m_pClientsList(nullptr)
, m_pCommandsManager(nullptr)
, m_pCmdModel(model)
, m_pClientsModel(clientsModel)
{
   createWidgets();
   fillUserCommandsList();
   refillClientsList();

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
   qDebug() << "pressed";
   m_pClientsModel->addClient("abfadfas;lfkaf");
   m_pClientsModel->addClient("abfadfas;lfkaf");
   m_pClientsModel->addClient("abfadfas;lfkaf1");
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

void MainScreen::fillUserCommandsList()
{
   m_pUserCommands->clear();
   m_pUserCommands->addItems(m_pCmdModel->userCommandsList());
}

void MainScreen::refillClientsList()
{
   m_pClientsList->clear();
   m_pClientsList->addItems(m_pClientsModel->getClientsNames());
}

void MainScreen::createWidgets()
{
   m_pUserCommands = new QComboBox(this);
   m_pFire = new QPushButton(this);
   m_pManageCommands = new QPushButton(this);
   m_pClientsList = new QListWidget(this);
   m_pCommandsManager = new CommandsManager(m_pCmdModel, this);
}

void MainScreen::connectSignalAndSlots()
{
   connect(m_pManageCommands, &QPushButton::clicked, this, &MainScreen::buttonManageCommandsPressed);
   connect(dynamic_cast<QObject*>(m_pCmdModel), SIGNAL(userCommandsListChanged()), this, SLOT(fillUserCommandsList()));
   connect(dynamic_cast<QObject*>(m_pClientsModel), SIGNAL(clientListChanged()), this, SLOT(refillClientsList()));
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
