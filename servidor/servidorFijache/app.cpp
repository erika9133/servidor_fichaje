#include <iostream> //readConfig
#include <fstream> //readConfig
#include <QMap>
#include <QDateTime>
#include "app.h"
#include "json.h"

App::App()
{
    ///Load config file
    QVector<QString> m_config = readConfig("config.txt");
    ///Not empty and expected items
    if(!m_config.empty() && m_config.size() == 7){
        QHostAddress  ip = QHostAddress();
        ///cant convert ip to localhost
        if(m_config.at(0) == "localhost" || m_config.at(0) == "127.0.0.1"){
            ip.setAddress(QHostAddress::LocalHost);
        }else{
           ip.setAddress(m_config.at(0));
        }//end if
        m_ws = new WS(ip, m_config.at(1).toUShort());
        m_bbdd = new BBDD(m_config.at(2), m_config.at(3).toInt(), m_config.at(4), m_config.at(5), m_config.at(6));
        ///When websocket recive a message, is sent here
        connect(m_ws, SIGNAL(emitRecivedMessage(IncomingMessage)), this, SLOT(processIncomingMessage(IncomingMessage)));
    }else{
        qDebug() << "Error 001. Config file damage.";
    }//end if else
   // m_bbdd->test(); //test borrar
}//end

App::~App()
{
    delete m_ws;
    delete m_bbdd;
}//end

/***private***/
bool App::checkLogin(const QString &user,const QString &pass)
{
    bool boolReturned = false;
    const QString select= "SELECT clientes_pass FROM clientes WHERE clientes_user LIKE :user";
    ///BBDD select is prepared to accept several values cause we use a qMap.
    QMap< QString, QString> keyValue;
    ///Key - value
    QString key = ":user";
    keyValue.insert(key,user);
    ///Insert qmap and query. the qmap will be itinerated by default for every key-value item.
    QVector<QString> result = m_bbdd->select(keyValue,select);
    ///If the login password is the same bbdd password the user is valid
    if(!result.isEmpty() && result.at(0) == pass) boolReturned = true;
    return boolReturned;
}//end

bool App::checkUser(const QString &user,const QString &pass)
{
    bool boolReturned = false;
    const QString select= "SELECT usuarios_pass FROM usuarios WHERE usuarios_ean13 LIKE :ean13 AND usuarios_valido IS TRUE" ;
    QMap< QString, QString> keyValue;
    QString key = ":ean13";
    keyValue.insert(key,user);
    QVector<QString> result = m_bbdd->select(keyValue,select);
    if(!result.isEmpty() && result.at(0) == pass) boolReturned = true;
    return boolReturned;
}//end

bool App::checkRightData(const QString &type,const QString &date)
{
    bool boolReturned = false;
    if(type == "in" || type == "out")
    {
        QDateTime dateTemp;
        dateTemp.fromString(date,"dd/MM/yyyy  h:m:s");
        if(dateTemp.isValid() && dateTemp < QDateTime::currentDateTime()){
            boolReturned = true;
        }
    }
    return boolReturned;
}//end

/***public slots***/
//Main method to check messages and response or do things
void App::processIncomingMessage(IncomingMessage m)
{
    QString jType = JSON::findTypeMessage(m.ptrMessage);
    if(jType == "mainlogin"){
        QVector<QString> vectorLogin = JSON::unParseMainLogin(m.ptrMessage);
        if(checkLogin(vectorLogin.at(0),vectorLogin.at(1)))
        {
            Socket *temp = m_ws->findSocket(m.ptrSocket);
            if(temp != nullptr){
                m_ws->findSocket(m.ptrSocket)->valid = true; //WIP not working
                qDebug() << "Socket: " << m.ptrSocket << " login as user client.";
            }else{
                qDebug() << "error"; //WIP description
            }

        }else
        {
            qDebug() << "Error 04. Coudnt login the websocket client";
        }//end else if mainwindow
    }else{
        ///Socket is login
        if(m_ws->findSocket(m.ptrSocket)->valid == true) //WIP != nullptr struct
        {
            ///User login or logout request
            if(jType == "login")
            {
                 QVector<QString> vectorLogin = JSON::unParseLogin(m.ptrMessage);
                 if(checkUser(vectorLogin.at(0),vectorLogin.at(1)))
                 {
                     if(checkRightData(vectorLogin.at(2),vectorLogin.at(3))){
                        //WIP making
                     }

                 }else
                 {
                     qDebug() << "Error 05. User not valid.";
                 }//end else if login
            }else if(jType == "other")
            {

            }
        ///If client hadnt logined and message is not a login request....
        }else   qDebug() << "Error 05. Message error.";
    }//end else jtype
}//end

//Tools
QVector<QString> App::readConfig(const QString file) const
{
    ///Expected struct in config file
    /***************
    * //Websockect IP
    * 0
    * //Websockect port
    * 1
    * //Postgres IP
    * 2
    * //Postgres port
    * 3
    * //Postgres name
    * 4
    * //Postgres user
    * 5
    * //Postgres pass
    * 6
    ***************/
    QVector<QString> qVectorReturned = {};
    std::ifstream tempFile;
    std::string line;

    tempFile.open (file.toStdString().c_str());
    if(tempFile.is_open())
    {
        while (getline(tempFile,line))
        {
            QString tempQString = line.c_str();
            ///Avoid comment lines
            if(!tempQString.startsWith("//"))
            {
                ///Remove odd char
                tempQString = tempQString.remove(QRegExp(QString::fromUtf8("[-`~!@#$%^&*()_€”+=|:;<>«»,.?/{}\'\"")));
                qVectorReturned.push_back(tempQString);
            }//end if
       }//end while
    }//end if
    return qVectorReturned;
}//end
