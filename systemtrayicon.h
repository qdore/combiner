#ifndef SYSTEMTRAYICON_H
#define SYSTEMTRAYICON_H

#include <QSystemTrayIcon>
#include "config.h"
#include "menu.h"

class SystemTrayIcon : public QSystemTrayIcon
{
private:
    menu* m;
public:
    explicit SystemTrayIcon();
    void setDisableIcon();
    void setAbleIcon();
};

#endif // SYSTEMTRAYICON_H
