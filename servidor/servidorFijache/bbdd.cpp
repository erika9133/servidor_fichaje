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
}

BBDD::~BBDD()
{

}

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
        }
      // qDebug() << "" << QUuid::createUuid().toString();
    }
}
