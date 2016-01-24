#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QComboBox>
#include <QPushButton>
#include <QTextEdit>
#include <QListWidget>
#include <QLineEdit>
#include <QLabel>
#include <QResizeEvent>
#include <QMessageBox>
#include <QSettings>

#include "view/ExtendParametrEdit.hpp"
#include "view/CommandsManager.hpp"
#include "model/ICommandsModel.hpp"
#include <QDebug>

CommandsManager::CommandsManager(ICommandsModel *cmdModel, QWidget *parent)
: QDialog(parent)
, m_pParent(parent)
, m_pAbstractCommands(nullptr)
, m_pCommandNameLabel(nullptr)
, m_pUserCommandName(nullptr)
, m_pParameterName(nullptr)
, m_pParameterData(nullptr)
, m_pParameterDataList()
, m_pExtendedParameterDataEdit(nullptr)
, m_pNewCommand(nullptr)
, m_pSaveCommand(nullptr)
, m_pRemoveCommand(nullptr)
, m_pUserCommandsList(nullptr)
, m_pCommandDescription(nullptr)
, m_pExtendedParameterEditDialog(nullptr)
, m_pCmdModel(cmdModel)
, m_pSettings(nullptr)
, m_folderName("UserCommands")
, m_cmdAbstractName("Command")

{
   createWidgets();
   m_pSettings = new QSettings(this);
   resetTexts();
   connectSignalAndSlots();
   refillAbstractCommandsList();
   refillParameterNamesList();
   refillUserCommandsList();
   refillCommandDescription();
   loadSettings();

   m_pExtendedParameterDataEdit->setIcon(QIcon(":/icons/edit.png"));
   m_pCommandDescription->setReadOnly(true);

   QHBoxLayout *pSecondRowLayout = new QHBoxLayout;
   pSecondRowLayout->addWidget(m_pCommandNameLabel);
   pSecondRowLayout->addWidget(m_pUserCommandName);

   QHBoxLayout *pThirdRowLayout = new QHBoxLayout;
   pThirdRowLayout->addWidget(m_pParameterName, 1);
   pThirdRowLayout->addWidget(m_pParameterData, 1);
   pThirdRowLayout->addWidget(m_pExtendedParameterDataEdit);

   QHBoxLayout *pFourthRowLayout = new QHBoxLayout;
   pFourthRowLayout->addWidget(m_pNewCommand);
   pFourthRowLayout->addWidget(m_pSaveCommand);
   pFourthRowLayout->addWidget(m_pRemoveCommand);

   QVBoxLayout *pLeftSideLayout = new QVBoxLayout;
   pLeftSideLayout->addWidget(m_pAbstractCommands);
   pLeftSideLayout->addLayout(pSecondRowLayout);
   pLeftSideLayout->addLayout(pThirdRowLayout);
   pLeftSideLayout->addLayout(pFourthRowLayout);
   pLeftSideLayout->addWidget(m_pUserCommandsList);

   QHBoxLayout *pMainLayout = new QHBoxLayout;
   pMainLayout->addLayout(pLeftSideLayout);
   pMainLayout->addWidget(m_pCommandDescription);


   setMinimumSize(QSize(600, 400));
   setLayout(pMainLayout);
}

void CommandsManager::openExtendedParameterEditDialog()
{
   qDebug();
   m_pExtendedParameterEditDialog->setData(m_pAbstractCommands->currentText(),
                                           m_pParameterName->currentText(),
                                           m_pParameterData->text());
   m_pExtendedParameterEditDialog->open();
}

void CommandsManager::extendedDialogResult(int result)
{
   qDebug() << "( result : " << result << ")";
   if(result == QDialog::Accepted)
   {
      m_pParameterData->setText(m_pExtendedParameterEditDialog->getParameterData());
      saveParameterData();
   }
}

void CommandsManager::refillAbstractCommandsList()
{
   qDebug();
   m_pAbstractCommands->clear();
   for(auto *it: m_pCmdModel->abstractCommandsList())
   {
      m_pAbstractCommands->addItem(it->getName());
   }
}

void CommandsManager::refillParameterNamesList(QString)
{
   qDebug();
   m_pParameterName->clear();
   m_pParameterName->addItems(QList<QString>::fromVector(m_pCmdModel->commandParameterNames(m_pAbstractCommands->currentText())));
   if(m_pParameterName->count() == 0)
   {
      m_pParameterName->setEnabled(false);
      m_pParameterData->setEnabled(false);
      m_pExtendedParameterDataEdit->setEnabled(false);
   } else
   {
      m_pParameterName->setEnabled(true);
      m_pParameterData->setEnabled(true);
      m_pExtendedParameterDataEdit->setEnabled(true);
   }
}

