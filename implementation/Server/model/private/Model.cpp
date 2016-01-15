#include "Server/model/Model.hpp"
#include "Common/gen/GEN_CommandFactory.hpp"
#include "Common/gen/GEN_CommandsHelper.hpp"

#include <QDebug>

Model::Model(QObject *parent)
: QObject(parent)
, ICommandsModel()
, IClientsModel()
, m_userCommandsList()
, m_clientsList()
, m_connectedClients()
, m_pFactory(nullptr)
, m_pHelper(nullptr)
{
   m_pFactory = new GEN_CommandFactory;
   m_pHelper = new GEN_CommandsHelper;
   if(!m_pFactory || !m_pHelper)
   {
      qFatal("Unable to create factory or helper.");
      //      m_pFactory = nullptr;
   }
}

Model::~Model()
{
   delete m_pFactory;
   delete m_pHelper;
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
      command = m_pFactory->createCommand(cmdName, parameters);
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
   return m_pHelper->getAvailableCommands();
}

const QString Model::commandDescription(QString cmdName) const
{
   return m_pHelper->getCommandDescription(cmdName);
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
   return m_pHelper->getCommandParameterNames(cmdName);
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
      m_clientsList.insert(name, "");
   }
   emit clientListChanged();
}

void Model::removeClient(QString name)
{
   m_clientsList.remove(name);
   emit clientListChanged();
}

bool Model::changeClientName(QString oldName, QString newName)//TODO move to view.
{
   if(m_clientsList.keys().contains(oldName) && !m_clientsList.keys().contains(newName))
   {
      QString clientResult = m_clientsList.take(oldName);
      if(m_clientsList.remove(oldName) > 0)
      {
         qWarning() << "Unable to remove client \"" << oldName << "\" from clients map.";
         return false;
      }
      m_clientsList.insert(newName, clientResult);
   } else
   {
      qWarning() << " Name \"" << newName << "\" is already in use";
      return false;
   }
}

void Model::setResultsForClient(QString clientName, QString result)
{
   if(m_clientsList.keys().contains(clientName))
   {
      m_clientsList[clientName] = result;
   } else
   {
      qWarning() << " No \"" << clientName << "\" in list.";
   }
}

const QStringList Model::getClientsNames()
{
   return m_clientsList.keys();
}
