#include "Common/Commands/CmdIsProcessRunning.hpp"
#ifdef CLIENT
#include "Client/windows/WinExecutor.hpp"
#endif

CmdIsProcessRunning::CmdIsProcessRunning(QObject *parent)
: ICommand("Is process running",
           QVector<QString>{"Process Name"},
           parent)
{
   resetTexts();
#ifdef CLIENT
   m_pExecutor = new WinExecutor;
#endif
}

void CmdIsProcessRunning::resetTexts()
{
   m_description = tr("Returns true if process is running otherwise returns false.");
}

#ifdef CLIENT
bool CmdIsProcessRunning::execute()
{
   QString split = "::::";
   m_pExecutor->getRunningProcessesList(m_results, m_error, split);
   for(QString nameAndPid: m_results)
   {
      QString processName = nameAndPid.split(split).first();
      if(processName.compare(m_parameterData.first(), Qt::CaseInsensitive) == 0)
      {
         m_results.clear();
         m_results.append("Process " + processName + " is running.");
         return true;
      }
   }
   m_error = "No process " + m_parameterData.first() + " found.";
   return false;
}
#endif
