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
        const MSG &msg = *static_cast < MSG* > ( message );
        HWND wnd;
        /*HCURSOR cursor[10];
        cursor[10] = NULL;*/

        switch ( msg.message )
        {
            case WM_SETCURSOR:
                /*cursor[0] = LoadCursor ( 0, IDC_ARROW );
                cursor[1] = LoadCursor ( 0, IDC_IBEAM );
                cursor[2] = LoadCursor ( 0, IDC_ARROW );
                cursor[3] = LoadCursor ( 0, IDC_SIZE );
                cursor[4] = LoadCursor ( 0, IDC_HAND );
                cursor[5] = LoadCursor ( 0, IDC_UPARROW );
                cursor[6] = LoadCursor ( 0, IDC_APPSTARTING );
                cursor[7] = LoadCursor ( 0, IDC_HAND );
                cursor[8] = LoadCursor ( 0, IDC_NO );
                cursor[9] = LoadCursor ( 0, IDC_CROSS );

                for ( int i = 0; cursor[i] != NULL; ++i )
                {
                    SetSystemCursor ( cursor[i], OCR_CROSS );
                }*/

                //qDebug() << "here ";
            break;

            case WM_NCLBUTTONDOWN:
                //qDebug() << "here";
            break;

            case WM_MOUSEACTIVATE:
                //qDebug() << "here";
            break;

            case WM_MOUSEMOVE:
            {
                if ( NULL != system::getCore()->sc->wg )
                {
                    wnd = (HWND)system::getCore()->sc->wg->winId();

                    if ( wnd == msg.hwnd )
                    {
                        return false;
                    }
                }

                break;
            }

            case WM_NCHITTEST:

            if ( NULL != system::getCore()->sc->wg )
            {
                wnd = (HWND)system::getCore()->sc->wg->winId();

                if ( wnd == msg.hwnd )
                {
                    return false;
                }
            }

            break;

            default:
                //qDebug() << msg.message;
            break;
        }
    }
    #endif

    return false;
}
