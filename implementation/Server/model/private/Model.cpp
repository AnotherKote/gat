#include "Server/model/Model.hpp"

#include <QDebug>

Model::Model(QObject *parent)
: QObject(parent)
, ICommandsModel()
, IClientsModel()
, m_userCommandsList()
, m_clientsList()
, m_connectedClients()
, m_helper(CommandHelper::instance())
{
}

Model::~Model()
{
}

bool Model::saveUserCommand(QString userCmdName, QString cmdName, QVector<QString> parameters, QString &errorMessage)
{
   qDebug() << userCmdName << cmdName << parameters;
   bool ret = false;
   ICommand* command = nullptr;
   if(m_userCommandsList.keys().contains(userCmdName))
   {
      errorMessage = tr("Unable to create command \"%1\". Name is already in use.").arg(userCmdName);
   } else
   {
      command = m_helper.createCommand(cmdName, parameters);
      if(command)
      {
         m_userCommandsList.insert(userCmdName, command);
         ret = true;
         emit userCommandsListChanged();
      } else
      {
         errorMessage = tr("Unable to create command \"%1\". Factory screwed up.").arg(userCmdName);
      }
   }
   return ret;
}

const QVector<ICommand *> &Model::abstractCommandsList() const
{
   return m_helper.getAvailableCommands();
}

const QString Model::commandDescription(QString cmdName) const
{
   return m_helper.getCommandDescription(cmdName);
}

const QList<QString> Model::userCommandsList() const
{
   return m_userCommandsList.keys();
}

const ICommand * Model::getUserCommand(QString userCmdName) const
{
   qDebug() << " ( userCmdName : " << userCmdName << " )";
   ICommand * ret = nullptr;
   if(m_userCommandsList.contains(userCmdName))
   {
      ret = m_userCommandsList.value(userCmdName);
   }
   return ret;
}


const QVector<QString> &Model::commandParameterNames(QString cmdName) const
{
   return m_helper.getCommandParameterNames(cmdName);
}

bool Model::removeCommand(QString cmdName)
{
   int ret  = 0 ;
   ret = m_userCommandsList.remove(cmdName);
   qDebug() << "removed command retvalue : " << ret;
   emit userCommandsListChanged();
   return (ret > 0);
}


void Model::addClient(QString name)
{
   qDebug() << " ( name : " << name << " )";

   if(m_clientsList.keys().contains(name))
   {
      qWarning() << "Unable to add client \"" << name << "\". Already in list";
   } else
   {
      m_clientsList.insert(name, CommandResult());
      emit clientListChanged();
   }
}

void Model::removeClient(QString name)
{
   m_clientsList.remove(name);
   emit clientListChanged();
}

bool Model::changeClientName(QString oldName, QString newName)//TODO move to view.
{
   Q_UNUSED(oldName);
   Q_UNUSED(newName);
   Q_ASSERT_X(false, "Model::changeClientName", "NOT implemented yet!");
   return false;
}

void Model::setResultsForClient(QString clientName, CommandResult result)
{
   if(m_clientsList.keys().contains(clientName))
   {
      m_clientsList[clientName] = result;
      emit clientResultReady(clientName);
   } else
   {
      qWarning() << " No \"" << clientName << "\" in list.";
   }
}

const CommandResult Model::getResultForClient(QString clientName) const
{
   return m_clientsList.value(clientName);
}

const QStringList Model::getClientsNames()
{
   return m_clientsList.keys();
}
