#ifndef X11INFO_H
#define X11INFO_H
#include <QtCore/qnamespace.h>
#include "QtX11Extras/qtx11extrasglobal.h"

#ifndef QTX11EXTRASGLOBAL_H
#define QTX11EXTRASGLOBAL_H

#include <QtCore/qglobal.h>

QT_BEGIN_NAMESPACE

#ifndef QT_STATIC
#  if defined(QT_BUILD_X11EXTRAS_LIB)
#    define Q_X11EXTRAS_EXPORT Q_DECL_EXPORT
#  else
#    define Q_X11EXTRAS_EXPORT Q_DECL_IMPORT
#  endif
#else
#  define Q_X11EXTRAS_EXPORT
#endif

QT_END_NAMESPACE

#endif // QTX11EXTRASGLOBAL_H

typedef struct _XDisplay Display;
struct xcb_connection_t;

QT_BEGIN_NAMESPACE

class Q_X11EXTRAS_EXPORT X11Info
{
public:
    static unsigned long appRootWindow();
    static Display *display();

private:
    X11Info();
};

QT_END_NAMESPACE

#endif // X11INFO_H
