#ifndef WS_H
#define WS_H

#include <QObject>
#include <QString>
#include <QtWebSockets/qwebsocketserver.h>
#include <QtWebSockets/qwebsocket.h>

class QWebSocketServer; ///Provides server methods
class QWebSocket; ///Clients to connect to the server

struct IncomingMessage {
  const QString *ptrMessage;
  const QWebSocket *ptrSocket;
};

struct Socket {
  bool admin;
  bool valid;
  QWebSocket *ptrSocket;
};

class WS : public QObject
{
    Q_OBJECT
    QWebSocketServer *m_pWebSocketServer;
    QList<Socket*> m_sockets;

public:
    WS(const QHostAddress ip ,const quint16 port);
    ~WS();

    void sentMessage(const QString *ptrMessage, QWebSocket *ptrSocket) const;
    bool isValid(const QWebSocket *ptrSocket) const;
    bool isAdmin(const QWebSocket *ptrSocket) const;
    Socket *findSocket(const QWebSocket *ptrSocket);

private slots:  
    void socketConnected();
    void socketDisconnected();
    void recivedMessage(const QString message);
    void onClosed();

signals:
    void emitRecivedMessage(IncomingMessage const message);

};
#endif // WS_H
