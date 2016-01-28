#include <QVector>

#include "Common/gen/GEN_CommandFactory.hpp"
#include "Common/gen/GEN_CommandsHelper.hpp"
#include <QDebug>
#include "Common/Commands/CmdGetProcessList.hpp"
#include "Common/Commands/CmdShowMessage.hpp"
#include "Common/Commands/CmdIsProcessRunning.hpp"
#include "Common/Commands/CmdKillProcessByName.hpp"

GEN_CommandFactory::GEN_CommandFactory()
: m_pHelper(nullptr)
{
   m_pHelper = new GEN_CommandsHelper;
}

#ifdef CLIENT
IExecutableCommand *GEN_CommandFactory::createCommand(QString cmdName, QVector<QString> parameters)
#else
ICommand *GEN_CommandFactory::createCommand(QString cmdName, QVector<QString> parameters)
#endif
{
   qDebug() << cmdName << parameters;
   ICommand *retCommand = nullptr;
   auto it = std::find_if(m_pHelper->getAvailableCommands().begin(),
                          m_pHelper->getAvailableCommands().end(),
                          [&](ICommand*cmd){
                             return (cmd->getName().compare(cmdName) == 0);
                          });
   if(it != m_pHelper->getAvailableCommands().end())
   {
      if(cmdName.compare("Show message box") == 0)
      {
         retCommand = new CmdShowMessage();
      } else if(cmdName.compare("Get process list")  == 0)
      {
         retCommand = new CmdGetProcessList();
      } else if(cmdName.compare("Is process running")  == 0)
      {
         retCommand = new CmdIsProcessRunning();
      } else if(cmdName.compare("Kill process by name") == 0)
      {
         retCommand = new CmdKillProcessByName();
      }

      if(!retCommand->setParameters(parameters))
      {
         qWarning() << "Can't set parameters for command::" << retCommand->getName();
         retCommand->deleteLater();
         retCommand = nullptr;
      }
   } else
   {
      qDebug() << "Can't create command " << cmdName << ". No such abstract command";
      return nullptr;
   }
#ifdef CLIENT
   return dynamic_cast<IExecutableCommand*>(retCommand);
#else
   return retCommand;
#endif
}

