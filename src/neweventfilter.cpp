#include "neweventfilter.h"
#include <xcb/xcb.h>
#include <QDebug>
#include "core.h"

NewEventFilter::NewEventFilter()
{
}


bool NewEventFilter::nativeEventFilter ( const QByteArray &eventType, void *message, long *l ) Q_DECL_OVERRIDE
{
    if ( eventType == "xcb_generic_event_t" )
    {
        //xcb_generic_event_t *e = static_cast < xcb_generic_event_t* > ( message );

    }

    return false;
}
