#ifndef INVOKER_H
#define INVOKER_H

#include <QObject>
#include <QStack>

class NetworkManager;
class ProtocolManager;
class GEN_CommandFactory;

class Invoker : public QObject
{
   Q_OBJECT
   NetworkManager *m_pNetworkManager;
   ProtocolManager *m_pProtocolManager;
   GEN_CommandFactory *m_pFactory;
//   QStack<ICommand>s m_commandsStack;
public:
   explicit Invoker(QObject *parent = 0);
   ~Invoker();
   void run(QString host, int port, int recconectionInterval);
signals:

public slots:
   void slotMessageFromServer(QString message);
};

#endif // INVOKER_H
