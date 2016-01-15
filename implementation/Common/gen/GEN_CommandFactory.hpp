#ifndef GEN_COMMANDFACTORY_H
#define GEN_COMMANDFACTORY_H

#include <QString>

class ICommand;
class GEN_CommandsHelper;

class GEN_CommandFactory
{
   GEN_CommandsHelper *m_pHelper;
public:
   GEN_CommandFactory();

   ICommand* createCommand(QString cmdName, QVector<QString> parameters);
};

#endif // GEN_COMMANDFACTORY_H
