#include <QCoreApplication>
#include <memory>
#include <app.h>

std::unique_ptr<App> g_app;
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    ///Create dinamic ptr, not needed to be deleted
    g_app = std::make_unique<App>();
    ///Run loop main program
    a.exec();
    return 0;
}//END
