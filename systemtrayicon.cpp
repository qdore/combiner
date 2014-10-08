#include "systemtrayicon.h"

SystemTrayIcon::SystemTrayIcon()
{
    m = new menu();
    this->setContextMenu(m);
    m->father = static_cast<void*>(this);
    this->setIcon(QIcon(DISABLEDICON));
    m->fun_start();
}

void SystemTrayIcon::setAbleIcon()
{
    this->setIcon(QIcon(ICON));
}

void SystemTrayIcon::setDisableIcon()
{
    this->setIcon(QIcon(DISABLEDICON));
}
