#include "bbdd.h"

BBDD::BBDD(QString host, int port, QString database, QString user, QString pass)
{
    m_bdStatus = false;
    m_host = host;
    m_port = port;
    m_database = database;
    m_user = user;
    m_pass = pass;
    m_db = QSqlDatabase::addDatabase("QPSQL");
    qDebug() << "Postgres cargado en puerto:" << m_port;
}//end

BBDD::~BBDD(){}//end

void BBDD::connect()
{
    if(!m_bdStatus)
    {
        m_db.setHostName(m_host);
        m_db.setPort(m_port);
        m_db.setDatabaseName(m_database);
        m_db.setUserName(m_user);
        m_db.setPassword(m_pass);
        bool ok = m_db.open();
        QSqlError error = m_db.lastError();
        if (ok)
        {
            m_bdStatus = true;
        }else{
            m_bdStatus = false;
            qDebug() << "Error de conexion" << error.text();
        }//end if else
    }//end if
}//end

void BBDD::disconnect()
{
    if(m_bdStatus) m_bdStatus = false;
    if(m_db.open()) m_db.close();
}//end

void BBDD::test()
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
}