void CommandsManager::createParameterDataList(QString)
{
   qDebug();
   m_pParameterData->clear();
   m_pParameterDataList.clear();
   for (int i = 0; i < m_pParameterName->count(); ++i)
   {
      m_pParameterDataList.append("");
   }
}

void CommandsManager::fillParameterDataList(QStringList dataList)
{
   qDebug() << " ( dataList : " << dataList << " )";
   m_pParameterData->clear();
   m_pParameterDataList.clear();
   m_pParameterDataList = dataList;
}

void CommandsManager::manageParameterData(int index)
{
   qDebug() << " ( index:" << index << " )";
   if(m_pParameterDataList.size() == 0)
   {
      return;
   }

   if(index >= 0 && index < m_pParameterDataList.size())
   {
      m_pParameterData->setText(m_pParameterDataList.at(index));
   }
}

void CommandsManager::saveParameterData()
{
   qDebug();
   m_pParameterDataList[m_pParameterName->currentIndex()] = m_pParameterData->text();
}

void CommandsManager::refillUserCommandsList()
{
   qDebug();
   m_pUserCommandsList->clear();
   m_pUserCommandsList->addItems(m_pCmdModel->userCommandsList());
}

void CommandsManager::saveCommand()
{
   qDebug();
   if(m_pUserCommandName->text().isEmpty())
   {
      message(tr("Command name is empty!"));
      return;
   }

   int index = 0;
   for(QString data: m_pParameterDataList)
   {
      if(data.isEmpty())
      {
         message(tr("Parameter \"%1\" is empty!").arg(m_pParameterName->itemText(index)));
         return;
      }
      index++;
   }
   QString errorMessage;
   if(!m_pCmdModel->saveUserCommand(m_pUserCommandName->text(),
                                m_pAbstractCommands->currentText(),
                                QVector<QString>::fromList(m_pParameterDataList),
                                errorMessage))
   {
      message(errorMessage);
   }
}

void CommandsManager::message(QString message)
{
   qDebug() << "( message : " << message << " )";
   QMessageBox::information(this, tr("Info", "Message box info"), message);
}

void CommandsManager::loadCommand(QString userCmdName)
{
   qDebug() << "( userCmdName : " << userCmdName << " )";
   if(userCmdName.isEmpty())
   {
      //clear everything?
      return;
   }
   const ICommand *currentCommand = m_pCmdModel->getUserCommand(userCmdName);

   if(!currentCommand)
   {
      qCritical() << " Can't get command \"" << userCmdName << "\" from model.";
      message(tr("Some internal error occured. Please, save log file and send it to developers."));
      return;
   }

   //set abstract command
   int currentAbstractCommandIndex = m_pAbstractCommands->findText(currentCommand->getName());
   if(currentAbstractCommandIndex == -1)
   {
      qCritical() << " Can't get index of abstract command \"" << userCmdName <<"\". Search for \"" << currentCommand->getName() <<"\"";
      message(tr("Some internal error occured. Please, save log file and send it to developers."));
      return;
   }
   m_pAbstractCommands->setCurrentIndex(currentAbstractCommandIndex);

   //fill parameter data
   fillParameterDataList(QStringList::fromVector(currentCommand->getParametersData()));
   manageParameterData(m_pParameterName->currentIndex());

   //fill name
   m_pUserCommandName->clear();
   m_pUserCommandName->setText(userCmdName);
}

void CommandsManager::removeCommand(QString userCmdName)
{
   m_pCmdModel->removeCommand(userCmdName);
}

void CommandsManager::clearAll()
{
   m_pAbstractCommands->setCurrentIndex(0);
   m_pUserCommandName->clear();
   m_pParameterData->clear();
}

void CommandsManager::refillCommandDescription(QString currentAbstractCommand)
{
   qDebug() << " ( currentAbstractCommand : " << currentAbstractCommand << " )";
   if(currentAbstractCommand.isEmpty())
   {
      currentAbstractCommand = m_pAbstractCommands->currentText();
   }
   m_pCommandDescription->clear();
   m_pCommandDescription->setText(m_pCmdModel->commandDescription(currentAbstractCommand));
}

void CommandsManager::showEvent(QShowEvent *)
{
   qDebug();
   //TODO set min size ();
   resize(m_pParent->width()/2, m_pParent->height()/2);
   move((m_pParent->x() + m_pParent->width()/2) - width()/2,
        (m_pParent->y() + m_pParent->height()/2) - height()/2);
}

