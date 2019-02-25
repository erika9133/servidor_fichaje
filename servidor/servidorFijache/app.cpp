#include <iostream> //leerArchivoLineaPorLinea
#include <fstream> //leerArchivoLineaPorLinea
#include "app.h"

App::App()
{
   QVector<QString> m_config = leerArchivoLineaPorLinea("config.txt");
   if(!m_config.empty()){
       m_ws = new WS(m_config.at(1), m_config.at(3).toUShort());
       m_bbdd = new BBDD(m_config.at(5), m_config.at(7).toInt(), m_config.at(9),m_config.at(11),m_config.at(13));
   }else{
       qDebug() << "Archivo de configuracion vacio";
   }//end if else
   m_bbdd->test(); //test borrar
}//end

App::~App()
{
    delete m_ws;
    delete m_bbdd;
}//end

//Herramientas≥
QVector<QString> App::leerArchivoLineaPorLinea(const QString archivo)
{
    QVector<QString> devolver = {};
    std::ifstream archivoTempI;
    std::string linea;

    archivoTempI.open (archivo.toStdString().c_str());
    if(archivoTempI.is_open())
    {
       while (getline(archivoTempI,linea))
       {
         // Para remover caracteres raros
         QString temp = linea.c_str();
         temp = temp.remove(QRegExp(QString::fromUtf8("[-`~!@#$%^&*()_€”+=|:;<>«»,.?/{}\'\"")));
         devolver.push_back(temp);
       }//end while
    }//end if
    return devolver;
}
