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
bool App::checkMainLogin(const IncomingMessage &message)
{
    bool boolReturned = false;
    ///Get QVector with user-password
    QVector<QString> vectorLogin = JSON::unParseMainLogin(message.ptrMessage);

    const QString select= "SELECT clientes_pass FROM clientes WHERE clientes_user LIKE :user";
    ///BBDD select is prepared to accept several values cause we use a qMap.
    QMap< QString, QString> keyValue;
    ///Key - value
    QString key = ":user";
    keyValue.insert(key,vectorLogin.at(0));
    ///Insert qmap and query. the qmap will be itinerated by default for every key-value item.
    QVector<QString> result = m_bbdd->select(keyValue,select);
    ///If the login password is the same bbdd password the user is valid
    if(!result.isEmpty() && result.at(0) == vectorLogin.at(1))
    {
        Socket *temp = m_ws->findSocket(message.ptrSocket);
        ///Just in case was a connecting ws error
        if(temp != nullptr)
        {
            m_ws->findSocket(message.ptrSocket)->valid = true;
            boolReturned = true;
            qDebug() << "Socket: " << message.ptrSocket << " login as user client.";
        }else{
            qDebug() << "Error: Client in list is empty";
        }//end else
    }else{
        qDebug() << "Error. Coudnt login the websocket client";
    }//end else
    return boolReturned;
}//end

bool App::checkLogin(const IncomingMessage &message)
{
    bool boolReturned = false;
    ///Vector at 0 user. 1 pass. 2 type. 3 date
    QVector<QString> vectorLogin = JSON::unParseLogin(message.ptrMessage);

    const QString select= "SELECT usuarios_pass FROM usuarios WHERE usuarios_ean13 LIKE :ean13 AND usuarios_valido IS TRUE" ;
    QMap< QString, QString> keyValue;
    QString key = ":ean13";
    keyValue.insert(key,vectorLogin.at(0));
    QVector<QString> result = m_bbdd->select(keyValue,select);
    ///if USER is right and active in db
    if(!result.isEmpty() && result.at(0) == vectorLogin.at(1))
    {
        Socket *temp = m_ws->findSocket(message.ptrSocket);
        if(temp != nullptr)
        {
            ///Previusly set it. if CLient is login
            if(m_ws->findSocket(message.ptrSocket)->valid == true)
            {
                ///if type of login is right
                if(vectorLogin.at(2) == "in" || vectorLogin.at(2) == "out")
                {
                    QDateTime dateTemp;
                    dateTemp.fromString(vectorLogin.at(3),"dd.MM.yyyy hh:mm:ss.z");
                    ///Needed to have a TimeSpect
                   // dateTemp.setTimeSpec();
                    qDebug() << vectorLogin.at(3);

                    qDebug() << dateTemp.date();
                    qDebug() << dateTemp.time();
                    qDebug() << dateTemp.timeZone();
                    qDebug() << dateTemp.timeSpec();
                    ///if date is valid and real date
                    if(dateTemp.isValid()) // && dateTemp < QDateTime::currentDateTime()
                    {
                        boolReturned = true;
                        qDebug() << "right!! :)"; //WIP
                    }else{
                        qDebug() << "Date is not well formed.";
                    }//end else
                }else{
                    qDebug() << "Error. Type of access is wrong.";
                }//end else type in out
            }else{
                qDebug() << "Error. User is not valid. Need it to be login";
            }//end else socket valid
        }else{
            qDebug() << "Error. Coudnt find client in list";
        }//end else nullptr
    }else{
        qDebug() << "Error. Coudnt login the user";
    }//end else login query
    return boolReturned;
}//end



/***public slots***/
//Main method to check messages and response or do things
void App::processIncomingMessage(IncomingMessage m)
{
    QString jType = JSON::findTypeMessage(m.ptrMessage);

    if(jType == "mainlogin") checkMainLogin(m); //WIP returned bool, do smt
    else if(jType == "login") checkLogin(m);
    else qDebug() << "Error: Message type is not valid";

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