void CommandsManager::createWidgets()
{
   m_pAbstractCommands = new QComboBox;

   m_pCommandNameLabel = new QLabel;
   m_pUserCommandName = new QLineEdit;

   m_pParameterName = new QComboBox;
   m_pParameterData = new QLineEdit;
   m_pExtendedParameterDataEdit = new QPushButton;

   m_pNewCommand = new QPushButton;
   m_pSaveCommand = new QPushButton;
   m_pRemoveCommand = new QPushButton;

   m_pUserCommandsList = new QListWidget;

   m_pCommandDescription = new QTextEdit;

   m_pExtendedParameterEditDialog = new ExtendParametrEdit(this);
}

void CommandsManager::connectSignalAndSlots()
{
   connect(m_pExtendedParameterDataEdit, &QPushButton::clicked, this, &CommandsManager::openExtendedParameterEditDialog);
   connect(m_pExtendedParameterEditDialog, &QDialog::finished, this, &CommandsManager::extendedDialogResult);

   connect(m_pAbstractCommands, &QComboBox::currentTextChanged, this, &CommandsManager::refillParameterNamesList);
   connect(m_pAbstractCommands, &QComboBox::currentTextChanged, this, &CommandsManager::createParameterDataList);
   connect(m_pAbstractCommands, &QComboBox::currentTextChanged, this, &CommandsManager::refillCommandDescription);

   connect(m_pParameterName, SIGNAL(currentIndexChanged(int)), this, SLOT(manageParameterData(int)));
   connect(m_pParameterData, &QLineEdit::editingFinished, this, &CommandsManager::saveParameterData);
   connect(dynamic_cast<QObject*>(m_pCmdModel), SIGNAL(userCommandsListChanged()), this, SLOT(refillUserCommandsList()));

   connect(m_pUserCommandsList, &QListWidget::currentTextChanged, this, &CommandsManager::loadCommand);

   //buttons
   connect(m_pSaveCommand, &QPushButton::clicked, this, &CommandsManager::saveCommand);
   connect(m_pNewCommand, &QPushButton::clicked, this, &CommandsManager::clearAll);
   connect(m_pRemoveCommand, &QPushButton::clicked, this, [&](){
      auto selectedItems = m_pUserCommandsList->selectedItems();
      if(selectedItems.count() > 0)
      {
         removeCommand(selectedItems.front()->text());
      }
   });
   connect(this, &CommandsManager::finished, this, &CommandsManager::saveSettings);

   //   connect(m_pAbstractCommands, &QComboBox::currentTextChanged, [&](QString index){
//      qDebug() << "int " << index;
//   });
}

void CommandsManager::resetTexts()
{
   qDebug();
   m_pCommandNameLabel->setText(tr("Command name: "));
   m_pNewCommand->setText(tr("New", "create new command"));
   m_pSaveCommand->setText(tr("Save", "Save command"));
   m_pRemoveCommand->setText(tr("Remove", "Remove command"));
}

void CommandsManager::saveSettings()
{
   qDebug();
   m_pSettings->remove(m_folderName);
   m_pSettings->beginGroup(m_folderName);
   for(QString userCmd: m_pCmdModel->userCommandsList())
   {
      const ICommand *curCmd = m_pCmdModel->getUserCommand(userCmd);
      if(curCmd && (curCmd->getParameterNames().size() == curCmd->getParametersData().size()))
      {
         m_pSettings->beginGroup(userCmd);
         m_pSettings->setValue(m_cmdAbstractName, curCmd->getName());
         for(int i = 0; i < curCmd->getParameterNames().size(); i++)
         {
            m_pSettings->setValue(curCmd->getParameterNames().at(i),
                                  curCmd->getParametersData().at(i));
         }
         m_pSettings->endGroup();
      }
   }
   m_pSettings->endGroup();
}

void CommandsManager::loadSettings()
{
   qDebug();
   m_pSettings->beginGroup(m_folderName);
   for(QString userCmdName: m_pSettings->childGroups())
   {
      m_pSettings->beginGroup(userCmdName);
      QString cmdName;
      QVector<QString> parameters;
      cmdName = m_pSettings->value(m_cmdAbstractName).toString();
      if(!cmdName.isEmpty())
      {
         for(QString parameterName: m_pCmdModel->commandParameterNames(cmdName))
         {
            QString parameterData = m_pSettings->value(parameterName).toString();
            if(!parameterData.isEmpty())
            {
               parameters.push_back(parameterData);
            }else
            {
               qWarning() << "Empty parameter";
            }
         }
         QString errorMessage;
         qDebug() << "load command: " << userCmdName;
         qDebug() << "Abstract command: " << cmdName;
         qDebug() << "parameters: " << parameters;
         if(!m_pCmdModel->saveUserCommand(userCmdName,
                                      cmdName,
                                      parameters,
                                      errorMessage))
         {
            message(errorMessage);
         }

      }
      m_pSettings->endGroup();
   }
   m_pSettings->endGroup();
}
