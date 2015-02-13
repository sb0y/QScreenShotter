#include "x11info.h"

#ifdef HAVE_QT5
# include <X11/Xlib.h>
# include <QtGlobal>
#else
//#include <QX11Info>
#endif


Display* X11Info::display()
{
#ifdef HAVE_QT5
    if (!_display) {
        _display = XOpenDisplay(NULL);
    }
    return _display;
#else
    return 0;//QX11Info::display();
#endif
}

unsigned long X11Info::appRootWindow(int screen)
{
#ifdef HAVE_QT5
    return screen == -1?
                XDefaultRootWindow(display()) :
                XRootWindowOfScreen(XScreenOfDisplay(display(), screen));
#else
    return 0;//QX11Info::appRootWindow(screen);
#endif
}

Display* X11Info::_display = 0;
