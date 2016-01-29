#include "Invoker.hpp"
#include "NetworkManager.hpp"
#include "windows/WinExecutor.hpp"
#include "Common/ProtocolManager.hpp"
#include "Common/Commands/IExecutableCommand.hpp"

#include <QDebug>

Invoker::Invoker(QObject *parent)
: QObject(parent)
, m_pNetworkManager(nullptr)
, m_pProtocolManager(nullptr)
, m_helper(CommandHelper::instance())
{
   m_pNetworkManager = new NetworkManager(this);
   m_pProtocolManager = new ProtocolManager(this);

   connect(m_pNetworkManager, &NetworkManager::signalDataReceived, this, &Invoker::slotMessageFromServer);
}

Invoker::~Invoker()
{
}

void Invoker::run(QString host, int port, int recconectionInterval)
{
   m_pNetworkManager->start(host, port, recconectionInterval);
}

void Invoker::slotMessageFromServer(QString message)
{
   QString cmdName;
   QVector<QString> parameters;
   QString error;
   if(m_pProtocolManager->decodeCommand(message, cmdName, parameters, error))
   {
      IExecutableCommand *cmd = m_helper.createCommand(cmdName, parameters);
      if(cmd)
      {
         QString cmdResultData;
         if(cmd->execute())
         {
            cmdResultData = m_pProtocolManager->encodeResult(cmdName, cmd->results(), true);
         }
         else
         {
            QStringList result;
            result.append(cmd->errorMessage());
            cmdResultData = m_pProtocolManager->encodeResult(cmdName, result, false);
            qDebug() << "Can't execute command " << cmdName << ". Command returned false." << cmd->errorMessage();
         }
         m_pNetworkManager->slotSendToServer(cmdResultData);
      } else
      {
         qDebug() << "Can't create command. Factory returned nullptr.";
      }
   }else
   {
      qDebug() <<" Error while decoding message from server. " << error;
   }
}

