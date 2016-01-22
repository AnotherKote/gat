#include <QApplication>

#include "controller/Controller.hpp"
#include <QDebug>
////<debug>
//#include "view/MainScreen.hpp"
//#include "Server/model/Model.hpp"
//#include "Common/gen/GEN_CommandFactory.hpp"
//#include "Common/gen/GEN_CommandsHelper.hpp"
////</debug>

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

   QApplication server(argc, argv);
   qSetMessagePattern("[%{time process}] %{function}(line:%{line})\t%{message}"); //      qInstallMessageHandler(myMessageOutput);

   Controller c;
   c.show();

   //Controller controller;
   return server.exec();
}
