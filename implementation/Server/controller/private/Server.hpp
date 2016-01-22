#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QMap>

class QTcpServer;
class QTcpSocket;

class Server : public QObject //TODO more network manager then server. Change name?
{
   Q_OBJECT
   QTcpServer *m_pTcpServer;
//   QTcpSocket *m_pCurrentConnection;
   QMap<QString, QTcpSocket*> m_pConnectedSockets;
   quint16 m_blockSize;
public:
   explicit Server(QObject *parent = 0);
   ~Server();
signals:
   void signalNewConnection(QString adr);
   void signalDisconnect(QString adr);
   void signalMessageReceived(QString adr, QString message);
   void message(QString message);

public slots:
   void slotNewConnection();
   void slotReadClient();
   void slotDisconnected();
   void slotSendToClient(QString name, QString data);
};

#endif // SERVER_H
