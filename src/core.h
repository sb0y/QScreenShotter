#ifndef CORE_H
#define CORE_H

#include <QObject>
#include "mainwindow.h"
#include <QApplication>
#include "system.h"
#include <map>
#include <QString>
#include <QWidget>
#include <QScreen>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QRect>
#include <QSignalMapper>
#include "aboutdialog.h"
#include <QString>
//#include "xwindowrectangle.h"
#include "screenshot.h"
#include <QTimer>
#ifdef HAVE_X11
    #include "neweventfilter.h"
#endif
#include "x11info.h"
#define getWindow(winID,cast_type)({static_cast<cast_type>(system::getCore()->windows[winID]);})

class core : public QApplication
{
    Q_OBJECT

public:
    screenshot *sc;
    QRect screen;

    std::map < QString, QWidget* > windows;
    QTimer timer;

    MainWindow::actions action;

    explicit core ( int &argc, char *argv[] );
    virtual ~core();
    int exec();
    void setPixmap ( QPixmap &pixmap );

    bool isVisible;

    // tray
    QSystemTrayIcon *trayIcon;
    QMenu *trayMenu;
    QAction *hideAction;
    QAction *quitAction;

    QPixmap picture;

    //XWindowRectangle rect;

private:
    void initTray();
    std::map < QString, QRect > windowGeometry;

signals:

public slots:
    void trayClick ( QSystemTrayIcon::ActivationReason reason );
    void mainAction ( MainWindow::actions action = MainWindow::DEFAULT );
    void toggleVisability();
    void showAbout();

    void trayShotDisplay();
    void trayShotWindow();
    void trayShotRect();
};

#endif // CORE_H
