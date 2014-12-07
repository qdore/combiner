#ifndef CONFIG_H
#define CONFIG_H
#include <QCoreApplication>
#include <QString>
#include <string>

#define ICON ":/icon/icon/menu_icon.tiff"
#define DISABLEDICON ":/icon/icon/menu_icon_disabled.tiff"

#define CONFIGFILE "../config.ini"
#define SHADOW "/usr/local/bin/ss-local"
#define SHADOWLOCALPORT 10800
#define HTTPPORT 17776

#define PASSWORD "QWlvhb1314"

extern std::string proxy_message;


#endif // CONFIG_H
