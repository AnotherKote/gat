#include <QComboBox>
#include <QPushButton>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QEvent>
#include <QLabel>
#include <QTextEdit>
#include <QDebug>

#include "model/ICommandsModel.hpp"
#include "model/IClientsModel.hpp"
#include "model/CommandResult.hpp"
#include "view/MainScreen.hpp"
#include "view/CommandsManager.hpp"

MainScreen::MainScreen(ICommandsModel *model, IClientsModel *clientsModel, QWidget *parent)
: QMainWindow(parent)
, m_pUserCommands(nullptr)
, m_pFire(nullptr)
, m_pManageCommands(nullptr)
, m_pClientsList(nullptr)
, m_pCommandsManager(nullptr)
, m_pCmdModel(model)
, m_pClientsModel(clientsModel)
, m_pResultedCommandName(nullptr)
, m_pResult(nullptr)
{
   createWidgets();
   connectSignalAndSlots();
   fillUserCommandsList();
   refillClientsList();

   m_pClientsList->setSelectionMode(QAbstractItemView::ExtendedSelection); //QAbstractItemView::MultiSelection

   QHBoxLayout *pButtonsAndComboBox = new QHBoxLayout();
   pButtonsAndComboBox->addWidget(m_pUserCommands, 3);
   pButtonsAndComboBox->addWidget(m_pFire, 2);
   pButtonsAndComboBox->addWidget(m_pManageCommands, 0);

   QVBoxLayout *pLeftSideLayout = new QVBoxLayout();
   pLeftSideLayout->addLayout(pButtonsAndComboBox);
   pLeftSideLayout->addWidget(m_pResultedCommandName);
   pLeftSideLayout->addWidget(m_pResult);

   QHBoxLayout *pMainLayout = new QHBoxLayout();
   pMainLayout->addLayout(pLeftSideLayout, 2);
   pMainLayout->addWidget(m_pClientsList, 1);

   QWidget *centralWidget = new QWidget();
   centralWidget->setLayout(pMainLayout);
   setCentralWidget(centralWidget);

   resetTexts();
   setMinimumSize(QSize(640,480)); //TODO get rid of the magic numbers
}

void MainScreen::buttonManageCommandsPressed()
{
   qDebug() << "pressed";
   m_pCommandsManager->open();
}

void MainScreen::slotFire()
{
   if(!m_pUserCommands->currentText().isEmpty())
   {
      QList<QListWidgetItem*> selectedItems = m_pClientsList->selectedItems();
      QStringList selectedTexts;
      for(QListWidgetItem* item: selectedItems)
      {
         selectedTexts.append(item->text());
      }
      if(selectedTexts.count() > 0)
      {
         emit fireCommand(m_pUserCommands->currentText(), selectedTexts);
      }
   }
}

void MainScreen::clientResultChanged(QString clientName)
{
   qDebug() << "Client result changed" << clientName;
   CommandResult result = m_pClientsModel->getResultForClient(clientName);
   QList<QListWidgetItem*> items = m_pClientsList->findItems(clientName, Qt::MatchExactly);
   if(items.size() == 1)
   {
      QListWidgetItem *item = items.first();
      item->setBackgroundColor((result.successful) ? Qt::green : Qt::red);
   } else {
      qDebug() << tr("Something terrible happen. Please contact developers.");
   }
   if(clientName == m_pClientsList->currentItem()->text())
   {
      currentSelectedClientChanged(clientName);
   }
}

bool MainScreen::event(QEvent *event)
{
   if (event->type() == QEvent::LanguageChange)
   {
      resetTexts();
   }
   return QMainWindow::event(event);
}

void MainScreen::currentSelectedClientChanged(QString clientName)
{
   m_pResult->clear();
   m_pResultedCommandName->setText("");
   CommandResult result = m_pClientsModel->getResultForClient(clientName);
   m_pResultedCommandName->setText(result.cmdName);
   qDebug() << "in";
   m_pResult->addItems(result.result);
   qDebug() << "out";
   if(m_pResultedCommandName->text().isEmpty())
   {
      m_pResultedCommandName->setText(tr("No commands was send to this client."));
   }
   if(m_pResult->count() == 0)
   {
      m_pResult->addItem(tr("No result output."));
   }
}

void MainScreen::fillUserCommandsList()
{
   qDebug();
   m_pUserCommands->clear();
   qDebug() << m_pCmdModel->userCommandsList().size();
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
   m_pResultedCommandName = new QLabel(this);
   m_pResult = new QListWidget(this);

}

void MainScreen::connectSignalAndSlots()
{
   qDebug();
   connect(m_pManageCommands, &QPushButton::clicked, this, &MainScreen::buttonManageCommandsPressed);
   connect(dynamic_cast<QObject*>(m_pCmdModel), SIGNAL(userCommandsListChanged()), this, SLOT(fillUserCommandsList()));
   connect(dynamic_cast<QObject*>(m_pClientsModel), SIGNAL(clientListChanged()), this, SLOT(refillClientsList()));
   connect(dynamic_cast<QObject*>(m_pClientsModel), SIGNAL(clientResultReady(QString)), this, SLOT(clientResultChanged(QString)));
   connect(m_pFire, &QPushButton::clicked, this, &MainScreen::slotFire);
   connect(m_pClientsList, &QListWidget::currentTextChanged, this, &MainScreen::currentSelectedClientChanged);
}

void MainScreen::resetTexts()
{
   m_pFire->setText(tr("Fire", "Fire command to clients"));
   m_pManageCommands->setText(tr("Manage commands", "Open user commands manager"));
}
