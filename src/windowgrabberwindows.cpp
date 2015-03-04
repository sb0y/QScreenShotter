#include "windowgrabberwindows.h"
#include "windowswindow.h"
#include "core.h"

windowGrabberWindows::windowGrabberWindows()
{
    wnd = NULL;
}

windowGrabberWindows::~windowGrabberWindows()
{
    delete wnd;
}

void windowGrabberWindows::windowUnderCursor ( bool includeDecorations )
{
    int y, x;
    uint w, h;
    UINT cxWindowBorder, cyWindowBorder;

    POINT pointCursor;
    QPoint qpointCursor = QCursor::pos();
    pointCursor.x = qpointCursor.x();
    pointCursor.y = qpointCursor.y();
    HWND windowUnderCursor = WindowFromPoint ( pointCursor );
    HWND root = GetAncestor ( windowUnderCursor, GA_ROOT );

    if ( includeDecorations )
    {
        LONG_PTR style = GetWindowLongPtr ( windowUnderCursor, GWL_STYLE );

        if ( ( style & WS_CHILD ) != 0 )
        {
            windowUnderCursor = root;
        }
    }

    QPixmap pm;

    if ( root == windowUnderCursor )
    {
        windowUnderCursor = GetDesktopWindow();
    }
    //child = windowUnderCursor;

    WINDOWINFO wi;
    GetWindowInfo ( windowUnderCursor, &wi );

    cxWindowBorder = wi.cxWindowBorders;
    cyWindowBorder = wi.cyWindowBorders;

    //HDC childDC = GetDC ( child );

    RECT windowRect;

    GetWindowRect ( windowUnderCursor, &windowRect );

    w = ( windowRect.right - windowRect.left );
    h = ( windowRect.bottom - windowRect.top );

    /*HDC targetDC = GetWindowDC ( windowUnderCursor );
      HDC hDC = CreateCompatibleDC ( targetDC );

      HBITMAP tempPic = CreateCompatibleBitmap ( targetDC, w, h );

      HGDIOBJ oldPic = SelectObject ( hDC, tempPic );

      BitBlt ( hDC, 0, 0, w, h, targetDC, 0, 0, SRCCOPY );
      tempPic = ( HBITMAP ) SelectObject ( hDC, oldPic ); */

     QPixmap screen = qApp->primaryScreen()->grabWindow ( QApplication::desktop()->winId() );
     pm = screen.copy ( windowRect.left, windowRect.top, w, h );

     //DeleteDC ( hDC );
     //DeleteObject ( tempPic );
     //ReleaseDC ( windowUnderCursor, targetDC );

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
