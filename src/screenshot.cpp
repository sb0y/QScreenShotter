#include "screenshot.h"
#include "core.h"

screenshot::screenshot ( core *c )
{
    main = c;
    wgl = NULL, dgl = NULL, rg = NULL;
}

screenshot::~screenshot()
{
    delete wgl;
    delete dgl;
    delete rg;
}

int screenshot::init()
{
    main->toggleVisability();
    return 1;
}

int screenshot::shootWindow()
{
    if ( NULL == wgl )
        wgl = new windowGrabberLinux;

    QTimer::singleShot ( 400, wgl, SLOT ( start() ) );

    return 1;
}

int screenshot::shootDesktop ( bool now )
{
    if ( NULL == dgl )
        dgl = new desktopGrabberLinux;

    if ( now )
    {
        dgl->start();
    } else {
        QTimer::singleShot ( 400, dgl, SLOT ( start() ) );
    }

    return 1;
}

int screenshot::shootRectangle()
{
    if ( NULL == rg )
        rg = new rectangleGrabber;

    QTimer::singleShot ( 400, rg, SLOT ( start() ) );

    return 1;
}
