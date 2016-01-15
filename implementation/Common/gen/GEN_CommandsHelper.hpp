#ifndef GEN_COMMANDSHELPER_H
#define GEN_COMMANDSHELPER_H

#include <QString>
#include <QVector>

#include "Common/Commands/ICommand.hpp"

class GEN_CommandsHelper
{
   QVector<ICommand *> m_availableCommands;
   QVector<QString> m_availableCommadsNames;
   const QVector<QString> m_emptyVector;
   const QString m_emptyString;
public:
   GEN_CommandsHelper();
   ~GEN_CommandsHelper();

   //TODO remove getAvailableCommands. Replace it with one of the other getters.
   const QVector<ICommand *> & getAvailableCommands() const { return m_availableCommands; }
   const QVector<QString> & getAvailableCommandsNames() { return m_availableCommadsNames; }
   const QVector<QString> & getCommandParameterNames(QString cmdName);
   const QString & getCommandDescription(QString cmdName);
};

#endif // GEN_COMMANDSHELPER_H
