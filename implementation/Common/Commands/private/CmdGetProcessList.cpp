#include "Common/Commands/CmdGetProcessList.hpp"

#ifdef CLIENT
#include "Client/windows/WinExecutor.hpp"
#endif

CmdGetProcessList::CmdGetProcessList(QObject *parent)
: ICommand("Get process list",
           QVector<QString>(),
           parent)
{
   resetTexts();
#ifdef CLIENT
   m_pExecutor = new WinExecutor;
#endif
}

void CmdGetProcessList::resetTexts()
{
   m_description = tr("Gets running process list from remote machine");
}

#ifdef CLIENT
bool CmdGetProcessList::execute()
{
   return m_pExecutor->getRunningProcessesList(m_results, m_error);
}
#endif

///TODO static macros init
