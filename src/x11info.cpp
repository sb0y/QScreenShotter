#include "x11info.h"
#include <qdebug.h>
//#include <qpa/qplatformnativeinterface.h>
//#include <qpa/qplatformwindow.h>
#include <qscreen.h>
#include <qwindow.h>
#include <qguiapplication.h>
#include <xcb/xcb.h>

//QT_BEGIN_NAMESPACE

/*!
    \class QX11Info
    \inmodule QtX11Extras
    \since 5.1
    \brief Provides information about the X display configuration.

    The class provides two APIs: a set of non-static functions that
    provide information about a specific widget or pixmap, and a set
    of static functions that provide the default information for the
    application.

    \warning This class is only available on X11. For querying
    per-screen information in a portable way, use QDesktopWidget.
*/

/*!
    Constructs an empty QX11Info object.
*/
/*X11Info::X11Info()
{
}

Display* X11Info::display()
{
    if ( !qApp )
        return NULL;

    QPlatformNativeInterface *native = qApp->platformNativeInterface();

    if ( !native )
        return NULL;

    void *display = native->nativeResourceForScreen ( QByteArray( "display" ), QGuiApplication::primaryScreen() );
    return reinterpret_cast<Display *>(display);
}

unsigned long X11Info::appRootWindow()
{
    if ( !qApp )
        return 0;

    QPlatformNativeInterface *native = qApp->platformNativeInterface();

    if ( !native )
        return 0;
    return static_cast < xcb_window_t > ( reinterpret_cast < quintptr > ( native->nativeResourceForIntegration ( QByteArrayLiteral ( "rootwindow" ) ) ) );
}

QT_END_NAMESPACE*/
