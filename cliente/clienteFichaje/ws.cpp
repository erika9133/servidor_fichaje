#include <QDebug>
#include <QTimer>
#include <QString>
#include "ws.h"

QT_USE_NAMESPACE

WS::WS(const QHostAddress ip, const quint16 port)
{
     QTimer::singleShot(0,this,SLOT(go()));
     //m_url = QUrl(QStringLiteral("ws://"+ip.toString()+":"+QString::number(port)));

     m_url.setPath("ws");
     m_url.setHost(ip.toString());
     m_url.setPort(port);
     qDebug() << m_url.toString();
}

WS::~WS()
{
 if (m_connected) disconnect();
 delete m_webSocket;
}

void WS::go()
{
    m_webSocket = new QWebSocket();
    connect(m_webSocket, SIGNAL(connected()),this,SLOT(connected()));
    connect(m_webSocket, SIGNAL(disconnected()),this,SLOT(disconnected()));
    connect(m_webSocket, SIGNAL(textMessageReceived(QString)),this,SLOT(reciveMessage(QString)));
    m_webSocket->open(m_url);
}

void WS::connected()
{
    m_connected = true;
    qDebug() << "WebSocket connected";
    qDebug() << m_connected;
    //sendMessage("a");
}

void WS::disconnected()
{
    m_connected = false;
    qDebug() << "WebSocket disconnected";
    m_webSocket->close();
}

void WS::sendMessage(QString message)
{
    if (m_connected){
        //qDebug() << "Message enviado:" << message;
        m_webSocket->sendTextMessage(message);
    }
}

void WS::reciveMessage(QString message)
{
    emit procesarMensaje(message);
   // qDebug() << "Message recibido:" << message;
}
