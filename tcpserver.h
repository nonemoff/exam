#ifndef TCPSERVER_H
#define TCPSERVER_H
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

#include <QByteArray>
#include <QDebug>
#include <QtNetwork>
#include <qglobal.h>

class TcpServer : public QObject {
  Q_OBJECT
public:
  explicit TcpServer(QObject *parent = nullptr);
  ~TcpServer();
public slots:
  void close();
  void slotNewConnection();
  void slotClientDisconnected();
  void slotServerRead();

private:
  QTcpServer *tcpServer;
  int server_status;
  QMap<int, QTcpSocket *> SClients;
};
#endif // TCPSERVER_H