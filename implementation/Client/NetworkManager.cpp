#include "NetworkManager.hpp"

#include <QTimer>
#include <QMetaEnum>
#include <QDataStream>

NetworkManager::NetworkManager(QObject *parent)
   : QObject(parent)
   , m_host("")
   , m_port(0)
   , m_pSocket(nullptr)
   , m_pTimer(nullptr)
   , m_blockSize(0)
{
   m_pSocket = new QTcpSocket(this);
   m_pTimer = new QTimer(this);
   m_pTimer->setSingleShot(true);
   connect(m_pTimer, &QTimer::timeout, this, &NetworkManager::slotConnect);
   connect(m_pSocket, &QTcpSocket::connected, this, &NetworkManager::slotConnectionSuccessful);
   connect(m_pSocket, SIGNAL(error(QAbstractSocket::SocketError)), SLOT(slotError(QAbstractSocket::SocketError)));
   connect(m_pSocket, &QTcpSocket::readyRead, this, &NetworkManager::slotReadyRead);
}

void NetworkManager::start(QString host, int port, int reconnectionInterval )
{
   if(!host.isEmpty() && port != 0 && reconnectionInterval != 0)
   {
      m_pTimer->setInterval(reconnectionInterval);
      m_host = host;
      m_port = port;
      slotConnect();
   } else
   {
      qDebug() << "Can't start server. Host is empty or port is 0.";
   }
}

void NetworkManager::slotConnect()
{
   m_pSocket->connectToHost(m_host, m_port);
}

void NetworkManager::slotConnectionSuccessful()
{
   m_pTimer->stop();
   qDebug() << "Connection succesful";
}

void NetworkManager::slotReadyRead()
{
   QDataStream in(m_pSocket);
   in.setVersion(QDataStream::Qt_5_0);
   while(true)
   {
      if (!m_blockSize)
      {
         if(m_pSocket->bytesAvailable() < sizeof(quint16))
         {
            qDebug() << "Available bytes in socket less then quint16. Aborting read loop.";
            break;
         } else
         {
            in >> m_blockSize;
         }
      }
      if(m_pSocket->bytesAvailable() < m_blockSize)
      {
         qDebug() << "Available bytes in socket less then m_blockSize. Aborting read loop.";
         break;
      }
      QString receivedData;
      in >> receivedData;
      //TODO signal that data is received. Signal to Invoker. Invoker -> decoder -> indoker -> factory -> invoker -> execute;
      qDebug() << "receivedData : " << receivedData;
      emit signalDataReceived(receivedData);
      m_blockSize = 0;
   }
}

void NetworkManager::slotError(QAbstractSocket::SocketError error)
{
   m_pTimer->start();
   QMetaObject mObj = QAbstractSocket::staticMetaObject;
   QMetaEnum mEnum = mObj.enumerator(mObj.indexOfEnumerator("SocketError"));

   qDebug() << "Client connection error: " << mEnum.valueToKey(error);
}

void NetworkManager::slotSendToServer(QString data)
{
   qDebug() << " data:"<< data;
   QByteArray dataToSend;
   QDataStream out(&dataToSend, QIODevice::WriteOnly);
   out.setVersion(QDataStream::Qt_5_0);
   out << quint16(0) << data;
   out.device()->seek(0);
   out << quint16(dataToSend.size() - sizeof(quint16));
   m_pSocket->write(dataToSend);
   qDebug() << "send " << quint16(dataToSend.size() - sizeof(quint16));
   qDebug() << "send " << dataToSend.size();
}

