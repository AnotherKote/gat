#include "Common/CommandHelper.hpp"

CommandHelper::CommandHelper()
: m_availableCommandsNames()
, m_emptyVector()
, m_emptyString("")
{}

void CommandHelper::addCommand(QString name, std::function<ICommand *()> factoryMethod)
{
   commands.insert(name, factoryMethod);
   m_availableCommands.append(factoryMethod());
}

CommandHelper::~CommandHelper()
{
   for(auto *icommand: m_availableCommands)
   {
      delete icommand;
   }
   m_availableCommands.clear();
}

const QVector<QString> &CommandHelper::getCommandParameterNames(QString cmdName) const
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

const QString &CommandHelper::getCommandDescription(QString cmdName) const
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

#ifdef CLIENT
IExecutableCommand *CommandHelper::createCommand(QString cmdName, QVector<QString> parameters) const
#else
ICommand *CommandHelper::createCommand(QString cmdName, QVector<QString> parameters) const
#endif
{
   ICommand* ptr = nullptr;

   auto iter = commands.find(cmdName);
   if(iter != commands.end())
   {
      ptr = iter.value()();
      if(!ptr->setParameters(parameters))
      {
         qWarning() << "Can't set parameters for command::" << ptr->getName();
//         delete ptr;
         ptr->deleteLater();
         ptr = nullptr;
      }
   }
#ifdef CLIENT
   return dynamic_cast<IExecutableCommand*>(ptr);
#else
   return ptr;
#endif
}
