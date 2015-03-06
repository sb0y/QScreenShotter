#include "windowswindow.h"

windowsWindow::windowsWindow()
{
    owner = NULL;
    installEventFilter ( this );
    mm = -1;
    highlightedWindow = NULL;
}

windowsWindow::~windowsWindow()
{

}

bool windowsWindow::drawRectangle ( int x, int y, int w, int h )
{
    Gdiplus::GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    //erase the rectangle on desktop
    HWND dsk = GetDesktopWindow();

    Gdiplus::GdiplusStartup ( &gdiplusToken, &gdiplusStartupInput, NULL );
    HDC hdc = GetDC ( NULL );
    Gdiplus::Graphics graphics ( hdc );
    Gdiplus::Pen pen ( Gdiplus::Color::Red, 3 );
    //rec = location
    Gdiplus::Rect rec ( x, y, w, h );
    Gdiplus::Status st = graphics.DrawRectangle ( &pen, rec );
    BOOL bl = FlashWindow ( dsk, FALSE );
    RedrawWindow ( dsk, NULL, NULL, RDW_ERASENOW | RDW_UPDATENOW );

    ReleaseDC ( NULL, hdc );

    return bl;
}

void windowsWindow::timerEvent ( QTimerEvent *e )
{
    mm = 1;
    mouseTick();
    e->accept();
}

void windowsWindow::mouseTick()
{
    //qDebug() << "mouse move";

    int y = 0, x = 0;
    uint w = 0, h = 0;

    HWND windowUnderCursor = NULL;
    RECT *rect = NULL;

    POINT pointCursor;
    QPoint qpointCursor = QCursor::pos();
    pointCursor.x = qpointCursor.x();
    pointCursor.y = qpointCursor.y();

    for ( int i = 0; owner->windows.size() > i; ++i )
    {
        if ( PtInRect ( owner->windows [ i ].rect, pointCursor ) )
        {
            windowUnderCursor = owner->windows [ i ].winId;
            rect = owner->windows [ i ].rect;
            break;
        }
    }

    w = ( rect->right - rect->left );
    h = ( rect->bottom - rect->top );
    x = rect->left;
    y = rect->top;

    //qDebug() << x << y << w << h;

    if ( highlightedWindow != windowUnderCursor )
    {
        if ( drawRectangle ( x, y, w, h ) )
        {
            highlightedWindow = windowUnderCursor;
        }
    }
}

void windowsWindow::mouseMoveEvent ( QMouseEvent *e )
{
    if ( mm == 0 )
        return;

    e->ignore();

    mm = 0;
    QObject::startTimer ( 0 );
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
   // e->ignore();

    if ( e->type() == QEvent::MouseMove )
    {
        e->ignore();
        return false;
    }

    return QDialog::eventFilter ( o, e );
}

void windowsWindow::setOwner ( windowGrabberWindows *w )
{
    owner = w;
}
