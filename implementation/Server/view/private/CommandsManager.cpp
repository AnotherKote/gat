#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QComboBox>
#include <QPushButton>
#include <QTextEdit>
#include <QListWidget>
#include <QLineEdit>
#include <QLabel>

#include "view/ExtendParametrEdit.hpp"
#include "view/CommandsManager.hpp"
#include <QDebug>

CommandsManager::CommandsManager(QWidget *parent)
: QDialog(parent)
, m_pParent(parent)
, m_pAbstractCommands(nullptr)
, m_pCommandNameLabel(nullptr)
, m_pUserCommandName(nullptr)
, m_pParameterName(nullptr)
, m_pParameterData(nullptr)
, m_pExtendedParameterDataEdit(nullptr)
, m_pNewCommand(nullptr)
, m_pSaveCommand(nullptr)
, m_pRemoveCommand(nullptr)
, m_pUserCommandsList(nullptr)
, m_pCommandDescription(nullptr)
, m_pExtendedParameterEditDialog(nullptr)
{
   createWidgets();
   resetTexts();
   connectSignalAndSlots();

   m_pExtendedParameterDataEdit->setIcon(QIcon(":/icons/edit.png"));

   m_pCommandDescription->setText("Some text Some text Some text Some text Some text Some text Some text Some text Some text Some text Some text Some text Some text Some text Some text Some text Some text Some text Some text Some text Some text Some text Some text Some text Some text Some text Some text Some text Some text Some text Some text Some text Some text Some text Some text Some text Some text Some text Some text Some text Some text Some text Some text ");
   m_pCommandDescription->setReadOnly(true);

   QHBoxLayout *pSecondRowLayout = new QHBoxLayout;
   pSecondRowLayout->addWidget(m_pCommandNameLabel);
   pSecondRowLayout->addWidget(m_pUserCommandName);

   QHBoxLayout *pThirdRowLayout = new QHBoxLayout;
   pThirdRowLayout->addWidget(m_pParameterName);
   pThirdRowLayout->addWidget(m_pParameterData);
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
   m_pExtendedParameterEditDialog->setData(m_pAbstractCommands->currentText(),
                                           m_pParameterName->currentText(),
                                           m_pParameterData->text());
   m_pExtendedParameterEditDialog->open();
}

void CommandsManager::extendedDialogResult(int result)
{
   if(result == QDialog::Accepted)
   {
      m_pParameterData->setText(m_pExtendedParameterEditDialog->getParameterData());
   }
}

void CommandsManager::showEvent(QShowEvent *)
{
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
}

void CommandsManager::resetTexts()
{
   m_pCommandNameLabel->setText(tr("Command name: "));
   m_pNewCommand->setText(tr("New", "create new command"));
   m_pSaveCommand->setText(tr("Save", "Save command"));
   m_pRemoveCommand->setText(tr("Remove", "Remove command"));
}
