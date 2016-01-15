#include "Common/Commands/CmdGetProcessList.hpp"

CmdGetProcessList::CmdGetProcessList(QObject *parent)
: ICommand("Get process list",
           QVector<QString>(),
           parent)
{
   resetTexts();
}

void CmdGetProcessList::resetTexts()
{
   m_description = tr("Gets running process list from remote machine");
}


///TODO static macros init
