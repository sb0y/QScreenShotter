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

bool windowsWindow::drawRectangle (int x, int y, int w, int h )
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

    ReleaseDC ( NULL, hdc );

    return true;
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

    HWND dsk = GetDesktopWindow();

    for ( int i = 0; owner->windows.size() > i; ++i )
    {
        windowUnderCursor = NULL;

        if ( dsk == owner->windows [ i ].winId )
        {
            continue;
        }

        if ( PtInRect ( owner->windows [ i ].rect, pointCursor ) )
        {
            windowUnderCursor = owner->windows [ i ].winId;
            rect = owner->windows [ i ].rect;
            break;
        }
    }

    if ( NULL != windowUnderCursor )
    {
        if ( GetAncestor ( windowUnderCursor, GA_ROOT ) == windowUnderCursor )
        {
            SystemParametersInfo ( SPI_GETWORKAREA, 0, rect, 0 );
        }

        w = rect->right - rect->left;
        h = rect->bottom - rect->top;
        x = rect->left;
        y = rect->top;

        //qDebug() << x << y << w << h;

        if ( highlightedWindow != windowUnderCursor )
        {
            if ( NULL != highlightedWindow )
            {
                eraseRectangle();
            }

            if ( drawRectangle ( x, y, w, h ) )
            {
                highlightedWindow = windowUnderCursor;
                highlightedWindowRECT = *rect;
                //SetActiveWindow ( windowUnderCursor );
                //SetFocus ( windowUnderCursor );
            }
        }
    } else {

        if ( NULL != highlightedWindow )
        {
            eraseRectangle();
        }
   }
}

void windowsWindow::eraseRectangle()
{
    if ( NULL == highlightedWindow )
        return;

    RECT rectUpd;

    rectUpd = highlightedWindowRECT;

    rectUpd.left -= 2;
    rectUpd.right += 2;
    rectUpd.top -= 2;
    rectUpd.bottom += 2;

    //RedrawWindow ( highlightedWindow, rect, NULL, RDW_ERASE|RDW_INVALIDATE|RDW_ALLCHILDREN );
    //RedrawWindow ( NULL, rect, NULL, RDW_ERASENOW|RDW_ERASE|RDW_INVALIDATE|RDW_ALLCHILDREN );

    RedrawWindow ( highlightedWindow, &rectUpd, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_ALLCHILDREN );
    RedrawWindow ( NULL, &rectUpd, NULL, RDW_ERASENOW | RDW_ERASE | RDW_INVALIDATE | RDW_ALLCHILDREN );

    FlashWindow ( highlightedWindow, FALSE );

    highlightedWindow = NULL;
    highlightedWindowRECT = {0,0,0,0};
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
