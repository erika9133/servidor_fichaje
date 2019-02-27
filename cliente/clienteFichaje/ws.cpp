#include <QDebug>
#include <QTimer>
#include <QString>
#include "ws.h"

QT_USE_NAMESPACE

WS::WS(const QHostAddress ip, const quint16 port)
{
    ///Wait to main application exec loop
   // QTimer::singleShot(0,this,SLOT(go()));
    ///Add to url the rigth address
    m_url.setScheme("ws");
    m_url.setHost(ip.toString());
    m_url.setPort(port);

    m_webSocket = new QWebSocket();
    connect(m_webSocket, SIGNAL(connected()),this,SLOT(connected()));
    connect(m_webSocket, SIGNAL(disconnected()),this,SLOT(disconnected()));
    connect(m_webSocket, SIGNAL(textMessageReceived(QString)),this,SLOT(reciveMessage(QString)));
    m_webSocket->open(m_url);
    sendMessage("a");
}//end

WS::~WS()
{
 if (m_connected) disconnect();
 delete m_webSocket;
}//end

void WS::sendMessage(const QString message) const
{
    if (m_connected) m_webSocket->sendTextMessage(message);
}//end

/***public slots***/
void WS::go()
{

}//end

void WS::connected()
{
    m_connected = true;
    qDebug() << "WebSocket connected in path: " + m_url.toString();
}//end

void WS::disconnected()
{
    m_connected = false;
    qDebug() << "WebSocket disconnected";
    m_webSocket->close();
}//end

void WS::reciveMessage(const QString message) const
{
    emit procesarMensaje(message);
}//end
