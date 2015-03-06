#include "windowgrabberlinux.h"
#include <QDebug>
#include "mainwindow.h"
#include "core.h"
#ifdef HAVE_X11
    #include <X11/Xlib.h>
    #include <X11/Xatom.h>
    #include <X11/Xutil.h>
    #include <X11/extensions/Xfixes.h>
    #include <X11/extensions/shape.h>
    #include <QX11Info>
#endif
#include <QDesktopWidget>

//#include "customframe.h"
//include "X11Info.h"

windowGrabberLinux::windowGrabberLinux()
{
    setMouseTracking ( true );
    setWindowModality ( Qt::WindowModal );
   // setAttribute ( Qt::WA_NoSystemBackground, true );

    setFixedSize ( 0, 0 );

    //customFrame *f = new customFrame ( NULL, Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::X11BypassWindowManagerHint | Qt::Popup );

    splashWnd = new QDialog ( NULL, Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint );
    splashWnd->setAttribute ( Qt::WA_NoSystemBackground, true );
    splashWnd->move ( 0, 0 );
    splashWnd->setMouseTracking ( false );
    //splashWnd->setWindowModality ( Qt::WindowModal );
    splashWnd->setFixedSize ( system::getCore()->screen.width(), system::getCore()->screen.height() );
    splashWnd->setFocusPolicy ( Qt::NoFocus );
    splashWnd->setAttribute ( Qt::WA_TransparentForMouseEvents, true );

    layout = new QHBoxLayout ( splashWnd );
    splashWnd->setLayout ( layout );
    label = new QLabel ( splashWnd );
    layout->addWidget ( label );
    layout->setContentsMargins ( 0, 0, 0, 0 );

    /*system::getCore()->rect.setXY(50,50);
    system::getCore()->rect.setWH(400,400);
    system::getCore()->rect.draw();*/

    //setFixedSize ( 0, 0 );
    //setAttribute ( Qt::WA_TranslucentBackground );
    //setStyleSheet ( "background:transparent;" );
    /* create window */

   /* Display *d = QX11Info::display();
    int s = QX11Info::appScreen();

    Window w = XCreateSimpleWindow(
                d,
                RootWindow(d, s),
                0, 0, 600, 600, 0,
                None,
                None
           );

    enum
    {
        WM_HINTS_FUNCTIONS = (1L << 0),
        WM_HINTS_DECORATIONS =  (1L << 1),

        WM_FUNC_ALL = (1L << 0),
        WM_FUNC_RESIZE = (1L << 1),
        WM_FUNC_MOVE = (1L << 2),
        WM_FUNC_MINIMIZE = (1L << 3),
        WM_FUNC_MAXIMIZE = (1L << 4),
        WM_FUNC_CLOSE = (1L << 5)
    };

    struct WindowHints
    {
        unsigned long flags, functions, decorations, status;
        long input_mode;
    };

    Atom wmHintsProperty = XInternAtom(d, "_MOTIF_WM_HINTS", 0);
    struct WindowHints hints;
    hints.flags = WM_HINTS_DECORATIONS;
    hints.decorations = 0;
    XChangeProperty
    (
        d,
        w,
        wmHintsProperty,
        wmHintsProperty,
        32,
        PropModeReplace,
        (unsigned char *)&hints,
        5
    );

    Atom WindowType = XInternAtom(d, "_NET_WM_WINDOW_TYPE", False);
    Atom DialogType = XInternAtom(d, "_NET_WM_WINDOW_TYPE_DIALOG", False);
    XChangeProperty(
        d,
        w,
        WindowType,
        XA_ATOM,
        32,
        PropModeReplace,
        reinterpret_cast<unsigned char*>(&DialogType), 1
    );

    XGCValues gc_val;
    GC gc_line;

    gc_val.function           = GXxor;
    gc_val.plane_mask         = AllPlanes;
    gc_val.foreground         = WhitePixel ( d, s );
    gc_val.background         = BlackPixel ( d, s );
    gc_val.line_width         = 4;
    gc_val.line_style         = LineSolid;
    gc_val.cap_style          = CapButt;
    gc_val.join_style         = JoinMiter;
    gc_val.fill_style         = FillOpaqueStippled;
    gc_val.fill_rule          = WindingRule;
    gc_val.graphics_exposures = False;
    gc_val.clip_x_origin      = 0;
    gc_val.clip_y_origin      = 0;
    gc_val.clip_mask          = None;
    gc_val.subwindow_mode     = IncludeInferiors;

    //XGrabServer ( display );

    gc_line = XCreateGC ( d, w, GCFunction | GCPlaneMask |  GCForeground | GCBackground | GCLineWidth | GCLineStyle |
                GCCapStyle  | GCJoinStyle  |  GCFillStyle  |  GCFillRule  |  GCGraphicsExposures |
                GCClipXOrigin |  GCClipYOrigin  |  GCClipMask  | GCSubwindowMode, &gc_val );

    XDrawRectangle ( d, w, gc_line, 0, 0, 100, 100 );

    XMapWindow(d, w);
    XFlush ( d ); */
}

