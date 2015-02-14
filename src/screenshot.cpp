#include "screenshot.h"
#include "core.h"

screenshot::screenshot ( core *c )
{
    main = c;
    wg = NULL, dg = NULL, rg = NULL;
}

screenshot::~screenshot()
{
    delete wg;
    delete dg;
    delete rg;
}

int screenshot::init()
{
    main->toggleVisability();
    return 1;
}

int screenshot::shootWindow()
{
    if ( NULL == wg )
    #ifdef HAVE_X11
        wg = new windowGrabberLinux;
    #endif

    if ( NULL != wg )
        QTimer::singleShot ( 400, wg, SLOT ( start() ) );

    return 1;
}

int screenshot::shootDesktop ( bool now )
{
    if ( NULL == dg )
    #ifdef HAVE_X11
        dg = new desktopGrabberLinux;
    #endif

    if ( NULL != dg )
    {
        if ( now )
        {
            dg->start();
        } else {
            QTimer::singleShot ( 400, dg, SLOT ( start() ) );
        }
    }

    return 1;
}

int screenshot::shootRectangle()
{
    if ( NULL == rg )
    #ifdef HAVE_X11
        rg = new rectangleGrabber;
    #endif

    if ( NULL != rg )
        QTimer::singleShot ( 400, rg, SLOT ( start() ) );

    return 1;
}
