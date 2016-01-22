#ifndef MODEL_H
#define MODEL_H

#include "Common/Commands/ICommand.hpp"

#include <QObject>
#include <QMap>
#include <QList>
#include <QVector>
#include <Server/model/ICommandsModel.hpp>
#include <Server/model/IClientsModel.hpp>
//#include <QSharedPointer> //TODO

class GEN_CommandsHelper;
class GEN_CommandFactory;

class Model : public QObject,  public ICommandsModel, public IClientsModel
{
   Q_OBJECT

   QMap<QString, ICommand*> m_userCommandsList;
   QMap<QString, CommandResult> m_clientsList;
   QList<QString> m_connectedClients;
   GEN_CommandFactory *m_pFactory;
   GEN_CommandsHelper *m_pHelper;

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
