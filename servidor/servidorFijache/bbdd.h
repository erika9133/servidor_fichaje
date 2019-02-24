#ifndef BBDD_H
#define BBDD_H

#include <QString>
#include <QtSql>

class BBDD
{
    bool m_bdStatus;
    QString m_host;
    int m_port;
    QString m_database;
    QString m_user;
    QString m_pass;
    QSqlDatabase m_db;
public:
    BBDD(QString host, int port, QString database, QString user, QString pass);
    ~BBDD();
    void connect();
};

#endif // BBDD_H
