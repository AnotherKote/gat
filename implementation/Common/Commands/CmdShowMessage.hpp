#ifndef CMDSHOWMESSAGE_H
#define CMDSHOWMESSAGE_H

#include "Common/Commands/ICommand.hpp"

class CmdShowMessage : public ICommand
{
   Q_OBJECT

   void resetTexts();
public:
   explicit CmdShowMessage(QObject *parent = 0);
};

#endif // CMDSHOWMESSAGE_H
