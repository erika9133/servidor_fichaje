#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include "ws.h"

WS::WS(const QHostAddress ip, const quint16 port) : m_pWebSocketServer(new QWebSocketServer(QStringLiteral("servidor_fichaje")
                                                                 ,QWebSocketServer::NonSecureMode, this))
{
    if(m_pWebSocketServer->listen(ip, port))
    {
        QString debug = ip.toString();
        if(ip.toString() == "127.0.0.1") debug = "localhost";
        qDebug() << "WS start. Listening in: " + debug+ ":" + QString::number(port);
        ///Create signal-slot for main websocket server
        connect(m_pWebSocketServer, &QWebSocketServer::newConnection, this, &WS::socketConnected);
        connect(m_pWebSocketServer, &QWebSocketServer::closed, this, &WS::onClosed);
    }else{
        qDebug() << "Error 03. Coudnt create WS.";
    }//end if
}//end

WS::~WS()
{
    m_pWebSocketServer->close();
    ///Delete the ptr qlist items
    qDeleteAll(m_sockets);
    m_sockets.clear();
}//end

void WS::sentMessage(const QString *message, QWebSocket *ptrSocket) const
{
    ptrSocket->sendTextMessage(*message);
}//end

bool WS::isValid(const QWebSocket *ptrSocket) const
{
    bool boolReturned = false;
    for(auto i: m_sockets)
    {
        if(i->ptrSocket == ptrSocket)
        {
            if(i->valid) boolReturned = true;
            break;
        }//end if
    }//end for
    return boolReturned;
}//end

bool WS::isAdmin(const QWebSocket *ptrSocket) const
{
    bool boolReturned = false;
    for(auto i: m_sockets)
    {
        if(i->ptrSocket == ptrSocket)
        {
            if(i->admin) boolReturned = true;
            break;
        }//end if
    }//end for
    return boolReturned;
}//end

Socket *WS::findSocket(const QWebSocket *ptrSocket)
{
    ///Return something if couldnt be found
    Socket *ptrReturned = nullptr;
    for(int i = 0 ; i < m_sockets.size() ; i++)
    {
        ///if can find one item (socket) in the list with the same pointer-socket, return the pointer-item
        ///therefore it can be called and edit from outside
        if(m_sockets.at(i)->ptrSocket == ptrSocket){
            ptrReturned = m_sockets[i];
        }else{
        }
    }//end for
  return ptrReturned;
}//end

/***private slots***/
void WS::socketConnected()
{
    QWebSocket *ptrSocket = m_pWebSocketServer->nextPendingConnection();
    qDebug() << "Socket connected:" << ptrSocket;
    ///Create signal-slot for this new socket.
    connect(ptrSocket, &QWebSocket::textMessageReceived, this, &WS::recivedMessage);
    connect(ptrSocket, &QWebSocket::disconnected, this, &WS::socketDisconnected);
    ///Create new socket and put its pointer in the socket list
    Socket *socket = new Socket();
    ///When validate or login the socket, will be change the bool status
    socket->admin = false;
    socket->valid = false;
    socket->ptrSocket = ptrSocket;
    m_sockets.push_back(socket);
}//end

void WS::recivedMessage(QString message)
{
    QWebSocket *ptrSocket = qobject_cast<QWebSocket *>(sender());
    ///keep ptr socket and ptr message in one same struct
    IncomingMessage m;
    m.ptrSocket = ptrSocket;

    //TODO check menssage is valid, not return trash
    ///Remove odd char
    message = message.remove(QRegExp(QString::fromUtf8("[]-`~!@#$%^&*()_€”+=|;<>«».?/\'\"")));
    m.ptrMessage = &message;
    ///emit struct to main application to be process
    emit emitRecivedMessage(m);
    qDebug() << "From: " << ptrSocket << " Message recived: " << message;
}//end

void WS::onClosed()
{
     m_pWebSocketServer->close();
}//end

void WS::socketDisconnected()
{
    QWebSocket *ptrSocket = qobject_cast<QWebSocket *>(sender());
    if (ptrSocket)
    { 
        Socket *socket = findSocket(ptrSocket);
        ///check not null returned ptr
        if(socket){
            if(m_sockets.contains(socket)) m_sockets.removeAll((socket));
            ptrSocket->deleteLater();
            qDebug() << "Socket disconnected:" << ptrSocket;
        }//end if
    }//end if
}//end
