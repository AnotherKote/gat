#ifndef ICLIENTSMODEL_H
#define ICLIENTSMODEL_H

#include <QString>
#include <QStringList>
#include "model/CommandResult.hpp"

class IClientsModel
{
public:
   virtual void addClient(QString name) = 0;
   virtual void removeClient(QString name) = 0;
   virtual bool changeClientName(QString oldName, QString newName) = 0;
   virtual void setResultsForClient(QString clientName, CommandResult result) = 0;
   virtual const QStringList getClientsNames() = 0;
   virtual const CommandResult getResultForClient(QString clientName) const = 0;
   virtual void clientListChanged() = 0;
   virtual void clientResultReady(QString client) = 0;
};

#endif // ICLIENTSMODEL_H
