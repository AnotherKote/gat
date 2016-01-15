#ifndef CMDGETPROCESSLIST_H
#define CMDGETPROCESSLIST_H

#include "Common/Commands/ICommand.hpp"

class CmdGetProcessList : public ICommand
{
   Q_OBJECT

   void resetTexts();
public:
   explicit CmdGetProcessList(QObject *parent = 0);
};

#endif // CMDGETPROCESSLIST_H
