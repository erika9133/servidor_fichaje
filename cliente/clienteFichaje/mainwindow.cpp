#include <iostream> //readConfig
#include <fstream> //readConfig
#include <QDebug>
#include "ui_mainwindow.h"
#include "mainwindow.h"
#include "json.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ///Load config file
    m_config = readConfig("/Users/erika/Desktop/build-clienteFichaje/config.txt");
    ///Not empty and expected items
    if(!m_config.empty() && m_config.size() == 4){
        QHostAddress ip = QHostAddress();
        ///cant convert ip to localhost string
        if(m_config.at(3) == "localhost" || m_config.at(3) == "127.0.0.1"){
            ip.setAddress(QHostAddress::LocalHost);
        }else{
            ip.setAddress(m_config.at(3));
        }//end if
        m_ws = new WS(ip, m_config.at(2).toUShort());
        connect(m_ws, SIGNAL(loginReady()),this,SLOT(doLogin()));
    }else{
        qDebug() << "Error 001. Config file damage.";
    }//end if else
    ui->setupUi(this);
   // ui->logginbtn->setEnabled(false);
    //ui->logoutbtn->setEnabled(false);
    //Debug****
    ui->ean13->setText("1234567890123");
    ui->pass->setText("1234");
}//end

MainWindow::~MainWindow()
{
    delete ui;
    delete m_ws;
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
void MainWindow::doLogin()
{
   ///When websocket is susscessfully connected, can be send it login info
    m_ws->sendMessage(JSON::ParseMainLogin(m_config.at(0),m_config.at(1)));
}

void MainWindow::on_logginbtn_clicked()
{
    m_ws->sendMessage(JSON::ParseLogin(ui->ean13->text(),ui->pass->text(),"in"));
}
