#ifndef CONFIG_H
#define CONFIG_H
#include <QCoreApplication>
#include <QString>
#include <string>

#define ICON ":/icon/icon/menu_icon.tiff"
#define DISABLEDICON ":/icon/icon/menu_icon_disabled.tiff"

#define SHADOW "/usr/local/bin/ss-local"
#define SHADOWPORT "1080"

#define SHADOWADDRESS "mdss01.mengsky.net"
#define SHADOWSERVERPORT "50941"
#define SHADOWPASSWORD "30391899"
#define SHADOWMETHOD "aes-256-cfb"

#define PROXYPY (QCoreApplication::applicationDirPath().toStdString() + "/../Resources/local/proxy.py").c_str()
#define GOAGENTPORT "8086"

#define PASSWORD "QWlvhb1314"


#endif // CONFIG_H