bool windowGrabberLinux::eventFilter ( QObject *o, QEvent *e )
{
    Q_UNUSED ( o );
    e->ignore();
    //QApplication::instance()->postEvent(e);
    return false;
}

windowGrabberLinux::~windowGrabberLinux()
{
    delete splashWnd;
}

void windowGrabberLinux::keyPressEvent ( QKeyEvent *e )
{
    switch ( e->key() )
    {
        case Qt::Key_Escape:

            done();
            e->accept();

        break;

        case Qt::Key_Return:
        case Qt::Key_Enter:

            done();
            e->accept();

        break;

        default:
            e->ignore();
        break;
    }
}

static
Window findRealWindow ( Window w, int depth = 0 )
{
    if ( depth > 5 )
    {
        return None;
    }

    static Atom wm_state = XInternAtom ( QX11Info::display(), "WM_STATE", False );
    Atom type;
    int format;
    unsigned long nitems, after;
    unsigned char* prop;

    if ( XGetWindowProperty ( QX11Info::display(), w, wm_state, 0, 0, False, AnyPropertyType,
                               &type, &format, &nitems, &after, &prop ) == Success )
    {
        if ( prop != NULL )
        {
            XFree ( prop );
        }

        if ( type != None )
        {
            return w;
        }
    }

    Window root, parent;
    Window* children;
    unsigned int nchildren;
    Window ret = None;

    if ( XQueryTree ( QX11Info::display(), w, &root, &parent, &children, &nchildren ) != 0 )
    {
        for ( unsigned int i = 0;
            i < nchildren && ret == None;
              ++i )
        {
            ret = findRealWindow ( children [ i ], depth + 1 );
        }

        if ( children != NULL )
        {
            XFree ( children );
        }
    }

    return ret;
}

void windowGrabberLinux::start()
{
    prepare();
    exec();

    QTimer::singleShot ( 400, this, SLOT ( mouseTick() ) );

    /*xcb_connection_t *c = xcb_connect ( NULL, NULL );

    // get the first screen
    xcb_screen_t *screen = xcb_setup_roots_iterator (xcb_get_setup (c)).data;

    xcb_window_t win = xcb_generate_id ( c );

    xcb_create_window ( c,                             // Connection
                        XCB_COPY_FROM_PARENT,          // depth (same as root)
                        win,                           // window Id
                        screen->root,                  // parent window
                        0, 0,                          // x, y
                        system::getCore()->screen.width(), // width
                        system::getCore()->screen.height(), // height
                        0,                            // border_width
                        XCB_WINDOW_CLASS_INPUT_OUTPUT, // class
                        screen->root_visual,           // visual
                        0,                             //
                        NULL );                     // masks


    xcb_intern_atom_cookie_t cookie = xcb_intern_atom ( c, 0, strlen ( "_NET_WM_WINDOW_TYPE_SPLASH" ), "_NET_WM_WINDOW_TYPE_SPLASH" );
    xcb_intern_atom_reply_t *reply = xcb_intern_atom_reply ( c, cookie, NULL );

    xcb_change_property ( c,
                         XCB_PROP_MODE_REPLACE,
                         win,
                         (*reply).atom,
                         XCB_ATOM_INTEGER,
                         32,
                         0,
                         XCB_NONE );

    XserverRegion region = XFixesCreateRegion ( QX11Info::display(), NULL, 0 );
    XFixesSetWindowShapeRegion ( QX11Info::display(), win, ShapeBounding, 0, 0, 0 );
    XFixesSetWindowShapeRegion ( QX11Info::display(), win, ShapeInput, 0, 0, region );
    XFixesDestroyRegion ( QX11Info::display(), region );

    xcb_map_window ( c, win );
    xcb_flush ( c );*/

    //qDebug() << win;
}

