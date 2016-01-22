#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QObject>
#include <QTcpSocket>

class QTcpSocket;
class QTimer;

class NetworkManager : public QObject
{
   Q_OBJECT

   QString m_host;
   int m_port;
   QTcpSocket *m_pSocket;
   QTimer *m_pTimer;
   quint16 m_blockSize;

public:
   explicit NetworkManager(QObject *parent = 0);
   void start(QString host, int port, int reconnectionInterval = 10000);
signals:
   void signalDataReceived(QString message);

public slots:
   void slotConnect();
   void slotConnectionSuccessful();
   void slotReadyRead();
   void slotError(QAbstractSocket::SocketError error);
   void slotSendToServer(QString data);

};

#endif // NETWORKMANAGER_H
