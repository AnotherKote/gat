#include "Common/gen/GEN_CommandsHelper.hpp"

#include "Common/Commands/CmdGetProcessList.hpp"
#include "Common/Commands/CmdShowMessage.hpp"
#include "Common/Commands/CmdIsProcessRunning.hpp"
#include "Common/Commands/CmdKillProcessByName.hpp"

GEN_CommandsHelper::GEN_CommandsHelper()
: m_availableCommands()
, m_availableCommadsNames()
, m_emptyVector()
{
   m_availableCommands.append(new CmdGetProcessList);
   m_availableCommands.append(new CmdShowMessage);
   m_availableCommands.append(new CmdIsProcessRunning);
   m_availableCommands.append(new CmdKillProcessByName);

   for(auto it: m_availableCommands)
   {
      m_availableCommadsNames.push_back(it->getName());
   }
}

GEN_CommandsHelper::~GEN_CommandsHelper()
{
   for(auto *icommand: m_availableCommands)
   {
      delete icommand;
   }
   m_availableCommands.clear();
}

const QVector<QString> &GEN_CommandsHelper::getCommandParameterNames(QString cmdName)
{
   auto it = std::find_if(m_availableCommands.begin(),
                          m_availableCommands.end(),
                          [&](ICommand*cmd){
                             return (cmd->getName().compare(cmdName) == 0);
                          });
   if(it != m_availableCommands.end())
   {
      return (*it)->getParameterNames();
   } else
   {
      return m_emptyVector;
   }
}

const QString &GEN_CommandsHelper::getCommandDescription(QString cmdName)
{
   auto it = std::find_if(m_availableCommands.begin(),
                          m_availableCommands.end(),
                          [&](ICommand*cmd){
                             return (cmd->getName().compare(cmdName) == 0);
                          });
   if(it != m_availableCommands.end())
   {
      return (*it)->getDescription();
   } else
   {
      return m_emptyString;
   }
}
