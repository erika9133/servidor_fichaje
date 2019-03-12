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
   bool checkMainLogin(const IncomingMessage &message); //Check client data login (Several clients, one client is used for several users (peaple))
   bool checkLogin(const IncomingMessage &message); //Check user data login
   bool checkAdmin(const IncomingMessage &message);
   bool createUser(const IncomingMessage &message);
   QString generateEan13();
   int generateControlDigit(QString code);
   QString generateEmployeeCode();
   bool checkControlDigit(QString code);

public:
    App();
    ~App();

    QVector<QString> readConfig(const QString archivo) const;

public slots:
    void processIncomingMessage(IncomingMessage m);
};

#endif // APP_H
