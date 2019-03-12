#ifndef BBDD_H
#define BBDD_H

#include <QString>
#include <QtSql>

class BBDD
{
    bool m_bdStatus;
    int m_port;
    QString m_host;
    QString m_database;
    QString m_user;
    QString m_pass;
    QSqlDatabase m_db;

public:
    BBDD(const QString host, const int port, const QString database,const QString user, const QString pass);
    ~BBDD();

    void connect();
    void disconnect();
    QVector<QString> select(QMap< QString,  QString> &values,const QString &select);
    bool insert(QMap< QString, QString> &values,const QString &insert);
    QSqlQuery prepareBindValue(QMap< QString,  QString> &values,const QString &select);
    QString simpleSelect(const QString &select);
};

#endif // BBDD_H
