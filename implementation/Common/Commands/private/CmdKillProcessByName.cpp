#include "Common/Commands/CmdKillProcessByName.hpp"
#ifdef CLIENT
#include "Client/windows/WinExecutor.hpp"
#endif

CmdKillProcessByName::CmdKillProcessByName(QObject *parent)
: ICommand("Kill process by name",
           QVector<QString>{"Process Name"},
           parent)
{
   resetTexts();
#ifdef CLIENT
   m_pExecutor = new WinExecutor;
#endif
}

void CmdKillProcessByName::resetTexts()
{
   m_description = tr("Kill process by it's name. If more then one process with that name, only one will be killed.");
}

#ifdef CLIENT
bool CmdKillProcessByName::execute()
{
   return m_pExecutor->killProcessByName(m_parameterData.first(), m_error);
}
#endif
