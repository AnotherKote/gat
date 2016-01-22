#ifndef CMDGETPROCESSLIST_H
#define CMDGETPROCESSLIST_H

#include "Common/Commands/ICommand.hpp"

#ifdef CLIENT
#include "Common/Commands/IExecutableCommand.hpp"
#endif

class CmdGetProcessList
      : public ICommand
#ifdef CLIENT
      , public IExecutableCommand
#endif
{
   Q_OBJECT

   void resetTexts();
public:
   explicit CmdGetProcessList(QObject *parent = 0);

#ifdef CLIENT
   // IExecutableCommand interface
public:
   virtual bool execute() override;
#endif

};

#endif // CMDGETPROCESSLIST_H
