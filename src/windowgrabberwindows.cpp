#include "windowgrabberwindows.h"
#include "windowswindow.h"
#include "core.h"
#include <iostream>

windowGrabberWindows *windowGrabberWindows::self;

windowGrabberWindows::windowGrabberWindows()
{
    wnd = NULL;
    self = this;
}

windowGrabberWindows::~windowGrabberWindows()
{
    delete wnd;
    clearTrackedWindows();
}

void windowGrabberWindows::clearTrackedWindows()
{
    for ( unsigned int i = 0; windows.size() > i; ++i )
    {
        delete windows [ i ].rect;
    }

    //std::for_each ( windows.begin(), windows.end(), std::default_delete < RECT >() );

    windows.clear();
}

void windowGrabberWindows::windowUnderCursor ( bool includeDecorations )
{
    int y, x;
    uint w, h;

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

    WINDOWINFO wi;
    GetWindowInfo ( windowUnderCursor, &wi );

    //cxWindowBorder = wi.cxWindowBorders;
    //cyWindowBorder = wi.cyWindowBorders;

    //HDC childDC = GetDC ( child );

    RECT windowRect;

    GetWindowRect ( windowUnderCursor, &windowRect );

    if ( GetAncestor ( windowUnderCursor, GA_ROOT ) == windowUnderCursor )
    {
        SystemParametersInfo ( SPI_GETWORKAREA, 0, &windowRect, 0 );
    }

    w = windowRect.right - windowRect.left;
    h = windowRect.bottom - windowRect.top;
    x = windowRect.left;
    y = windowRect.top;

    qDebug() << "taked: " << x << y << w << h;

    /*HDC targetDC = GetWindowDC ( windowUnderCursor );
      HDC hDC = CreateCompatibleDC ( targetDC );

      HBITMAP tempPic = CreateCompatibleBitmap ( targetDC, w, h );

      HGDIOBJ oldPic = SelectObject ( hDC, tempPic );

      BitBlt ( hDC, 0, 0, w, h, targetDC, 0, 0, SRCCOPY );
      tempPic = ( HBITMAP ) SelectObject ( hDC, oldPic ); */

     pm = _pixmap.copy ( x, y, w, h );

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

   clearTrackedWindows();
   getAllAvailableWindows();

   _pixmap = qApp->primaryScreen()->grabWindow ( QApplication::desktop()->winId() );

   if ( wnd != NULL )
   {
       delete wnd;
       wnd = NULL;
   }

   wnd = new windowsWindow;
   wnd->setOwner ( this );
   //wnd->setAttribute ( Qt::WA_TransparentForMouseEvents, true );
   wnd->setWindowFlags ( Qt::BypassWindowManagerHint | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint );
   wnd->setFixedSize ( system::getCore()->screen.size().width(), system::getCore()->screen.size().height() );
   wnd->setWindowModality ( Qt::WindowModal );
   wnd->setFocusPolicy ( Qt::NoFocus );
   wnd->setMouseTracking ( true );

   // winhack
   // window unactivable and unfocusable when clicking
   HWND winHandle = ( HWND ) wnd->winId();
   //HDC hdc = GetDC ( winHandle ); // Get its DC.
   //EnableWindow ( winHandle, false );
   ShowWindow ( winHandle, SW_HIDE );

   LONG styles = GetWindowLong ( winHandle, GWL_EXSTYLE );

   SetWindowLong ( winHandle, GWL_EXSTYLE, styles | WS_EX_NOACTIVATE | WS_EX_APPWINDOW | WS_EX_TRANSPARENT );
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
    return &_pixmap;
}

WId windowGrabberWindows::winId()
{
    if ( wnd == NULL )
    {
        return NULL;
    }

    return wnd->winId();
}

BOOL CALLBACK windowGrabberWindows::EnumWindowsProc ( HWND hwnd, LPARAM lParam )
{
    Q_UNUSED ( lParam );

    if ( IsWindowVisible ( hwnd ) && IsWindowEnabled ( hwnd ) )
    {
        wchar_t class_name [ 80 ];
        wchar_t title [ 80 ];
        GetClassName ( hwnd, class_name, sizeof ( class_name ) );
        GetWindowText ( hwnd, title, sizeof ( title ) );

        if ( _wcsicmp ( class_name, L"Shell_TrayWnd" ) &&
             _wcsicmp ( class_name, L"Progman" ) &&
             _wcsicmp ( class_name, L"EdgeUiInputTopWndClass" ) )
        {
            //std::wcout << "Window title: " << title << std::endl;
            //std::wcout << "Class name: " << class_name << std::endl;

            RECT *rect = new RECT;
            GetWindowRect ( hwnd, rect );
            self->windows.push_back ( winInfo ( hwnd, rect ) );
        }
    }

   return TRUE;
}

void windowGrabberWindows::getAllAvailableWindows()
{
    EnumWindows ( EnumWindowsProc, NULL );
}

/*void windowGrabberWindows::showEvent ( QShowEvent * )
{
}*/
