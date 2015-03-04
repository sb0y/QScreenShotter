#include "windowswindow.h"

windowsWindow::windowsWindow()
{
    owner = NULL;
}

windowsWindow::~windowsWindow()
{

}

void windowsWindow::mouseMoveEvent ( QMouseEvent *e )
{
    qDebug() << "mouse move";
    e->ignore();
}

void windowsWindow::mousePressEvent ( QMouseEvent *e )
{
    qDebug() << "mouse press";
    e->ignore();
    ShowWindow ( ( HWND ) winId(), SW_HIDE );
    owner->windowUnderCursor();
    CloseWindow ( ( HWND ) winId() );

    assert ( NULL != owner );
    owner->done();
}

bool windowsWindow::eventFilter ( QObject *o, QEvent *e )
{
    qDebug() << "here";
    e->ignore();
    return false;
}

void windowsWindow::setOwner ( windowGrabberWindows *w )
{
    owner = w;
}
