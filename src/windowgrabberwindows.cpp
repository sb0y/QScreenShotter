#include "windowgrabberwindows.h"
#include "core.h"

windowGrabberWindows::windowGrabberWindows()
{
    setMouseTracking ( true );
    setWindowModality ( Qt::WindowModal );
    setFocusPolicy ( Qt::StrongFocus );
    setEnabled ( true );
    //move ( 0, 0 );
    //setFixedSize(1000,1000);
    //setWindowFlags(Qt::Widget | Qt::FramelessWindowHint);
   // setParent(0); // Create TopLevel-Widget
    //setAttribute(Qt::WA_NoSystemBackground, true);
    //setAttribute(Qt::WA_TranslucentBackground, true);
   // setAttribute(Qt::WA_PaintOnScreen); // as pointed by Caveman (thanks!)
    //QTthread *t = new QTthread;
    //t->setWorker ( new mouseSpy ( this ) );
    //t->start();
}

windowGrabberWindows::~windowGrabberWindows()
{

}

static
void windowUnderCursor ( bool includeDecorations = true )
{
    HWND child;
    int y,x;
    uint w, h;
    UINT cxWindowBorder, cyWindowBorder;

    POINT pointCursor;
    QPoint qpointCursor = QCursor::pos();
    pointCursor.x = qpointCursor.x();
    pointCursor.y = qpointCursor.y();
    HWND windowUnderCursor = WindowFromPoint(pointCursor);

    if ( includeDecorations )
    {
        LONG_PTR style = GetWindowLongPtr ( windowUnderCursor, GWL_STYLE );

        if ( ( style & WS_CHILD ) != 0 )
        {
            windowUnderCursor = GetAncestor ( windowUnderCursor, GA_ROOT );
        }
    }

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

    HDC childDC = GetDC ( child );

    RECT windowRect;
    GetWindowRect ( child, &windowRect);
    w = windowRect.right - windowRect.left;
    h = windowRect.bottom - windowRect.top;
    HDC targetDC = GetWindowDC ( child );
    HDC hDC = CreateCompatibleDC ( targetDC );
    HBITMAP tempPict = CreateCompatibleBitmap ( targetDC, w, h );
    HGDIOBJ oldPict = SelectObject ( hDC, tempPict );
    BitBlt ( hDC, 0, 0, w, h, targetDC, 0, 0, SRCCOPY );
    tempPict = (HBITMAP) SelectObject ( hDC, oldPict );
    QPixmap pm ( QtWin::fromHBITMAP ( tempPict ) );

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
    releaseMouse();
    system::getCore()->toggleVisability();
}

void windowGrabberWindows::start()
{
    prepare();
}

void windowGrabberWindows::prepare()
{
   //exec();
   //showFullScreen();
   QApplication::setOverrideCursor ( QCursor ( Qt::CrossCursor ) );

   setFocus ( Qt::PopupFocusReason );
   raise();
   activateWindow();
   grabMouse();
}

void windowGrabberWindows::mouseMoveEvent ( QMouseEvent *e )
{
    qDebug() << "mouse move";
    e->ignore();
}

void windowGrabberWindows::mousePressEvent ( QMouseEvent *e )
{
    e->ignore();
    windowUnderCursor();
    done();
}

bool windowGrabberWindows::eventFilter( QObject *o, QEvent *e )
{
    e->ignore();
    return false;
}

/*void windowGrabberWindows::showEvent ( QShowEvent * )
{
}*/
