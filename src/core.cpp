#include "core.h"
#include <qdebug.h>
#include <X11/Xlib.h>

core::core ( int &argc, char *argv[] ) :
    QApplication ( argc, argv )
{    
    setApplicationName ( QObject::tr ( "qsc" ) );
    setApplicationDisplayName ( QObject::tr ( "QScreenShotter" ) );
    setApplicationVersion ( QObject::tr ( "0.1b" ) );
    setOrganizationName ( QObject::tr ( "andrey@bagrintsev.me" ) );
    setOrganizationDomain ( QObject::tr ( "bagrintsev.me" ) );
    setWindowIcon ( QIcon ( ":/tray/images/tray.png" ) );

    setAttribute ( Qt::AA_NativeWindows, true );
    //setAttribute ( Qt::AA_X11InitThreads, true );

    isVisible = true;
    installNativeEventFilter ( new NewEventFilter );
    sc = NULL;
}

core::~core()
{
    std::map < QString, QWidget* >::iterator i;

    for ( i = windows.begin(); i != windows.end(); ++i )
    {
        //delete i->second;
        //i->second = NULL;
        i->second->deleteLater();
    }

    delete trayMenu;
    delete sc;
}

int core::exec()
{
    MainWindow *mw = new MainWindow;
    mw->init ( this );
    windows [ "main" ] = mw;

    initTray();

    if ( NULL == sc )
    {
        sc = new screenshot ( this );
    }

    sc->shootDesktop ( true );

    mw->show();

    screen = qApp->primaryScreen()->geometry();

    return QApplication::exec();
}

void core::initTray()
{
    trayIcon = new QSystemTrayIcon;
    trayMenu = new QMenu;
    QMenu *actionMenu = new QMenu ( trayMenu );
    actionMenu->setTitle ( "QScreenShotter" );

    QAction *wholeDisplay = new QAction ( QObject::tr ( "Whole display" ), trayMenu );
    QAction *window = new QAction ( QObject::tr ( "Window" ), trayMenu );
    QAction *rect = new QAction ( QObject::tr ( "Display area" ), trayMenu );

    actionMenu->addAction ( wholeDisplay );
    actionMenu->addAction ( window );
    actionMenu->addAction ( rect );

    trayIcon->setIcon ( QIcon ( ":/tray/images/tray.png" ) );
    trayIcon->show();

    hideAction = new QAction ( QObject::tr ( "&Hide" ), trayIcon );
    quitAction = new QAction ( QObject::tr ( "&Exit" ), trayIcon );

    trayMenu->addMenu ( actionMenu );
    trayMenu->addSeparator();
    trayMenu->addAction ( hideAction );
    trayMenu->addSeparator();
    trayMenu->addAction ( quitAction );

    trayIcon->setContextMenu ( trayMenu );

    QObject::connect ( trayIcon, SIGNAL ( activated ( QSystemTrayIcon::ActivationReason ) ),
                 this, SLOT ( trayClick ( QSystemTrayIcon::ActivationReason ) ) );
    QObject::connect ( quitAction, SIGNAL ( triggered ( bool ) ), qApp, SLOT ( quit() ) );
    QObject::connect ( hideAction, SIGNAL ( triggered ( bool ) ), this, SLOT ( toggleVisability() ) );

    QObject::connect ( wholeDisplay, SIGNAL ( triggered(bool) ), this, SLOT ( trayShotDisplay() ) );
    QObject::connect ( window, SIGNAL ( triggered(bool) ), this, SLOT ( trayShotWindow() ) );
    QObject::connect ( rect, SIGNAL ( triggered(bool) ), this, SLOT ( trayShotRect() ) );
}

void core::trayClick ( QSystemTrayIcon::ActivationReason reason )
{
    MainWindow *mw = NULL;
    std::map<QString,QRect>::iterator it = windowGeometry.end();

    switch ( reason )
    {
        case QSystemTrayIcon::Trigger:

            for ( std::map<QString,QWidget*>::iterator i = windows.begin();
                  i != windows.end(); ++i )
            {
                if ( i->first == "main" )
                {
                    mw = static_cast < MainWindow* > ( i->second );
                }

                if ( i->second->isVisible() )
                {
                    i->second->hide();
                    windowGeometry [ i->first ] = i->second->geometry();
                    isVisible = false;
                    hideAction->setText ( QObject::tr ( "&Show" ) );

                } else {
                    i->second->showNormal();
                    it = windowGeometry.find ( i->first );
                    isVisible = true;

                    if ( it != windowGeometry.end() )
                    {
                        i->second->move ( it->second.x(), it->second.y() );
                    }

                    hideAction->setText ( QObject::tr ( "&Hide" ) );
                }
            }

            if ( mw && mw->isVisible() )
            {
                mw->setFocus();
                mw->activateWindow();
            }

        break;
        case QSystemTrayIcon::DoubleClick:
        break;
        case QSystemTrayIcon::MiddleClick:
        break;
        case QSystemTrayIcon::Context:
            trayMenu->show();
        break;
        default:
        break;
    }
}

void core::toggleVisability()
{
    trayClick ( QSystemTrayIcon::Trigger );
}

void core::showAbout()
{
    QDialog *d = new aboutDialog;
    d->show();
    windows [ "about" ] = d;
}

void core::mainAction ( MainWindow::actions act )
{
    MainWindow::actions old_act = MainWindow::DEFAULT;

    if ( MainWindow::DEFAULT != act )
    {
        old_act = action;
        action = act;
    }

    if ( NULL == sc )
    {
        sc = new screenshot ( this );
    }

    sc->init();

    switch ( action )
    {
        case MainWindow::TAKE_WINDOW:
            sc->shootWindow();
        break;
        case MainWindow::TAKE_RECTANGLE:
            sc->shootRectangle();
        break;
        case MainWindow::TAKE_AREA:
            sc->shootDesktop();
        break;
        default:
        break;
    }

    if ( MainWindow::DEFAULT != act )
    {
        action = old_act;
    }
}

void core::trayShotDisplay()
{
    mainAction ( MainWindow::TAKE_AREA );
}

void core::trayShotWindow()
{
    mainAction ( MainWindow::TAKE_WINDOW );
}

void core::trayShotRect()
{
    mainAction ( MainWindow::TAKE_RECTANGLE );
}

void core::setPixmap ( QPixmap &pixmap )
{
    picture = pixmap;
}
