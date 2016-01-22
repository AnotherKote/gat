#include "SystemTray.hpp"

#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QApplication>

SystemTray::SystemTray(QWidget *parent)
: QLabel(parent)
, m_pSystemTray(nullptr)
, m_pSystemTrayMenu(nullptr)
{
   m_pSystemTray = new QSystemTrayIcon(this);
   m_pSystemTrayMenu = new QMenu(this);

   QAction *quit = new QAction (tr("Quit"), this);
   connect(quit, &QAction::triggered, qApp, &QApplication::quit);

   m_pSystemTrayMenu->addAction(quit);
   m_pSystemTray->setContextMenu(m_pSystemTrayMenu);
   m_pSystemTray->setToolTip("GAT Client");
   m_pSystemTray->setIcon(QIcon(":/icons/clients.png"));
   m_pSystemTray->showMessage("title", "message");
   m_pSystemTray->show();
}

