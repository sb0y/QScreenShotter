#include "neweventfilter.h"
#include <QDebug>
#include "core.h"

NewEventFilter::NewEventFilter()
{
}


bool NewEventFilter::nativeEventFilter ( const QByteArray &eventType, void *message, long *l ) Q_DECL_OVERRIDE
{
    #ifdef HAVE_X11
    if ( eventType == "xcb_generic_event_t" )
    {
        //xcb_generic_event_t *e = static_cast < xcb_generic_event_t* > ( message );
    }
    #elif WIN32
    if ( eventType == "windows_generic_MSG" || eventType == "windows_dispatcher_MSG" )
    {
        const MSG &msg = *static_cast < MSG * > ( message );

        switch ( msg.message )
        {
            case WM_SETCURSOR:
                qDebug() << "here";
            break;
        }
    }
    #endif

    return false;
}
