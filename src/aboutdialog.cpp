#include "aboutdialog.h"
#include "ui_aboutdialog.h"
#include <qdebug.h>

aboutDialog::aboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::aboutDialog)
{
    ui->setupUi ( this );
    setWindowTitle ( QObject::tr ( "About the program" ) );

    ui->qtVer->setText ( QString ( "Using Qt %0" ).arg ( QT_VERSION_STR ) );
    ui->runTimeInfo->setText ( "Running on " + getOS() );
}

aboutDialog::~aboutDialog()
{
    delete ui;
}

QString aboutDialog::getOS()
{
#ifdef WIN32
    switch ( QSysInfo::windowsVersion() )
    {
        case QSysInfo::WV_WINDOWS10: return "Windows 10";
        case QSysInfo::WV_WINDOWS8_1: return "Windows 8.1";
        case QSysInfo::WV_WINDOWS8: return "Windows 8";
        case QSysInfo::WV_WINDOWS7: return "Windows 7";
        case QSysInfo::WV_2000: return "Windows 2000";
        case QSysInfo::WV_XP: return "Windows XP";
        case QSysInfo::WV_VISTA: return "Windows Vista";

        default: return "Unknown Windows";
    }
#elif HAVE_X11

    utsname buf;
    if ( uname ( &buf ) == 0 )
    {

        return QString ( "%0 %1" ).arg ( buf.sysname ).arg ( buf.release );

    } else {
        return "Unknown Linux";
    }

#endif
}
