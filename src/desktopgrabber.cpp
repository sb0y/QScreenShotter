#include "desktopgrabber.h"
#include "core.h"

desktopGrabber::desktopGrabber()
{
    //setMouseTracking ( true );
    //setWindowModality( Qt::WindowModal );
    //setFixedSize ( 0, 0 );
}

desktopGrabber::~desktopGrabber()
{

}

void desktopGrabber::prepare()
{
    //QApplication::setOverrideCursor ( QCursor ( Qt::CrossCursor ) );
    //exec();
}

void desktopGrabber::mousePressEvent ( QMouseEvent *e )
{
    Q_UNUSED ( e );
    //done();
    e->accept();
}

void desktopGrabber::done()
{
    QList < QScreen *> screens = QGuiApplication::screens();
    QList < QScreen *>::iterator i = screens.begin();

    for ( ; i != screens.end(); ++i )
    {
        QPixmap qpix = qApp->primaryScreen()->grabWindow ( QApplication::desktop()->winId() );
        getWindow ( "main", MainWindow* )->setScreenPic ( qpix );
        system::getCore()->setPixmap ( qpix );
    }

    //QDialog::close();
    //QApplication::restoreOverrideCursor();
    system::getCore()->toggleVisability();
}

void desktopGrabber::start()
{
    prepare();
    done();
}

void desktopGrabber::showEvent ( QShowEvent * )
{

}


void desktopGrabber::hideEvent ( QHideEvent * )
{

}

QPixmap* desktopGrabber::pixmap()
{
    return NULL;
}
