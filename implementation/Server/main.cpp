#include <QApplication>

//<debug>
#include "view/MainScreen.hpp"
#include <QDebug>
//</debug>

int main(int argc, char *argv[])
{
   QApplication server(argc, argv);

   MainScreen mainScreen;
   mainScreen.show();

   //Controller controller;
   return server.exec();
}
