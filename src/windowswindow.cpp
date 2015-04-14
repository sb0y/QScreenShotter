#include "windowswindow.h"

windowsWindow::windowsWindow()
{
    owner = NULL;
    installEventFilter ( this );
    mm = -1;
    highlightedWindow = NULL;
    test();
}

windowsWindow::~windowsWindow()
{

}

bool windowsWindow::drawRectangle (int x, int y, int w, int h )
{
    Gdiplus::GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    //HWND dsk = GetDesktopWindow();

    Gdiplus::GdiplusStartup ( &gdiplusToken, &gdiplusStartupInput, NULL );
    HDC hdc = GetDC ( (HWND)winId() );

    //SetBkMode ( hdc, TRANSPARENT );

    Gdiplus::Graphics graphics ( hdc );
    Gdiplus::Pen pen ( Gdiplus::Color::Red, 3 );
    //rec = location
    Gdiplus::Rect rec ( x, y, w, h );
    Gdiplus::Status st = graphics.DrawRectangle ( &pen, rec );

    //graphics.Clear ( Gdiplus::Color::Transparent );

    ReleaseDC ( NULL, hdc );

    LockWindowUpdate ( (HWND)winId() );

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

    WINDOWPLACEMENT wp;
    wp.length = sizeof ( wp );

    for ( unsigned int i = 0; owner->windows.size() > i; ++i )
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
        //qDebug() << windowUnderCursor;
        //qDebug() << GetAncestor ( windowUnderCursor, GA_ROOT );

        GetWindowPlacement ( windowUnderCursor, &wp );

        if ( wp.showCmd == SW_SHOWMAXIMIZED )
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
                SetForegroundWindow ( windowUnderCursor );
                highlightedWindow = windowUnderCursor;
                highlightedWindowRECT = *rect;
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

    LockWindowUpdate ( NULL );

    ShowWindow ( (HWND)winId(), SW_HIDE );
    ShowWindow ( (HWND)winId(), SW_SHOW );

    highlightedWindow = NULL;
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
    //qDebug() << "mouse press";
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

void windowsWindow::test()
{
}
