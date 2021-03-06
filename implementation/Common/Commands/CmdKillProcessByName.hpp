#ifndef CMDKILLPROCESSBYNAME_H
#define CMDKILLPROCESSBYNAME_H

#include "Common/Commands/ICommand.hpp"

#ifdef CLIENT
#include "Common/Commands/IExecutableCommand.hpp"
#endif

class CmdKillProcessByName
#ifdef CLIENT
   : public IExecutableCommand
#else
   : public ICommand
#endif
{
   Q_OBJECT

   void resetTexts();
public:
   CmdKillProcessByName(QObject *parent = 0);

#ifdef CLIENT
   // IExecutableCommand interface
public:
   virtual bool execute() override;
#endif

};

#endif // CMDKILLPROCESSBYNAME_H
