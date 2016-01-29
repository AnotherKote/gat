#ifndef MODEL_H
#define MODEL_H

#include "Common/Commands/ICommand.hpp"
#include "Server/model/ICommandsModel.hpp"
#include "Server/model/IClientsModel.hpp"
#include "Common/CommandHelper.hpp"

#include <QObject>
#include <QMap>
#include <QList>
#include <QVector>

//#include <QSharedPointer> //TODO

class CommandHelper;

class Model : public QObject,  public ICommandsModel, public IClientsModel
{
   Q_OBJECT

   QMap<QString, ICommand*> m_userCommandsList;
   QMap<QString, CommandResult> m_clientsList;
   QList<QString> m_connectedClients;
   const CommandHelper &m_helper;

public:
   Model(QObject *parent = 0);
   virtual ~Model() override;

   // ICommandsModel interface
public:
   virtual bool saveUserCommand(QString userCmdName,
                                QString cmdName,
                                QVector<QString> parameters,
                                QString &errorMessage) override;
   virtual const QVector<ICommand *> &abstractCommandsList() const override;
   virtual const QString commandDescription(QString cmdName) const override;
   virtual const QList<QString> userCommandsList() const override;
   virtual const ICommand * getUserCommand(QString userCmdName) const override;
   virtual const QVector<QString> &commandParameterNames(QString cmdName) const override;
   virtual bool removeCommand(QString cmdName) override;
signals:
   void userCommandsListChanged();


   // IClientsModel interface
public:
   virtual void addClient(QString name) override;
   virtual void removeClient(QString name) override;
   virtual bool changeClientName(QString oldName, QString newName) override;
   virtual void setResultsForClient(QString clientName, CommandResult result) override;
   virtual const CommandResult getResultForClient(QString clientName) const override;
   virtual const QStringList getClientsNames() override;

signals:
   void clientListChanged();
   void clientResultReady(QString client);
};

#endif // MODEL_H
