#ifndef WS_H
#define WS_H

#include <QtCore/QObject>
#include <QtWebSockets/QWebSocket>
#include "ui_mainwindow.h"

class QWebSocket;


class WS : public QObject
{
    Q_OBJECT
    QUrl m_url;
    QWebSocket *m_webSocket;
    bool m_connected;

public:
    explicit WS(const QHostAddress ip, const quint16 port);
    ~WS();
    void sendMessage(QString message);


public slots:
    void go();
    void connected();
    void disconnected();
    void reciveMessage(QString message);

signals:
    void procesarMensaje(QString);

};

#endif // WS_H
