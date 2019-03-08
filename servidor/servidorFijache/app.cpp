#include <iostream> //readConfig
#include <fstream> //readConfig
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
bool App::checkLogin(QString user, QString pass)
{
    bool boolReturned = false;

   // QString select = "SELECT usuarios_pass"
     //               " FROM usuarios"
       //             ";";
            QString select= "SELECT clientes_pass FROM clientes WHERE clientes_user LIKE :user";
    ///BBDD select is prepared to accept several values cause we use a vector.
    QVector<QString> vectorUser {user};
    QVector<QString> result = m_bbdd->select(vectorUser,select);
    if(!result.isEmpty() && result.at(0) == pass) boolReturned = true;
    return boolReturned;
}//end


/***public slots***/
//Main method to check messages and response or do things
void App::processIncomingMessage(IncomingMessage m)
{
    QString jType = JSON::findTypeMessage(m.ptrMessage);
    if(jType == "mainlogin"){
        //m_bbdd->test();
       QVector<QString> vectoLogin = JSON::unParseMainLogin(m.ptrMessage);
        qDebug() << checkLogin(vectoLogin.at(0),vectoLogin.at(1));
    }else{
        //not working
    }
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
