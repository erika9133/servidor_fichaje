#ifndef WS_H
#define WS_H

#include <QObject>
#include <QString>
#include "QtWebSockets/qwebsocketserver.h"
#include "QtWebSockets/qwebsocket.h"

class QWebSocketServer;
class QWebSocket;

struct IncomingMessage {
  QString message;
  QWebSocket *pSocket;
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
    WS(const QString ip , const quint16 port);
    ~WS();
    void sentMessage(const QString &message, QWebSocket &ptrSocket);
    void reciveMessage(QString &message);
    bool isValid(const QWebSocket *ptrSocket);
    bool isAdmin(const QWebSocket *ptrSocket);
    Socket *findSocket(QWebSocket *ptrSocket);

signals:
    void emitRecivedMessage(IncomingMessage message);

private slots:  
    void socketConnected();
    void socketDisconnected();
    void recivedMessage(QString message);
    void onClosed(); // mirar

    void sentMessageJson(QString message);

};
#endif // WS_H
