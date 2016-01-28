#include <QApplication>
#include <QRegExp>
#include <QStringList>
#include <QString>
#include <QFile>
#include <QDebug>

#include "Common/gen/GEN_CommandFactory.hpp"
#include "Common/Commands/ICommand.hpp"
#include "Common/Commands/IExecutableCommand.hpp"
#include "Invoker.hpp"
#include "SystemTray.hpp"
#include "windows/WinExecutor.hpp"
#include "NetworkManager.hpp"
#include "Common/ProtocolManager.hpp"

QFile outFile("GAT_Client_log.txt");

void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
   QTextStream ts(&outFile);
   QByteArray localMsg = msg.toLocal8Bit();
   switch (type) {
   case QtDebugMsg:
      ts << QString("D: %1\t%2\n").arg(context.function).arg(localMsg.constData());
   break;
   case QtWarningMsg:
      ts << QString("W: %1\t%2\n").arg(context.function).arg(localMsg.constData());
   break;
   case QtCriticalMsg:
      ts << QString("C: %1\t%2\n").arg(context.function).arg(localMsg.constData());
   break;
   case QtFatalMsg:
      ts << QString("F: %1\t%2\n").arg(context.function).arg(localMsg.constData());
      ts.flush();
      abort();
   }
   ts.flush();
   return;
}

int main(int argc, char *argv[])
{
   QApplication client(argc, argv);
   outFile.open(QIODevice::WriteOnly);
   QStringList argList = client.arguments();
   QString serverIP("localhost");
   if(argList.count() > 1)
   {
      int index = argList.lastIndexOf(QRegExp("ip=([0-9]{1,3}[\.]){3}[0-9]{1,3}"));

      if(index != -1)
      {
         serverIP = argList.at(index).split("=").last();
      }
   }

//   qSetMessagePattern("[%{time process}] %{function}(line:%{line})\t%{message}"); //      qInstallMessageHandler(myMessageOutput);
   qInstallMessageHandler(myMessageOutput);

   SystemTray systemTray;
   Q_UNUSED(systemTray);

   Invoker invoker;
   invoker.run(serverIP, 10001, 1000);

   QApplication::setQuitOnLastWindowClosed(false);

   return client.exec();
}