void windowGrabberLinux::prepare()
{
    _pixmap = qApp->primaryScreen()->grabWindow ( QApplication::desktop()->winId() );

    label->setPixmap ( _pixmap );
    splashWnd->show();

    XserverRegion region = XFixesCreateRegion ( QX11Info::display(), NULL, 0 );

    XFixesSetWindowShapeRegion ( QX11Info::display(), splashWnd->effectiveWinId(), ShapeBounding, 0, 0, 0 );
    XFixesSetWindowShapeRegion ( QX11Info::display(), splashWnd->effectiveWinId(), ShapeInput, 0, 0, region );
    XFixesDestroyRegion ( QX11Info::display(), region );

    QApplication::setOverrideCursor ( QCursor ( Qt::CrossCursor ) );
    //system::getCore()->rect.draw();
}

void windowGrabberLinux::windowUnderCursor()
{
    Window root;
    Window child;
    uint mask;
    int rootX, rootY, winX, winY;
    uint border, depth;
    uint w, h;
    int x, y;

    Display *ds = QX11Info::display();

    XGrabServer ( ds );

    XQueryPointer ( ds, QX11Info::appRootWindow(), &root, &child, &rootX, &rootY, &winX, &winY, &mask );

    if ( child == None )
    {
        child = QX11Info::appRootWindow();
    }

    //child = findRealWindow ( child );

    XGetGeometry ( ds, child, &root, &x, &y, &w, &h, &border, &depth );

   // XTranslateCoordinates ( ds, child, QX11Info::appRootWindow(),  );

    XUngrabServer ( ds );

    //qDebug() << x << y << w << h;

    //QPixmap pm ( qApp->primaryScreen()->grabWindow ( child ) );
    QPixmap pm ( _pixmap.copy ( x, y, w, h ) );

    getWindow ( "main", MainWindow* )->setScreenPic ( pm );
    system::getCore()->setPixmap ( pm );
}

void windowGrabberLinux::done()
{
    splashWnd->close();
    close();
    QApplication::restoreOverrideCursor();
    system::getCore()->toggleVisability();
}

void windowGrabberLinux::mousePressEvent ( QMouseEvent *event )
{
    Q_UNUSED ( event );
    //if ( event->button() == Qt::LeftButton )
    //{
       windowUnderCursor();
       done();
    //}
    //event->accept();
}

void windowGrabberLinux::paintEvent ( QPaintEvent *e )
{
    e->ignore();
}

void windowGrabberLinux::mouseMoveEvent ( QMouseEvent *event )
{
    Q_UNUSED ( event );
    mouseTick();
    event->accept();
}

void windowGrabberLinux::mouseTick()
{
    Window root;

    Window child;
    uint mask;
    int rootX, rootY, winX, winY;
    uint border, depth = 32;
    uint w, h;
    int x, y;

    Display *ds = QX11Info::display();

    XQueryPointer ( ds, QX11Info::appRootWindow(), &root, &child, &rootX, &rootY, &winX, &winY, &mask );

    if ( child == None )
    {
        return;
    }

    //QPoint p = mapFromGlobal ( QCursor::pos() );

    XGetGeometry ( ds, child, &root, &x, &y, &w, &h, &border, &depth );

    drawOnLayer ( x, y, w, h );
}

void windowGrabberLinux::drawOnLayer ( int x, int y, int w, int h )
{
    QPixmap pm ( _pixmap );
    painter.begin ( &pm );
    //painter.setRenderHint ( QPainter::Antialiasing, true );
    pen.setColor ( Qt::red );
    pen.setWidth ( 3 );
    painter.setPen ( pen );
    QRect rect ( x+1, y+1, w-3, h-3 );
    painter.drawRoundedRect ( rect, 1, 1 );
    painter.fillRect ( rect, QColor ( 255, 0, 0, 20 ) );
    painter.end();

    label->setPixmap ( pm );
}

void windowGrabberLinux::showEvent ( QShowEvent * )
{

}

QPixmap* windowGrabberLinux::pixmap()
{
    return &_pixmap;
}

WId windowGrabberLinux::winId()
{
    return QDialog::winId();
}
