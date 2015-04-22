#include "core.h"
#include <qdebug.h>

core::core ( int &argc, char *argv[] ) :
    QApplication ( argc, argv )
{    
    setApplicationName ( QObject::tr ( "qsc" ) );
    setApplicationDisplayName ( QObject::tr ( "QScreenShotter" ) );
    setApplicationVersion ( QObject::tr ( "0.1b" ) );
    setOrganizationName ( QObject::tr ( "andrey@bagrintsev.me" ) );
    setOrganizationDomain ( QObject::tr ( "bagrintsev.me" ) );
    setWindowIcon ( QIcon ( ":/tray/images/tray32x32.png" ) );

    setAttribute ( Qt::AA_NativeWindows, true );
    //setAttribute ( Qt::AA_X11InitThreads, true );

    isVisible = true;

    #if defined(HAVE_X11) || defined(WIN32)
    installNativeEventFilter ( new NewEventFilter );
    #endif

    sc = NULL;

    QString path;
    #ifdef HAVE_X11
    path = QDir::homePath() + "/.config/QScreenShotter/config.conf";
    #elif WIN32
    path = QStandardPaths::writableLocation ( QStandardPaths::DataLocation ) + "/config.conf";
    #endif

    settings = new QSettings ( path, QSettings::IniFormat );
}

core::~core()
{
    std::map < QString, QWidget* >::iterator i;

    for ( i = windows.begin(); i != windows.end(); ++i )
    {
        //delete i->second;
        //i->second = NULL;
        if ( NULL == i->second )
        {
            continue;
        }

        i->second->deleteLater();
    }

    delete trayMenu;
    delete trayIcon;
    delete sc;

    settings->sync();

    delete settings;
}

void core::defaultSettings()
{
    struct container
    {
        const char *key;
        const char *val;
    };

    container pack[] =
    {
        { "WEB/site", "bagrintsev.me" },
        { "WEB/accessToken", "" },
        { "main/timeout", "300" },
        { NULL, NULL } // end
    };

    for ( int i = 0; pack [ i ].key != NULL; ++i )
    {
        if ( settings->value ( pack [ i ].key ).isNull() )
        {
            settings->setValue ( pack [ i ].key, pack [ i ].val );
        }
    }
}

int core::exec()
{
    MainWindow *mw = new MainWindow;
    windows [ "main" ] = mw;

    initTray();

    if ( NULL == sc )
    {
        sc = new screenshot ( this );
        sc->setTimeout ( settings->value ( "main/timeout" ).toInt() );
    }

    #ifdef WIN32
    mw->show();
    mw->setHidden ( true );
    #endif

    sc->shootDesktop ( true );

    #ifdef WIN32
    mw->setHidden ( false );
    #elif HAVE_X11
    mw->show();
    #endif

    mw->init ( this );

    screen = qApp->primaryScreen()->geometry();

    defaultSettings();

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

    trayIcon->setIcon ( QIcon ( ":/tray/images/tray32x32.png" ) );
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
                if ( NULL == i->second )
                {
                    continue;
                }

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

void core::exportToWEB()
{
    if ( picture.isNull() )
    {
        return;
    }

    if ( settings->value ( "WEB/accessToken" ).toString().isEmpty() )
    {
        openSettingsDialog();
        return;
    }

    exportDialog *ep = new exportDialog ( windows [ "main" ] );
    windows [ "export" ] = ep;

    ep->show();
}

void core::showExportResult ( QString big, QString small, QString userID )
{
    exportResult *er = new exportResult ( windows [ "main" ] );
    windows [ "exportResult" ] = er;

    er->setResult ( big, small, userID );
    er->show();
}

void core::openSettingsDialog()
{
    settingsDialog *sd = new settingsDialog ( windows [ "main" ] );
    windows [ "settingsDialog" ] = sd;
    sd->show();
}

void core::showAbout()
{
    QDialog *d = new aboutDialog;
    d->show();
    windows [ "about" ] = d;
}
