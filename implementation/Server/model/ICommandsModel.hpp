#ifndef ICOMMANDSMODEL_H
#define ICOMMANDSMODEL_H

#include "Common/Commands/ICommand.hpp"

#include <QVector>
#include <QString>

class ICommandsModel
{

public:
//   ICommandsModel(QObject *parent = 0):QObject(parent) {}
//   virtual ~ICommandsModel() = 0 {}
   virtual const QVector<ICommand *> &abstractCommandsList() const = 0;
   virtual const QString commandDescription(QString cmdName) const = 0;
   virtual bool saveUserCommand(QString userCmdName,
                                QString cmdName,
                                QVector<QString> parameters,
                                QString &errorMessage) = 0;
   virtual const QList<QString> userCommandsList() const = 0;
   virtual const ICommand* getUserCommand(QString userCmdName) const = 0;
   virtual const QVector<QString> &commandParameterNames(QString cmdName) const = 0;
   virtual bool removeCommand(QString cmdName) = 0;

   virtual void userCommandsListChanged() = 0;
};
//Q_DECLARE_INTERFACE(ICommandsModel, "ICommandsModel")
#endif // ICOMMANDSMODEL_H
