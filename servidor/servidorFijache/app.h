#ifndef APP_H
#define APP_H

#include <QVector>
#include "ws.h"
#include "bbdd.h"

class App
{
   BBDD *m_bbdd;
   WS *m_ws;
   QVector<QString> m_config;




public:
    App();
    ~App();
    QVector<QString> leerArchivoLineaPorLinea(const QString archivo);

};

#endif // APP_H
