#include <QApplication>
#include <QStringList>
//#include <QString>
#include <QDebug>

#include "Common/gen/GEN_CommandFactory.hpp"
#include "Common/Commands/ICommand.hpp"
#include "Common/Commands/IExecutableCommand.hpp"
#include "Invoker.hpp"
#include "SystemTray.hpp"
#include "windows/WinExecutor.hpp"
#include "NetworkManager.hpp"
#include "Common/ProtocolManager.hpp"

void myMessageOutput(QtMsgType type, const QString &msg)
{
   QByteArray localMsg = msg.toLocal8Bit();
   switch (type) {
   case QtDebugMsg:
      fprintf(stderr, "%s", localMsg.constData());
   break;
   case QtInfoMsg:
      fprintf(stderr, "%s", localMsg.constData());
   break;
   case QtWarningMsg:
      fprintf(stderr, "%s", localMsg.constData());
   break;
   case QtCriticalMsg:
      fprintf(stderr, "%s", localMsg.constData());
   break;
   case QtFatalMsg:
      fprintf(stderr, "%s", localMsg.constData());
      //flush
      abort();
   }
   return;
}

int main(int argc, char *argv[])
{
   QApplication client(argc, argv);

   qSetMessagePattern("[%{time process}] %{function}(line:%{line})\t%{message}"); //      qInstallMessageHandler(myMessageOutput);

   SystemTray systemTray;
   Q_UNUSED(systemTray);

   Invoker invoker;
   invoker.run("localhost", 10001, 1000);
//   Q_UNUSED(invoker);
//   NetworkManager netManager("localhost", 10000);

//   ICommand *cmd = dynamic_cast<ICommand*>(GEN_CommandFactory().createCommand("Show message box",QVector<QString>{"message header", "message to show", "1000"}));

//   ProtocolManager p;
//   QString data = p.encode(cmd);
//   qDebug() << data;
//   data = "ada";
//   QString cmdName;
//   QVector<QString> params;
//   QString error;
//   if(p.decode(data, cmdName, params, error))
//      qDebug() << cmdName << "::" << params;
//   else
//      qDebug() << error;


//   GEN_CommandFactory factory;

//   IExecutableCommand *pCmd = factory.createCommand("Show message box", QVector<QString>{"header", "Сообщение умопомрачениеСообщение умопомрачениеСообщение умопомрачениеСообщение умопомрачениеСообщение умопомрачениеСообщение умопомрачениеСообщение умопомрачениеСообщение умопомрачениеСообщение умопомрачениеСообщение умопомрачениеСообщение умопомрачениеСообщение умопомрачениеСообщение умопомрачениеСообщение умопомрачениеСообщение умопомрачениеСообщение умопомрачениеСообщение умопомрачениеСообщение умопомрачениеСообщение умопомрачениеСообщение умопомрачениеСообщение умопомрачениеСообщение умопомрачениеСообщение умопомрачениеСообщение умопомрачениеСообщение умопомрачениеСообщение умопомрачениеСообщение умопомрачениеСообщение умопомрачениеСообщение умопомрачениеСообщение умопомрачениеСообщение умопомрачениеСообщение умопомрачениеСообщение умопомрачениеСообщение умопомрачениеСообщение умопомрачение", "20"});
//   if(pCmd->execute())
//   {
//      qDebug() << pCmd->results();
//   } else
//   {
//      qDebug() << pCmd->errorMessage();
//   }
   QApplication::setQuitOnLastWindowClosed(false);

   return client.exec();
}
