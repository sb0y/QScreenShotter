#include "windowgrabberwindows.h"

windowGrabberWindows::windowGrabberWindows()
{
    setMouseTracking ( true );
    setWindowModality( Qt::WindowModal );
}

windowGrabberWindows::~windowGrabberWindows()
{

}

void windowGrabberWindows::save()
{

}

void windowGrabberWindows::done()
{

}

void windowGrabberWindows::start()
{

}

void windowGrabberWindows::prepare()
{

}

void windowGrabberWindows::mouseMoveEvent ( QMouseEvent *e )
{
    e->ignore();
}

void windowGrabberWindows::mousePressEvent ( QMouseEvent *e )
{
    e->ignore();
}
