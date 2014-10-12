#include "menu.h"
#include "config.h"
#include "systemtrayicon.h"
#include <QApplication>
#include <QStringList>
#include <memory>
#include <iostream>
#include <string>

menu::menu(QWidget *parent) :
    QMenu(parent),
    goagent(NULL),
    shadowsock(NULL)
{
    goagent = new QProcess;
    shadowsock = new QProcess;

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
    connect(goagent, SIGNAL(finished(int)), this, SLOT(fun_stop()));
    connect(shadowsock, SIGNAL(finished(int)), this, SLOT(fun_stop()));

}

void menu::fun_quit()
{
    fun_stop();
    QApplication::quit();
}

void menu::fun_stop()
{
    if (goagent != NULL)
    {
        goagent->terminate();
    }
    if (shadowsock != NULL)
    {
        shadowsock->terminate();
    }
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
    QStringList argument;
    argument.append(QObject::tr("-s"));
    argument.append(QObject::tr(SHADOWADDRESS));
    argument.append(QObject::tr("-p"));
    argument.append(QObject::tr(SHADOWSERVERPORT));
    argument.append(QObject::tr("-l"));
    argument.append(QObject::tr(SHADOWPORT));
    argument.append(QObject::tr("-k"));
    argument.append(QObject::tr(SHADOWPASSWORD));
    argument.append(QObject::tr("-m"));
    argument.append(QObject::tr(SHADOWMETHOD));
    shadowsock->start(QObject::tr(SHADOW), argument);
    QStringList argument2;
    argument2.append(QObject::tr(PROXYPY));
    goagent->start(QObject::tr("/usr/bin/python"), argument2);

    /*
    goagent->waitForFinished(2000);
    shadowsock->waitForFinished(2000);
    std::cout << goagent->readAllStandardError().data() << std::endl;
    std::cout << goagent->readAllStandardOutput().data() << std::endl;
    std::cout << shadowsock->readAllStandardError().data() << std::endl;
    std::cout << shadowsock->readAllStandardOutput().data() << std::endl;
    */

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
    start->setDisabled(true);
    stop->setDisabled(false);

    static_cast<SystemTrayIcon*>(father)->setAbleIcon();
}
