#ifndef CMDISPROCESSRUNNING_H
#define CMDISPROCESSRUNNING_H

#include "Common/Commands/ICommand.hpp"

#ifdef CLIENT
#include "Common/Commands/IExecutableCommand.hpp"
#endif

class CmdIsProcessRunning
#ifdef CLIENT
   : public IExecutableCommand
#else
   : public ICommand
#endif
{
   Q_OBJECT

   void resetTexts();
public:
   CmdIsProcessRunning(QObject *parent = 0);

#ifdef CLIENT
   // IExecutableCommand interface
public:
   virtual bool execute() override;
#endif
};

#endif // CMDISPROCESSRUNNING_H
