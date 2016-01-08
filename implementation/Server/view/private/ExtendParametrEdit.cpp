#include <QLabel>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>

#include "view/ExtendParametrEdit.hpp"

ExtendParametrEdit::ExtendParametrEdit(QWidget *parent)
: QDialog(parent)
, m_pCommandName(nullptr)
, m_pParameterName(nullptr)
, m_pParameterData(nullptr)
, m_pAcceptButton(nullptr)
, m_pCancelButton(nullptr)
{
   createWidgets();

   QHBoxLayout *pButtonsLayout = new QHBoxLayout;
   pButtonsLayout->addSpacing(1);
   pButtonsLayout->addWidget(m_pAcceptButton);
   pButtonsLayout->addSpacing(1);
   pButtonsLayout->addWidget(m_pCancelButton);
   pButtonsLayout->addSpacing(1);

   QVBoxLayout *pMainLayout = new QVBoxLayout;
   pMainLayout->addWidget(m_pCommandName);
   pMainLayout->addWidget(m_pParameterName);
   pMainLayout->addWidget(m_pParameterData);
   pMainLayout->addLayout(pButtonsLayout);

   connectSignalAndSlots();
   resetTexts();
   setLayout(pMainLayout);
   setMinimumSize(QSize(320, 240));
}

void ExtendParametrEdit::createWidgets()
{
   m_pCommandName = new QLabel;
   m_pParameterName = new QLabel;
   m_pParameterData = new QTextEdit;
   m_pAcceptButton = new QPushButton;
   m_pCancelButton = new QPushButton;
}

void ExtendParametrEdit::resetTexts()
{
   m_pAcceptButton->setText(tr("Accept", "text for Accept button"));
   m_pCancelButton->setText(tr("Cancel", "text for Cancel button"));
}

void ExtendParametrEdit::connectSignalAndSlots()
{
   connect(m_pAcceptButton, &QPushButton::clicked, this, &ExtendParametrEdit::accept);
   connect(m_pCancelButton, &QPushButton::clicked, this, &ExtendParametrEdit::reject);
}

void ExtendParametrEdit::setData(QString commandName, QString parameterName, QString parameterData)
{
   m_pCommandName->setText(commandName);
   m_pParameterName->setText(parameterName);
   m_pParameterData->setText(parameterData);
}

QString ExtendParametrEdit::getParameterData()
{
   return m_pParameterData->toPlainText();
}
