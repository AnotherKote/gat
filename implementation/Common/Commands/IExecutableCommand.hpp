#ifndef IEXECUTABLECOMMAND_H
#define IEXECUTABLECOMMAND_H

#include <QStringList>

class WinExecutor; //TODO interface

class IExecutableCommand
{
protected:
   WinExecutor *m_pExecutor;
   QStringList m_results;
   QString m_error;

public:
   virtual bool execute() = 0;
   const QStringList &results() { return m_results; }
   const QString &errorMessage() { return m_error; }
};

#endif // IEXECUTABLECOMMAND_H
