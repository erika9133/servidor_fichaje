#include "bbdd.h"

BBDD::BBDD(const QString host,const int port,const QString database,const QString user,const QString pass)
{
    m_bdStatus = false; ///keep connected bool status
    m_host = host;
    m_port = port;
    m_database = database;
    m_user = user;
    m_pass = pass;
    m_db = QSqlDatabase::addDatabase("QPSQL"); ///Conection and driver
    qDebug() << "BBDD start. Postgres load in: " + m_host + ":" + QString::number(m_port);
    connect();
}//end

BBDD::~BBDD(){ disconnect();}//end

void BBDD::connect()
{
    if(!m_bdStatus)
    {
        m_db.setHostName(m_host);
        m_db.setPort(m_port);
        m_db.setDatabaseName(m_database);
        m_db.setUserName(m_user);
        m_db.setPassword(m_pass);

        if (m_db.open())
        {
            m_bdStatus = true;
             qDebug() << "BBDD Connection open";
        }else{
            m_bdStatus = false;
            qDebug() << "Error 02. Couldnt connect to DB." << m_db.lastError();
        }//end if else
    }//end if
}//end

void BBDD::disconnect()
{
    if(m_bdStatus) m_bdStatus = false;
    if(m_db.open()) m_db.close();
    qDebug() << "BBDD Connection close";
}//end

///Send a generic query to db
QVector<QString> BBDD::select(QMap< QString, QString> &values,const QString &select){
    QVector<QString> vectorReturned;
    ///Only exec if everything is right
    m_db.transaction();
    QSqlQuery querySQL = prepareBindValue(values,select);
    if(querySQL.exec())
    {
        while(querySQL.next())
        {
            if(querySQL.isValid())
            {
                vectorReturned.push_back(querySQL.value(0).toString());
            }else{
                 qDebug() << "Error. Query not valid";
            }//end else valid
        }//end while
    }else{
        qDebug() << "Error. Query not executed";
    }//end else exec

    ///Only exec if everything is right
    m_db.commit();
    return vectorReturned;
}//end

///Insert a generic query to db
bool BBDD::insert(QMap< QString, QString> &values,const QString &insert){
    bool boolReturned = false;
    ///Only exec if everything is right
    m_db.transaction();
    QSqlQuery querySQL = prepareBindValue(values,insert);
    if(querySQL.exec())
    {
        ///Insert return a user id, if its returned means insert is suscessfull
        if(querySQL.next()){
            if(querySQL.isValid())
            {
                boolReturned = true;
            }else{
                 qDebug() << "Error. Query not valid";
            }//end else valid
        }else{
             qDebug() << "Error. Query not positionated in a valid record";
        }//end else next
    }else{
        qDebug() << "Error. Query not executed";
    }//end else exec
    ///Only exec if everything is right
    m_db.commit();
    return boolReturned;
}//end

QSqlQuery BBDD::prepareBindValue(QMap<QString, QString> &values,const QString &select)
{
    ///Open database in constructor
    QSqlQuery queryReturned;
    queryReturned.prepare(select);
    ///Iterate in std-style. https://doc.qt.io/qt-5/qmap.html
    QMap<QString,QString>::const_iterator i = values.constBegin();
    while (i != values.constEnd())
    {
        ///Bind value before exec and write it in select query
        queryReturned.bindValue(i.key(),i.value());
        ++i;
    }//end while iterate
    return queryReturned;
}//end

/*void BBDD::test()
{
    QStringList devolver;
    connect();
    m_db.transaction();
    QSqlQuery query("SELECT usuarios_pass"
           " FROM usuarios"
           ";", m_db);

    QString lastError = query.lastError().text().trimmed();
    if (!lastError.isEmpty())
    {
    qDebug() << lastError;

    }else{
    while(query.next())
    {
        qDebug() << query.value(0).toString();
         devolver.append(query.value(0).toString());
    }
    }
    m_db.commit();
    disconnect();
}*/

