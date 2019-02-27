#include <iostream> //readConfig
#include <fstream> //readConfig
#include <QDebug>
#include <QTimer>
#include "ui_mainwindow.h"
#include "mainwindow.h"
#include "json.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ///Wait to main application exec loop
    QTimer::singleShot(0,this,SLOT(go()));
    ///Load config file
    m_config = readConfig("/Users/erika/Desktop/build-clienteFichaje/config.txt");
    ///Not empty and expected items
    if(!m_config.empty() && m_config.size() == 4){
        QHostAddress  ip = QHostAddress();
        ///cant convert ip to localhost
        if(m_config.at(3) == "localhost" || m_config.at(3) == "127.0.0.1"){
            ip.setAddress(QHostAddress::LocalHost);
        }else{
            ip.setAddress(m_config.at(3));
        }//end if
        m_ws = new WS(ip, m_config.at(2).toUShort());
    }else{
        qDebug() << "Error 001. Config file damage.";
    }//end if else
     ui->setupUi(this);

}//end

MainWindow::~MainWindow()
{
    delete ui;
}//end

QVector<QString> MainWindow::readConfig(const QString file) const
{
    ///Expected struct in config file
    /***************
    * //user
    * 0
    * //pass
    * 1
    * //port
    * 2
    * //ip
    * 3
    ***************/
    QVector<QString> qVectorReturned = {};
    std::ifstream tempFile;
    std::string line;

    tempFile.open(file.toStdString().c_str());
    if(tempFile.is_open())
    {
        while (getline(tempFile,line))
        {
            QString tempQString = line.c_str();
            ///Avoid comment lines
            if(!tempQString.startsWith("//"))
            {
                ///Remove odd char
                tempQString = tempQString.remove(QRegExp(QString::fromUtf8("[-`~!@#$%^&*()_€”+=|:;<>«»,.?/{}\'\"")));
                qVectorReturned.push_back(tempQString);
            }//end if
       }//end while
    }//end if
    return qVectorReturned;
}//end

/***public slots***/
void MainWindow::go()
{
    ///Send login data to server
    m_ws->sendMessage("a");
    m_ws->sendMessage(JSON::ParseMainLoggin(m_config.at(0),m_config.at(1)));
    qDebug() << JSON::ParseMainLoggin(m_config.at(0),m_config.at(1));
}
