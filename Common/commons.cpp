#include "commons.h"

Commons::Commons()
{

}

QString Commons::AppDir()
{
    return QStandardPaths::standardLocations(QStandardPaths::ApplicationsLocation).first();
}

QString Commons::DesktopDir()
{
    return QStandardPaths::standardLocations(QStandardPaths::DesktopLocation).first();
}
