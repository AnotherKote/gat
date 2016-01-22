#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QStringList>

class IClientsModel;
class ICommandsModel;
class MainScreen; //todo INterface?
class Server;

class Controller : public QObject
{
   Q_OBJECT
   IClientsModel *m_pClientsModel;
   ICommandsModel *m_pCommandsModel;
   MainScreen *m_pView;
   Server *m_pServer;
   //TODO network manager
   void connectSignalAndSlots();

public:
   explicit Controller(QObject *parent = 0);
   ~Controller();
   void show();

public slots:
   void slotNewConnection(QString name);
   void slotDisconnect(QString name);
   void slotFireCommand(QString userCmdName, QStringList users);
   void slotDataReceived(QString name, QString data);
};

#endif // CONTROLLER_H
