#include <QCoreApplication>
#include <memory>
#include <app.h>

std::unique_ptr<App> g_app;
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    g_app = std::make_unique<App>();
    a.exec();
    return 0;
}
