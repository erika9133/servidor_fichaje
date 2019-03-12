#include <iostream> //readConfig
#include <fstream> //readConfig
#include <QMap>
#include <QChar> //ean13 checksun
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
    QMap<QString, QString> response;
    qDebug() << vectorLogin.size();
    if(vectorLogin.size() == 3)
    {
        const QString select= "SELECT usuarios_pass FROM usuarios WHERE usuarios_ean13 LIKE :ean13 AND usuarios_valido IS TRUE" ;
        QMap<QString, QString> keyValue;
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
                        ///Get UUID from ean13
                        QMap< QString, QString> keyValue;
                        QString key = ":ean13";
                        keyValue.insert(key,vectorLogin.at(0));
                        QString select = "SELECT usuarios_uuid FROM usuarios WHERE usuarios_ean13 LIKE :ean13";
                        QVector<QString> id = m_bbdd->select(keyValue,select);
                        QUuid logUuid = QUuid::createUuid();
                        QString insert = "INSERT INTO log (log_uuid,usuarios_uuid,log_type)"
                                         "VALUES"
                                         "(:log_uuid,:usuarios_uuid,:log_type) RETURNING usuarios_uuid";
                        ///A new map to pass values
                        QMap< QString, QString> keyValueInsert;
                        keyValueInsert.insert(":log_uuid",logUuid.toString());
                        keyValueInsert.insert(":usuarios_uuid",id.at(0));
                        keyValueInsert.insert(":log_type",vectorLogin.at(2));

                        if(m_bbdd->insert(keyValueInsert,insert))
                        {
                            ///Suscess insert!
                            boolReturned = true;
                            QDebug debug = qDebug();
                            debug.noquote();
                            debug << "User " << vectorLogin.at(0) << "have log"+vectorLogin.at(2) << "at " << QDateTime::currentDateTime().toString();

                            if(vectorLogin.at(2) == "in") response.insert("response1","Login suscess");
                            else if(vectorLogin.at(2) == "out") response.insert("response1","Logout suscess");
                        }else{
                            qDebug() << "Error. Error while insert data in db";
                            response.insert("error","Error while insert data in db");
                        }//end else insert valid
                    }else{
                        qDebug() << "Error. Type of access is wrong.";
                        response.insert("error","Type of access is wrong.");
                    }//end else type in out
                }else{
                    qDebug() << "Error. User is not valid. Need it to be login";
                    response.insert("error","User is not valid. Need it to be login.");
                }//end else socket valid
            }else{
                qDebug() << "Error. Coudnt find client in list";
                response.insert("error","Coudnt find client in list");
            }//end else nullptr
        }else{
            qDebug() << "Error. Coudnt login the user";
            response.insert("error","Coudnt login the user");
        }//end else login query
    }else{
         qDebug() << "Error. One parameter is missing";
         response.insert("error","One parameter is missing");
    }//end else vector size

    QString responseString = JSON::response(response);
    m_ws->sentMessage(&responseString,message.ptrSocket);
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

QString App::generateEan13()
{
    QString code = "";
    int country = 84; ///spain
    int company = 11111; ///out company;
    int user = m_bbdd->simpleSelect("SELECT usuarios_codigo FROM usuarios ORDER BY usuarios_codigo DESC LIMIT 1;").toInt();
    QString code;
    code.push_back(QString::number(country));
    code.push_back(QString::number(company));
    code.push_back(QString::number(user));
    code.push_back(QString::number(generateControlDigit(code)));
    user++;
    return code;
}//end

int App::generateControlDigit(QString code)
{
    ///C# Wikipedia example adapted
    int intReturned = -1;
    int pair = 0;
    int odd = 0;
    int temp;
    for (int i = code.size(); i >= 1; i--)
    {
        if (i % 2 != 0)
        {
            ///Digital value transform QChar to int
            odd +=  code.at(i).digitValue();
        }else{
            pair += code.at(i).digitValue();
        }//end else
    }//end for
    temp = (odd*3) + pair ;
    intReturned = (10 - (temp % 10)) % 10;
    return intReturned;
}//end

bool App::checkControlDigit(QString code)
{
    bool boolReturned = false;
    ///remove checksun number
    QString check = code.remove(12,13);
    ///and generate again
    int pair = 0;
    int odd = 0;
    int temp;
    for (int i = check.size(); i >= 1; i--)
    {
        if (i % 2 != 0)
        {
            odd +=  check.at(i).digitValue();
        }else{
            pair += check.at(i).digitValue();
        }//end else
    }//end for
    temp = (odd*3) + pair ;
    temp = (10 - (temp % 10)) % 10;
    if(code == QString::number(temp)) boolReturned = true;
    return boolReturned;
}//end
