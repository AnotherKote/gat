#include <QApplication>
#include <QFile>

#include "controller/Controller.hpp"
#include <QDebug>
////<debug>
//#include "view/MainScreen.hpp"
//#include "Server/model/Model.hpp"
//#include "Common/gen/GEN_CommandFactory.hpp"
//#include "Common/gen/GEN_CommandsHelper.hpp"
////</debug>

QFile outFile("GAT_Server_log.txt");

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

   QApplication server(argc, argv);
   outFile.open(QIODevice::WriteOnly);
//   qSetMessagePattern("[%{time process}] %{function}(line:%{line})\t%{message}"); //      ;
   qInstallMessageHandler(myMessageOutput);
   QApplication::setOrganizationName("AnotherKote'sSoftware");
   QApplication::setApplicationName("GATServer");

   Controller c;
   c.show();

   //Controller controller;
   return server.exec();
}
