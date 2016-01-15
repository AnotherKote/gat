#include <QObject>
#include "Common/Commands/CmdShowMessage.hpp"

CmdShowMessage::CmdShowMessage(QObject *parent)
: ICommand("Show message box",
           QVector<QString> {"Message Header", "Message", "Duration(s)"},
           parent)
{
   resetTexts();
}

void CmdShowMessage::resetTexts()
{
   m_description = tr("Show message on remote machine. \n"
                   "First parameter is message header. \n"
                   "Second parameter is message to display. \n"
                   "Third parameter is time (seconds) during which message will be displayed. \n");
}

