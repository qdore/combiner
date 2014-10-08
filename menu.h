#ifndef MENU_H
#define MENU_H

#include <QMenu>
#include <QAction>
#include <QProcess>

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
    QProcess* goagent;
    QProcess* shadowsock;

};

#endif
