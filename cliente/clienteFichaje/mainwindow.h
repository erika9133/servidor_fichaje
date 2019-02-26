#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ws.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    WS *m_ws;

public:
     MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QVector<QString> readConfig(const QString file);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
