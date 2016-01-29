#include "Common/Commands/CmdGetProcessList.hpp"
#include "Common/CommandHelper.hpp"

#ifdef CLIENT
#include "Client/windows/WinExecutor.hpp"
#endif

CmdGetProcessList::CmdGetProcessList(QObject *parent)
#ifdef CLIENT
: IExecutableCommand
#else
: ICommand
#endif
  ("Get process list",
           QVector<QString>(),
           parent)
{
   resetTexts();
#ifdef CLIENT
   m_pExecutor = new WinExecutor;
#endif
}

REGISTER_COMMAND(CmdGetProcessList)

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
