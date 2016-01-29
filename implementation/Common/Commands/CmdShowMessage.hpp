#ifndef CMDSHOWMESSAGE_H
#define CMDSHOWMESSAGE_H

#include "Common/Commands/ICommand.hpp"

#ifdef CLIENT
#include "Common/Commands/IExecutableCommand.hpp"
#endif

class CmdShowMessage
#ifdef CLIENT
   : public IExecutableCommand
#else
   : public ICommand
#endif
{
   Q_OBJECT

   void resetTexts();

   enum E_PARAMETERS
   {
      E_HEADER = 0,
      E_MESSAGE,
      E_DURATION
   };

public:
   explicit CmdShowMessage(QObject *parent = 0);
#ifdef CLIENT
   // IExecutableCommand interface
public:
   virtual bool execute() override;
#endif

};

#endif // CMDSHOWMESSAGE_H
