#ifndef WS_H
#define WS_H

#include <QtCore/QObject>
#include <QtWebSockets/QWebSocket>
#include <QUrl>


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
    void sendMessage(const QString message) const;

public slots:
    void go(); ///Wait to app exec loop and connect de signals-slots
    void connected();
    void disconnected();
    void reciveMessage(const QString message) const;

signals:
    void procesarMensaje(const QString) const;
    void loginReady() const; ///Wait to be connected before send login info to server

};

#endif // WS_H
