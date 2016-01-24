#include "controller/private/Server.hpp"
#include <QTcpServer>
#include <QTcpSocket>
#include <QByteArray>
#include <QDataStream>

#include <QDebug>

Server::Server(QObject *parent)
   : QObject(parent)
   , m_pTcpServer(nullptr)
   , m_pConnectedSockets()
   , m_blockSize(0)
{
   m_pTcpServer = new QTcpServer(this);
   if(!m_pTcpServer->listen(QHostAddress::Any, 10001))
   {
      qCritical() << "Can't listen to port 10000";
      m_pTcpServer->close();
   }
   qDebug() << "Server ready on port 10000";
   connect(m_pTcpServer, &QTcpServer::newConnection, this, &Server::slotNewConnection);
}

Server::~Server()
{
   m_pTcpServer->close();
}

void Server::slotNewConnection()
{
   QTcpSocket *connection = m_pTcpServer->nextPendingConnection();
   qDebug() << "new connection " << connection->peerName() << " :: " << connection->peerAddress();

   //TODO fix me
   if(m_pConnectedSockets.keys().contains(connection->peerAddress().toString()))
   {
      qDebug() << "More then one clients connected from one IP.";
      emit message(tr("More then one clients connected from one IP %1."
                      "Connection refused.").arg(connection->peerAddress().toString()));
      connection->disconnectFromHost();
   } else
   {
      m_pConnectedSockets.insert(connection->peerAddress().toString(), connection);
      connect(connection, &QTcpSocket::disconnected, this, &Server::slotDisconnected);
      connect(connection, &QTcpSocket::readyRead, this, &Server::slotReadClient);
      //      m_pCurrentConnection = connection;
      emit signalNewConnection(connection->peerAddress().toString());
   }
}

void Server::slotReadClient()
{
   qDebug();
   QTcpSocket *pSocket = dynamic_cast<QTcpSocket*>(sender());
   if(pSocket)
   {
      QDataStream in(pSocket);
      in.setVersion(QDataStream::Qt_5_0);
      while(true)
      {
         if (!m_blockSize)
         {
            if(pSocket->bytesAvailable() < sizeof(quint16))
            {
               qDebug() << "Available bytes in socket less then quint16. Aborting read loop.";
               break;
            } else
            {
               in >> m_blockSize;
            }
         }
         if(pSocket->bytesAvailable() < m_blockSize)
         {
            qDebug() << pSocket->bytesAvailable() << " < " << m_blockSize << " :: Available bytes in socket less then m_blockSize. Aborting read loop.";
            break;
         }
         QString receivedData;
         in >> receivedData;
         qDebug() << "receivedData : " << receivedData;
         m_blockSize = 0;
         emit signalMessageReceived(pSocket->peerAddress().toString(), receivedData);
      }
   } else
   {
      qDebug() << "Sender in slot is not QTcpSocket*";
   }
}

void Server::slotDisconnected()
{
   QTcpSocket *pSocket = dynamic_cast<QTcpSocket*>(sender());
   if(pSocket)
   {
      qDebug() << " disconnected " << pSocket->peerAddress();
      m_pConnectedSockets.remove(pSocket->peerAddress().toString());
      emit signalDisconnect(pSocket->peerAddress().toString());
      pSocket->deleteLater();
   } else
   {
      qDebug() << "Sender in slot is not QTcpSocket*";
   }
}

void Server::slotSendToClient(QString name, QString data)
{
   qDebug() << " name:" << name << " data:"<< data;
   auto it = m_pConnectedSockets.find(name);
   if(it != m_pConnectedSockets.end())
   {
      QByteArray dataToSend;
      QDataStream out(&dataToSend, QIODevice::WriteOnly);
      out.setVersion(QDataStream::Qt_5_0);
      out << quint16(0) << data;
      out.device()->seek(0);
      out << quint16(dataToSend.size() - sizeof(quint16));
      (*it)->write(dataToSend);
   } else
   {
      qDebug() << "No client adr \"" << name << "\" connected";
      emit message(QString("No such client adr ") + name + QString(" connected"));
   }
}
