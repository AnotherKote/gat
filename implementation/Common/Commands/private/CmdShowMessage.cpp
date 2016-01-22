#include <QObject>
#include "Common/Commands/CmdShowMessage.hpp"

#ifdef CLIENT
#include "Client/windows/WinExecutor.hpp"
#endif

CmdShowMessage::CmdShowMessage(QObject *parent)
: ICommand("Show message box",
           QVector<QString> {"Message Header", "Message", "Duration(s)"},
           parent)
{
   resetTexts();
#ifdef CLIENT
   m_pExecutor = new WinExecutor;
#endif
}

#ifdef CLIENT
bool CmdShowMessage::execute()
{
   if(m_parameterNames.size() == m_parameterData.size())
   {
      bool ok = false;
      int duration = m_parameterData[E_DURATION].toInt(&ok);
      if(ok)
      {
         m_pExecutor->showMessage(m_parameterData[E_HEADER],
                                  m_parameterData[E_MESSAGE],
                                  duration);
         return true;
      } else
      {
         m_error = tr("Duration parameter is not integer");
         return false;
      }
   } else
   {
      m_error = tr("Command execution error. m_parameterNames.size() != m_parameterData.size()");
      return false;
   }
}
#endif

void CmdShowMessage::resetTexts()
{
   m_description = tr("Show message on remote machine. \n"
                   "First parameter is message header. \n"
                   "Second parameter is message to display. \n"
                   "Third parameter is time (seconds) during which message will be displayed. \n");
}

