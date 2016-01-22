#ifndef COMMANDRESULT_H
#define COMMANDRESULT_H

#include <QString>

struct CommandResult
{
   QString cmdName;
   QStringList result;
   bool successful;
   CommandResult()
   : cmdName("")
   , result(QStringList())
   , successful(false)
   {}
   CommandResult(QString cmdName, QStringList result, bool successful)
   : cmdName(cmdName)
   , result(result)
   , successful(successful)
   {}

};

#endif // COMMANDRESULT_H
