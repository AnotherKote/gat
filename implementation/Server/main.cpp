#include <QApplication>

//<debug>
#include "view/MainScreen.hpp"
#include <QTranslator>
//</debug>
#include <QDebug>

int main(int argc, char *argv[])
{
   QApplication server(argc, argv);

   QTranslator translator;
   qDebug() << "translation.load " << translator.load("main_ru.qm","D:/dev/gat/implementation/Server");
   server.installTranslator(&translator);
   MainScreen mainScreen;
   mainScreen.show();
   mainScreen.setTranslator(&translator);

   //Controller controller;
   return server.exec();
}
