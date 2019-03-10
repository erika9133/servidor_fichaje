#ifndef APP_H
#define APP_H

#include <QObject>
#include <QVector>
#include "ws.h"
#include "bbdd.h"

class App : public QObject
{
   Q_OBJECT
   BBDD *m_bbdd;
   WS *m_ws;
   QVector<QString> m_config; //Module config data
   bool checkLogin(const QString &user,const QString &pass); //Check client data login (Several clients, one client is used for several users (peaple))
   bool checkUser(const QString &user,const QString &pass); //Check user data login
   bool checkRightData(const QString &type,const QString &date); //Check data type and date is right

public:
    App();
    ~App();

    QVector<QString> readConfig(const QString archivo) const;

public slots:
    void processIncomingMessage(IncomingMessage m);
};

#endif // APP_H
