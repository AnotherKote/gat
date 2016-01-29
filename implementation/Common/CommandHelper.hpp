#ifndef COMMANDHELPER_H
#define COMMANDHELPER_H

#include <type_traits>
#include <functional>
#include <QMap>

#include "Commands/ICommand.hpp"

#ifdef CLIENT
#include "Commands/IExecutableCommand.hpp"
#endif
template<class T>
class _command_registration;

class CommandHelper
{
   QVector<ICommand *> m_availableCommands;
   QVector<QString> m_availableCommandsNames;
   const QVector<QString> m_emptyVector;
   const QString m_emptyString;

   QMap< QString, std::function<ICommand*()> > commands;
   void addCommand(QString name, std::function<ICommand*()>factoryMethod);

   CommandHelper();
   Q_DISABLE_COPY(CommandHelper)
public:
   ~CommandHelper();
   template<class T>
   friend class _command_registration;

   //TODO remove getAvailableCommands. Replace it with one of the other getters.
   const QVector<ICommand *> & getAvailableCommands() const { return m_availableCommands; }
   const QVector<QString> & getAvailableCommandsNames() const { return m_availableCommandsNames; }
   const QVector<QString> & getCommandParameterNames(QString cmdName) const;
   const QString & getCommandDescription(QString cmdName) const;

#ifdef CLIENT
   IExecutableCommand* createCommand(QString cmdName, QVector<QString> parameters) const;
#else
   ICommand* createCommand(QString cmdName, QVector<QString> parameters) const;
#endif

   static CommandHelper& instance()
   {
      static CommandHelper object;
      return object;
   }
};

template<class T>
class _command_registration
{
public:
   _command_registration()
   {
      static_assert(std::is_base_of<ICommand, T>::value,
                    "inherit ICommand to use registration");
      T inst;
#ifdef CLIENT
      static_assert(std::is_base_of<IExecutableCommand, T>::value,
                    "inherit IExecutableCommand to use registration");
#endif
      CommandHelper::instance().addCommand(inst.getName(), [](){return new T;});
   }
};

#define REGISTER_COMMAND(T) \
   static _command_registration<T> \
   _command_registration_##T;

#endif // COMMANDHELPER_H
