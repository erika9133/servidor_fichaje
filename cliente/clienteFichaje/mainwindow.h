#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include "ws.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    WS *m_ws;
    Ui::MainWindow *ui;
    QVector<QString> m_config;

public:
     explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QVector<QString> readConfig(const QString file) const;

public slots:
    void doLogin(); ///Wait for websocket to be susscessfully connected

private slots:
    void on_logginbtn_clicked();
};

#endif // MAINWINDOW_H
