#include "desktopgrabberlinux.h"
#include "core.h"

desktopGrabberLinux::desktopGrabberLinux()
{
    //setMouseTracking ( true );
    //setWindowModality( Qt::WindowModal );
    //setFixedSize ( 0, 0 );
}

desktopGrabberLinux::~desktopGrabberLinux()
{

}

void desktopGrabberLinux::prepare()
{
    //QApplication::setOverrideCursor ( QCursor ( Qt::CrossCursor ) );
    //exec();
}

void desktopGrabberLinux::mousePressEvent ( QMouseEvent *e )
{
    Q_UNUSED ( e );
    //done();
    e->accept();
}

void desktopGrabberLinux::done()
{
    QList < QScreen *> screens = QGuiApplication::screens();
    QList < QScreen *>::iterator i = screens.begin();

    for ( ; i != screens.end(); ++i )
    {
        QPixmap qpix = (*i)->grabWindow ( 0, 0, 0, -1, -1 );
        getWindow ( "main", MainWindow* )->setScreenPic ( qpix );
        system::getCore()->setPixmap ( qpix );
    }

    //QDialog::close();
    //QApplication::restoreOverrideCursor();
    system::getCore()->toggleVisability();
}

void desktopGrabberLinux::start()
{
    prepare();
    done();
}
