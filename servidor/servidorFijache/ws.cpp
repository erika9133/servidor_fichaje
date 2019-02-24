#include <QDebug>
#include "QJsonDocument"
#include "QJsonObject"
#include "QJsonValue"
#include "ws.h"

///public
WS::WS(const QString ip , const qint16 port) : m_pWebSocketServer(new QWebSocketServer(QStringLiteral("servidor_fichaje")
                                                                 ,QWebSocketServer::NonSecureMode, this))
{
    if (m_pWebSocketServer->listen(QHostAddress(ip), port))
    {
        qDebug() << "WS start at port:" << port;
        connect(m_pWebSocketServer, &QWebSocketServer::newConnection, this, &WS::socketConnected);
        connect(m_pWebSocketServer, &QWebSocketServer::closed, this, &WS::onClosed);
    }//end if
}//end

WS::~WS()
{
    m_pWebSocketServer->close();
    for(auto i : m_sockets) delete i.ptrSocket;
    delete &m_sockets;
    delete m_pWebSocketServer;
}//end

QList<Socket> &WS::sockets()
{
    return m_sockets;
}//end

void WS::sentMessage(const QString &message, QWebSocket &ptrSocket)
{
    ptrSocket.sendTextMessage(message);
}//end

bool WS::isValid(const QWebSocket &ptrSocket)
{
    bool vReturn = false;
    for(auto i: m_sockets)
    {
        if(i.ptrSocket == &ptrSocket)
        {
            if(i.valid) vReturn = true;
            break;
        }//end if
    }//end for
    return vReturn;
}//end

bool WS::isAdmin(const QWebSocket &ptrSocket)
{
    bool vReturn = false;
    for(auto i: m_sockets)
    {
        if(i.ptrSocket == &ptrSocket)
        {
            if(i.admin) vReturn = true;
            break;
        }//end if
    }//end for
    return vReturn;
}//end

Socket &WS::findSocket(QWebSocket &ptrSocket)
{
    Socket vReturn;
    for(int i = 0 ; i < m_sockets.size() ; i++)
    {
        if(m_sockets.at(i).ptrSocket == &ptrSocket){
            //at return cont data. watch out
            vReturn = m_sockets[i];
        }//end if
    }//end for
    return vReturn;
}//end

///private slots
void WS::socketConnected()
{
    QWebSocket *ptrSocket = m_pWebSocketServer->nextPendingConnection();
    qDebug() << "Socket connected:" << ptrSocket;
    connect(ptrSocket, &QWebSocket::textMessageReceived, this, &WS::recivedMessage);
    connect(ptrSocket, &QWebSocket::disconnected, this, &WS::socketDisconnected);
    Socket socket;
    socket.admin = false;
    socket.valid = false;
    socket.ptrSocket = ptrSocket;
    m_sockets.push_back(socket);
}//end

void WS::recivedMessage(QString message)
{
    QWebSocket *ptrSocket= qobject_cast<QWebSocket *>(sender());
    IncomingMessage incomingMessage;
    incomingMessage.pSocket = ptrSocket;
    incomingMessage.message = message;
    emit emitRecivedMessage(incomingMessage);
    qDebug() << "From: " << ptrSocket << " Message recived: " << message;
}//end

void WS::onClosed()
{
    //revisar
     m_pWebSocketServer->close();
}//end

void WS::socketDisconnected()
{
    QWebSocket *ptrSocket = qobject_cast<QWebSocket *>(sender());
    if (ptrSocket)
    {
        qDebug() << "Socket disconnected:" << ptrSocket;
        ///FIX delete items in disconnect
        //Socket const &socket = findSocket(*ptrSocket);
        //if(m_sockets.contains(socket)) m_sockets.removeAll(socket);
        ptrSocket->deleteLater();
    }//end if
}//end


void WS::sentMessageJson(QString message)
{
    /*
    QJsonObject recordObject;
    QJsonObject addressObject;
    addressObject.insert("Street", "Downing Street 10");
    addressObject.insert("City", "London");
    addressObject.insert("Country", "Great Britain");
    recordObject.insert("Address", addressObject);

    QJsonArray phoneNumbersArray;
    phoneNumbersArray.push_back("+44 1234567");
    phoneNumbersArray.push_back("+44 2345678");
    recordObject.insert("Phone Numbers", phoneNumbersArray);

    QJsonArray recordsArray;
    recordsArray.push_back(recordObject);
    QJsonDocument doc(recordsArray);
    qDebug() << doc.toJson();
    */
}//end

