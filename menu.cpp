#include "menu.h"
#include "config.h"
#include "systemtrayicon.h"
#include "proxy.h"
#include <QApplication>
#include <QStringList>
#include <memory>
#include <iostream>
#include <string>
#include <QDebug>
#include <thread>


std::string proxy_message = "";


menu::menu(QWidget *parent) :
    QMenu(parent),
    arguments(new std::vector<QStringList>)
{
    t.start();
    std::shared_ptr<std::vector<encry_pass_host_port> > parse(ConfigParse()(std::string(CONFIGFILE)));
    int i = SHADOWLOCALPORT;
    for (auto x: *parse)
    {
        QStringList argument;
        argument.append(QObject::tr("-s"));
        argument.append(QString::fromStdString(std::get<2>(x)));
        argument.append(QObject::tr("-p"));
        argument.append(QString::fromStdString(std::get<3>(x)));
        argument.append(QObject::tr("-l"));
        argument.append(QString::fromStdString(std::to_string(i)));
        argument.append(QObject::tr("-k"));
        argument.append(QString::fromStdString(std::get<1>(x)));
        argument.append(QObject::tr("-m"));
        argument.append(QString::fromStdString(std::get<0>(x)));
        arguments->push_back(std::move(argument));
        i++;
    }
    start = new QAction(this);
    stop = new QAction(this);
    quit = new QAction(this);

    start->setText(QString("Combiner start"));
    stop->setText(QString("Combiner stop"));
    quit->setText(QString("Quit"));

    this->addAction(start);
    this->addAction(stop);
    this->addSeparator();
    this->addAction(quit);
    stop->setDisabled(true);

    connect(start, &QAction::triggered, this, &menu::fun_start);
    connect(stop, &QAction::triggered, this, &menu::fun_stop);
    connect(quit, &QAction::triggered, this, &menu::fun_quit);
}

void menu::fun_quit()
{
    fun_stop();
    QApplication::quit();
}

void menu::fun_stop()
{
    for (auto x: shadowsocks)
    {
        disconnect(x.get(), SIGNAL(finished(int)), this, SLOT(fun_stop()));
        x->terminate();
    }
    shadowsocks.clear();
    std::string command = "echo ";
    command = command + PASSWORD +\
            "| sudo -S networksetup -setautoproxystate 'Wi-Fi' off";
    system(command.c_str());
    command = "echo ";
    command = command + PASSWORD +\
                "| sudo -S networksetup -setautoproxystate 'Thunderbolt Ethernet' off";
    system(command.c_str());

    start->setDisabled(false);
    stop->setDisabled(true);
    static_cast<SystemTrayIcon*>(father)->setDisableIcon();
}

void menu::fun_start()
{
    randomProxy = "function randomProxy()\n"
    "{\n"
    "    switch( Math.floor( Math.random() * ";
    randomProxy += std::to_string(arguments->size());
    randomProxy += " ) )\n    {\n";
    int i = 0;
    for (auto argument: (*arguments))
    {
        randomProxy += "        case ";
        randomProxy += std::to_string(i);
        randomProxy += ":\n            return \"SOCKS5 127.0.0.1:";
        randomProxy += argument[5].toStdString();
        randomProxy += ";\";\n            break;\n";
        i++;
        shadowsocks.push_back(std::make_shared<QProcess>());
        shadowsocks[shadowsocks.size()  - 1]->start(QObject::tr(SHADOW), argument);
        connect(shadowsocks[shadowsocks.size()  - 1].get(), SIGNAL(finished(int)), this, SLOT(fun_stop()));
    }
    randomProxy += "    }\n}\n\n";
    proxy_message = url_message + randomProxy + function_message;
    /*
    std::string command = "echo ";
    command = command + PASSWORD +\
            "| sudo -S networksetup -setautoproxyurl 'Wi-Fi' 'http://127.0.0.1:" +\
            GOAGENTPORT + "/proxy.pac'";
    system(command.c_str());
    command = "echo ";
    command = command + PASSWORD +\
            "| sudo -S networksetup -setautoproxyurl 'Thunderbolt Ethernet' 'http://127.0.0.1:" +\
            GOAGENTPORT + "/proxy.pac'";
    system(command.c_str());
    */
    start->setDisabled(true);
    stop->setDisabled(false);
    static_cast<SystemTrayIcon*>(father)->setAbleIcon();
}

