#include "tcpserver.h"
#include "functions.h"
#include <QCoreApplication>
#include <QDebug>

TcpServer::~TcpServer() {
  foreach (int i, SClients.keys()) {
    SClients[i]->close();
    SClients.remove(i);
  }
  tcpServer->close();
  server_status = 0;
}

TcpServer::TcpServer(QObject *parent) : QObject(parent) {
  tcpServer = new QTcpServer(this);
  connect(tcpServer, &QTcpServer::newConnection, this,
          &TcpServer::slotNewConnection);

  test();

  if (!tcpServer->listen(QHostAddress::Any, 33333)) {
    qDebug() << "Server is not started";
  } else {
    server_status = 1;
    qDebug() << "Server is started";
  }
}

void TcpServer::slotNewConnection() {
  if (server_status == 1) {
    QTcpSocket *clientSocket = tcpServer->nextPendingConnection();
    int user_socket_id = clientSocket->socketDescriptor();
    SClients[user_socket_id] = clientSocket;
    connect(SClients[user_socket_id], &QTcpSocket::readyRead, this,
            &TcpServer::slotServerRead);
    connect(SClients[user_socket_id], &QTcpSocket::disconnected, this,
            &TcpServer::slotClientDisconnected);
  }
}

void TcpServer::slotServerRead() {
  QTcpSocket *clientSocket = (QTcpSocket *)sender();
  QByteArray array;
  while (clientSocket->bytesAvailable() > 0)
    array = clientSocket->readAll();
  if (!array.trimmed().isEmpty()) {
    QByteArray request = array.trimmed();
    QByteArray encryptedReq =
        parser(request); 

    if (encryptedReq.toStdString().find("Error!") != std::string::npos) {
      clientSocket->write(request + "\r\n");
      clientSocket->write(encryptedReq + "\r\n");
    } else {
      clientSocket->write(request + "\r\n");
      clientSocket->write(encryptedReq + "\r\n");
    }
  }
}

void TcpServer::slotClientDisconnected() {
  QTcpSocket *clientSocket = (QTcpSocket *)sender();
  int user_socket_id = clientSocket->socketDescriptor();
  clientSocket->close();
  SClients.remove(user_socket_id);
}

void TcpServer::close() {
  this->~TcpServer();
  QCoreApplication::quit();
}