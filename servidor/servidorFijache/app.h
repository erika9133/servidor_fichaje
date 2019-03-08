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
   QVector<QString> m_config;
   bool checkLogin(QString user, QString pass);

public:
    App();
    ~App();

    QVector<QString> readConfig(const QString archivo) const;

public slots:
    void processIncomingMessage(IncomingMessage m);
};

#endif // APP_H
