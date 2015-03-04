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

    Gdiplus::GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    //erase the rectangle on desktop
    HWND dsk = GetDesktopWindow();

    Gdiplus::GdiplusStartup ( &gdiplusToken, &gdiplusStartupInput, NULL );
    HDC hdc = GetDC ( NULL );
    Gdiplus::Graphics graphics ( hdc );
    Gdiplus::Pen pen ( Gdiplus::Color::Red, 3 );
    //rec = location
    Gdiplus::Rect rec ( 20, 20, 248, 162 );
    Gdiplus::Status st = graphics.DrawRectangle ( &pen, rec );
    BOOL bl = FlashWindow ( dsk, FALSE );
    RedrawWindow ( dsk, NULL, NULL, RDW_ERASENOW |RDW_UPDATENOW|RDW_ALLCHILDREN );
    ReleaseDC ( NULL, hdc );

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
