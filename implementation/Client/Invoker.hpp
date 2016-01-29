#ifndef INVOKER_H
#define INVOKER_H

#include "Common/CommandHelper.hpp"

#include <QObject>
#include <QStack>

class NetworkManager;
class ProtocolManager;

class Invoker : public QObject
{
   Q_OBJECT
   NetworkManager *m_pNetworkManager;
   ProtocolManager *m_pProtocolManager;
   const CommandHelper &m_helper;

public:
   explicit Invoker(QObject *parent = 0);
   ~Invoker();
   void run(QString host, int port, int recconectionInterval);
signals:

public slots:
   void slotMessageFromServer(QString message);
};

#endif // INVOKER_H
