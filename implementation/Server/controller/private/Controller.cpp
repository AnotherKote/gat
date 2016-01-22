#include "controller/Controller.hpp"
#include "controller/private/Server.hpp"
#include "view/MainScreen.hpp"
#include "model/IClientsModel.hpp"
#include "model/ICommandsModel.hpp"
#include "model/Model.hpp"
#include "Common/ProtocolManager.hpp"
#include "model/CommandResult.hpp"

Controller::Controller(QObject *parent)
: QObject(parent)
, m_pClientsModel(nullptr)
, m_pCommandsModel(nullptr)
, m_pView(nullptr)
, m_pServer(nullptr)
{
   Model *pMainModel = new Model(this);
   m_pClientsModel = static_cast<IClientsModel*>(pMainModel);
   m_pCommandsModel = static_cast<ICommandsModel*>(pMainModel);
   m_pView = new MainScreen(pMainModel, pMainModel);
   m_pServer = new Server(this);

   connectSignalAndSlots();
}

void Controller::connectSignalAndSlots()
{
   connect(m_pServer, &Server::signalNewConnection, this, &Controller::slotNewConnection);
   connect(m_pServer, &Server::signalDisconnect, this, &Controller::slotDisconnect);
   connect(m_pView, &MainScreen::fireCommand, this, &Controller::slotFireCommand);
   connect(m_pServer, &Server::signalMessageReceived, this, &Controller::slotDataReceived);
}

Controller::~Controller()
{
   m_pView->deleteLater();
}

void Controller::show()
{
   m_pView->show();
}

void Controller::slotNewConnection(QString name)
{
   m_pClientsModel->addClient(name);
}

void Controller::slotDisconnect(QString name)
{
   m_pClientsModel->removeClient(name);
}

void Controller::slotFireCommand(QString userCmdName, QStringList users)
{
   ProtocolManager protocolManager;
   const ICommand* cmd = m_pCommandsModel->getUserCommand(userCmdName);
   for(QString user: users)
   {
      m_pServer->slotSendToClient(user, protocolManager.encodeCommand(cmd));
   }
}

void Controller::slotDataReceived(QString name, QString data)
{
   ProtocolManager protocolManager;
   QStringList result;
   bool successful;
   QString error;
   QString cmd;
   if(protocolManager.decodeResult(data, cmd, result, successful, error))
   {
      CommandResult cmdResult(cmd, result, successful);
      m_pClientsModel->setResultsForClient(name, cmdResult);
      qDebug() << "result: "   << result;
      qDebug() << "successful:" << successful;
      qDebug() << "cmdName:" << cmd;
   } else {
      qDebug() << "error: " << error;
   }

}
