#include "screenshot.h"
#include "core.h"

screenshot::screenshot ( core *c )
{
    main = c;
    wg = NULL, dg = NULL, rg = NULL;
    currentGrabber = NULL;
    timeout = 0;
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
    #elif WIN32
        wg = new windowGrabberWindows;
    #endif

    if ( NULL != wg )
    {
        currentGrabber = wg;
        QTimer::singleShot ( timeout, this, SLOT ( startCurrentGrabber() ) );
    }

    return 1;
}

int screenshot::shootDesktop ( bool now )
{
    if ( NULL == dg )
       dg = new desktopGrabber;

    if ( NULL != dg )
    {
        if ( now )
        {
            dg->start();
        } else {
            currentGrabber = dg;
            QTimer::singleShot ( timeout, this, SLOT ( startCurrentGrabber() ) );
        }
    }

    return 1;
}

int screenshot::shootRectangle()
{
    if ( NULL == rg )
        rg = new rectangleGrabber;

    if ( NULL != rg )
    {
        currentGrabber = rg;
        QTimer::singleShot ( timeout, this, SLOT ( startCurrentGrabber() ) );
    }

    return 1;
}

void screenshot::startCurrentGrabber()
{
    if ( NULL != currentGrabber )
    {
        currentGrabber->start();
        currentGrabber = NULL;
    }
}

void screenshot::setTimeout ( int val )
{
    timeout = val;
}
