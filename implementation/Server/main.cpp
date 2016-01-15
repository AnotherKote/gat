#include <QApplication>
#include <QTime>
#include <QRegularExpression>
//<debug>
#include "view/MainScreen.hpp"
#include "Server/model/Model.hpp"
#include <QDebug>
#include "Common/gen/GEN_CommandFactory.hpp"
#include "Common/gen/GEN_CommandsHelper.hpp"
//</debug>

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

   Model *model = new Model();
   IClientsModel *clientsModel = static_cast<IClientsModel*>(model);
   ICommandsModel *cmdModel = static_cast<ICommandsModel*>(model);

   MainScreen mainScreen(cmdModel, clientsModel);
   mainScreen.show();

   //Controller controller;
   return server.exec();
}
