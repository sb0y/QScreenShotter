#include "windowgrabberwindows.h"
#include "windowswindow.h"
#include "core.h"

windowGrabberWindows::windowGrabberWindows()
{
    wnd = NULL;
    //wnd.setMouseTracking ( true );
    //wnd.setWindowModality ( Qt::WindowModal );
   // setFocusPolicy ( Qt::StrongFocus );
    //wnd.setWindowFlags ( Qt::MSWindowsOwnDC | Qt::BypassWindowManagerHint | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint );

    //move ( 0, 0 );
    //setFixedSize(1000,1000);
    //wnd.setFixedSize ( system::getCore()->screen.size().width(), system::getCore()->screen.size().height() );
    //setWindowFlags(Qt::Widget | Qt::FramelessWindowHint);
   // setParent(0); // Create TopLevel-Widget
    //setAttribute(Qt::WA_NoSystemBackground, true);
    //setAttribute(Qt::WA_TranslucentBackground, true);
   // setAttribute(Qt::WA_PaintOnScreen);
    //QTthread *t = new QTthread;
    //t->setWorker ( new mouseSpy ( this ) );
    //t->start();
}

windowGrabberWindows::~windowGrabberWindows()
{
    delete wnd;
}

void windowGrabberWindows::windowUnderCursor ( bool includeDecorations )
{
    HWND child;
    int y,x;
    uint w, h;
    UINT cxWindowBorder, cyWindowBorder;

    POINT pointCursor;
    QPoint qpointCursor = QCursor::pos();
    pointCursor.x = qpointCursor.x();
    pointCursor.y = qpointCursor.y();
    HWND windowUnderCursor = WindowFromPoint ( pointCursor );

    if ( includeDecorations )
    {
        LONG_PTR style = GetWindowLongPtr ( windowUnderCursor, GWL_STYLE );

        if ( ( style & WS_CHILD ) != 0 )
        {
            windowUnderCursor = GetAncestor ( windowUnderCursor, GA_ROOT );
        }
    }

    child = windowUnderCursor;

    WINDOWINFO wi;
    GetWindowInfo ( child, &wi );

    RECT r;
    GetWindowRect ( child, &r );
    x = r.left;
    y = r.top;
    w = r.right - r.left;
    h = r.bottom - r.top;
    cxWindowBorder = wi.cxWindowBorders;
    cyWindowBorder = wi.cyWindowBorders;

    //HDC childDC = GetDC ( child );

    RECT windowRect;
    GetWindowRect ( child, &windowRect);
    w = windowRect.right - windowRect.left;
    h = windowRect.bottom - windowRect.top;
    HDC targetDC = GetWindowDC ( child );
    HDC hDC = CreateCompatibleDC ( targetDC );
    HBITMAP tempPic = CreateCompatibleBitmap ( targetDC, w, h );
    HGDIOBJ oldPic = SelectObject ( hDC, tempPic );
    BitBlt ( hDC, 0, 0, w, h, targetDC, 0, 0, SRCCOPY );
    tempPic = ( HBITMAP ) SelectObject ( hDC, oldPic );
    QPixmap pm ( QtWin::fromHBITMAP ( tempPic ) );

    DeleteDC ( hDC );
    ReleaseDC ( child, targetDC );

    getWindow ( "main", MainWindow* )->setScreenPic ( pm );
    system::getCore()->setPixmap ( pm );
}

void windowGrabberWindows::save()
{

}

void windowGrabberWindows::done()
{
    QApplication::restoreOverrideCursor();
    system::getCore()->toggleVisability();
    wnd->close();
    delete wnd;
    wnd = NULL;
}

void windowGrabberWindows::start()
{
    prepare();
}

void windowGrabberWindows::prepare()
{
   //exec();

   if ( wnd != NULL )
   {
       delete wnd;
       wnd = NULL;
   }

   wnd = new windowsWindow;
   wnd->setOwner ( this );
   wnd->setWindowFlags ( Qt::MSWindowsOwnDC | Qt::BypassWindowManagerHint | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint );
   wnd->setFixedSize ( system::getCore()->screen.size().width(), system::getCore()->screen.size().height() );
   wnd->setWindowModality ( Qt::WindowModal );
   wnd->setMouseTracking ( true );

   // winhack
   // window unactivable and unfocusable when clicking
   HWND winHandle = ( HWND ) wnd->winId();
   ShowWindow ( winHandle, SW_HIDE );

   SetWindowLong ( winHandle, GWL_EXSTYLE, GetWindowLong ( winHandle, GWL_EXSTYLE ) | WS_EX_NOACTIVATE | WS_EX_APPWINDOW | WS_EX_TRANSPARENT );
   SetWindowPos ( winHandle, HWND_TOPMOST, 0, 0, 0, 0, SWP_SHOWWINDOW | SWP_NOSIZE | SWP_NOMOVE ); // window-positioning options
   ShowWindow ( winHandle, SW_SHOW );

   //showFullScreen();
   QApplication::setOverrideCursor ( QCursor ( Qt::CrossCursor ) );

   //setFocus ( Qt::PopupFocusReason );
   //raise();
   //activateWindow();
   //grabMouse();
}

QPixmap* windowGrabberWindows::pixmap()
{
    return NULL;
}

/*void windowGrabberWindows::showEvent ( QShowEvent * )
{
}*/
