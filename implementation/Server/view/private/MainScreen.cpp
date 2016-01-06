#include <QComboBox>
#include <QPushButton>
#include <QVBoxLayout>

#include "view/MainScreen.hpp"
#include <QDebug>

MainScreen::MainScreen(QWidget *parent)
: QMainWindow ( parent )
{
   createWidgets();
   QVBoxLayout *layout = new QVBoxLayout(this);
   layout->addWidget(m_pFire);
   layout->addWidget(m_pUserCommands);
   layout->addWidget(m_pManageCommands);
   layout->addWidget(m_pFire);
   QWidget *centralWidget = new QWidget(this);
   centralWidget->setLayout(layout);
   setCentralWidget(centralWidget);
   setText();

   connect(m_pFire, &QPushButton::clicked, [&](){
      if(m_pUserCommands->currentIndex() % 2 == 0)
      {
         translateToEnglish();
      } else
      {
         translateToRussian();
      }
   });
}

void MainScreen::createWidgets()
{
   m_pUserCommands = new QComboBox(this);
   m_pFire = new QPushButton(this);
   m_pManageCommands = new QPushButton(this);
}

void MainScreen::setText()
{
   qDebug() << "setText";
   m_pFire->setText(tr("Fire", "Fire command to clients"));
   m_pManageCommands->setText(tr("Manager commands", "Open user commands manager"));

   int curIndex = 0;
   if(m_pUserCommands->count() > 0)
   {
      curIndex = m_pUserCommands->currentIndex();
      m_pUserCommands->clear();
   }

   m_pUserCommands->addItem(tr("English"));
   m_pUserCommands->addItem(tr("Russian"));
   m_pUserCommands->setCurrentIndex(curIndex);
}

//<debug>
#include <QTranslator>
//</debug>

void MainScreen::setTranslator(QTranslator *translator)
{
   m_pTranslator = translator;
}

void MainScreen::translateToEnglish()
{
   qDebug() << "to english " << m_pTranslator->load("main_en.qm","D:/dev/gat/implementation/Server");
   setText();
}

void MainScreen::translateToRussian()
{
   qDebug() << "to russian " << m_pTranslator->load("main_ru.qm","D:/dev/gat/implementation/Server");
   setText();
}


