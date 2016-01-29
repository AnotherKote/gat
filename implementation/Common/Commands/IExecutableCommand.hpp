#ifndef IEXECUTABLECOMMAND_H
#define IEXECUTABLECOMMAND_H

#include <QStringList>
#include "Common/Commands/ICommand.hpp"

class WinExecutor; //TODO interface

class IExecutableCommand : public ICommand
{
protected:
   WinExecutor *m_pExecutor;
   QStringList m_results;
   QString m_error;

public:
   IExecutableCommand(const QString name,
                       const QVector<QString> parameterNames,
                       QObject *parent = 0)
      : ICommand(name, parameterNames, parent){}
   virtual bool execute() = 0;
   const QStringList &results() { return m_results; }
   const QString &errorMessage() { return m_error; }
};

#endif // IEXECUTABLECOMMAND_H
