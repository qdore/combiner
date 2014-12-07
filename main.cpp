#include "systemtrayicon.h"
#include "server/server.hpp"
#include "config.h"
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <thread>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setAttribute(Qt::AA_UseHighDpiPixmaps);
    SystemTrayIcon w;
    w.show();
    return a.exec();
}
