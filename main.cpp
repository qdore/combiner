#include "systemtrayicon.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setAttribute(Qt::AA_UseHighDpiPixmaps);
    SystemTrayIcon w;
    w.show();
    return a.exec();
}
