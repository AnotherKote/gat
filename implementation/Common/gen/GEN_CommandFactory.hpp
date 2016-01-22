#ifndef GEN_COMMANDFACTORY_H
#define GEN_COMMANDFACTORY_H

#include <QString>

//#ifndef CLIENT
//;
//#endif

#ifdef CLIENT
class IExecutableCommand;
#else
class ICommand;
#endif

class GEN_CommandsHelper;

class GEN_CommandFactory
{
   GEN_CommandsHelper *m_pHelper;
public:
   GEN_CommandFactory();

#ifdef CLIENT
   IExecutableCommand* createCommand(QString cmdName, QVector<QString> parameters);
#else
   ICommand* createCommand(QString cmdName, QVector<QString> parameters);
#endif

};

#endif // GEN_COMMANDFACTORY_H
