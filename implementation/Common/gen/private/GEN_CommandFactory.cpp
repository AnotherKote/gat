#include <QVector>

#include "Common/gen/GEN_CommandFactory.hpp"
#include "Common/gen/GEN_CommandsHelper.hpp"
#include <QDebug>
#include "Common/Commands/CmdGetProcessList.hpp"
#include "Common/Commands/CmdShowMessage.hpp"

GEN_CommandFactory::GEN_CommandFactory()
: m_pHelper(nullptr)
{
   m_pHelper = new GEN_CommandsHelper;
}

ICommand *GEN_CommandFactory::createCommand(QString cmdName, QVector<QString> parameters)
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
   return retCommand;
}

