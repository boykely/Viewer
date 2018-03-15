#ifndef COMMONS_H
#define COMMONS_H

#include <QStandardPaths>

class Commons
{
public:
    Commons();
    static QString AppDir();
    static QString DesktopDir();
};

#endif // COMMONS_H
