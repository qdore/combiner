#ifndef MENU_H
#define MENU_H

#include "configparse.h"
#include "config.h"
#include <QMenu>
#include <QAction>
#include <QProcess>
#include <vector>
#include <QStringList>
#include <memory>
#include "server/server.hpp"
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <thread>
#include <QThread>

class HttpThread : public QThread
{
public:
    Q_OBJECT

    void run() Q_DECL_OVERRIDE
    {
        std::string s = std::to_string(HTTPPORT);
        http::server::server http("0.0.0.0", s.c_str(), ".");
        http.run();
    }
};

class menu : public QMenu
{
    Q_OBJECT
public:
    explicit menu(QWidget *parent = 0);
    void* father;

public slots:
    void fun_stop();
    void fun_start();
    void fun_quit();

private:
    QAction* start;
    QAction* stop;
    QAction* quit;
    HttpThread t;
    std::vector<std::shared_ptr<QProcess> > shadowsocks;
    std::shared_ptr<std::vector<QStringList> > arguments;
    std::string randomProxy;
};



#endif
