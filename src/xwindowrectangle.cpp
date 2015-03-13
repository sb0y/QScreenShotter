#include "xwindowrectangle.h"
#include <unistd.h>
#include <xcb/xcb.h>
#include <X11/Xlib.h>

XWindowRectangle::XWindowRectangle(QObject *parent) :
    QObject(parent)
{
    /*Display *display = XOpenDisplay(NULL);
    int screen_num = DefaultScreen(display);
    Window root_win = RootWindow ( display, screen_num );
    XGCValues gc_val;
    GC gc_line;

    gc_val.function           = GXxor;
    gc_val.plane_mask         = AllPlanes;
    gc_val.foreground         = WhitePixel ( display, screen_num );
    gc_val.background         = BlackPixel ( display, screen_num );
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

    gc_line = XCreateGC ( display, root_win, GCFunction | GCPlaneMask |  GCForeground | GCBackground | GCLineWidth | GCLineStyle |
                GCCapStyle  | GCJoinStyle  |  GCFillStyle  |  GCFillRule  |  GCGraphicsExposures |
                GCClipXOrigin |  GCClipYOrigin  |  GCClipMask  | GCSubwindowMode, &gc_val );

    XDrawRectangle ( display, root_win, gc_line, 50, 50, 400, 400 );
    XFlush ( display );*/

   // XUngrabServer ( display );

     c = xcb_connect ( NULL, NULL );

     /* get the first screen */
     screen = xcb_setup_roots_iterator (xcb_get_setup (c)).data;

     gc = xcb_generate_id (c);

     /* root window */
     wnd = screen->root;

     uint32_t mask = 0;
     uint32_t values[2];
     mask = XCB_CW_EVENT_MASK;
     values[0] = XCB_EVENT_MASK_SUBSTRUCTURE_NOTIFY;

     xcb_change_window_attributes_checked ( c, wnd, mask, values );

     drown = false;
     X = Y = W = H = 0;
}

XWindowRectangle::~XWindowRectangle()
{
    clear();
}

void XWindowRectangle::waitEvent()
{
    xcb_generic_event_t *event;

    while ( ( event = xcb_wait_for_event ( c ) ) )
    {
        switch ( event->response_type & ~0x80 )
        {
            case XCB_EXPOSE:
            {
                xcb_expose_event_t *expose = (xcb_expose_event_t *)event;
                redraw();
                break;
            }

            case XCB_BUTTON_PRESS:
            {
                xcb_button_press_event_t *press = (xcb_button_press_event_t *)event;
                break;
            }

            case XCB_MOTION_NOTIFY:
            {
                xcb_motion_notify_event_t *move = (xcb_motion_notify_event_t *)event;
            }

            default:
                redraw();
            break;
        }

    }
}

void XWindowRectangle::draw()
{
    mask = XCB_GC_FOREGROUND | XCB_GC_LINE_WIDTH | XCB_GC_SUBWINDOW_MODE | XCB_GC_GRAPHICS_EXPOSURES;
    uint32_t values[] = {
        screen->black_pixel,
        4,
        XCB_SUBWINDOW_MODE_INCLUDE_INFERIORS,
        1
    };

    xcb_create_gc ( c, gc, wnd, mask, values );
    xcb_map_window ( c, wnd );
    xcb_flush ( c );

    redraw();
    waitEvent();
}

void XWindowRectangle::redraw()
{
    xcb_rectangle_t rectangles[] = {
        { X,Y,W,H }
    };

    xcb_poly_rectangle ( c, wnd, gc, 1, rectangles );
    xcb_flush ( c );
}

void XWindowRectangle::setXY ( int x, int y )
{
    X = x;
    Y = y;
}

void XWindowRectangle::setWH ( int w, int h )
{
    W = w;
    H = h;
}

void XWindowRectangle::clear()
{
    W = H = X = Y = 0;
    drown = false;
    //xcb_flush ( c );
    //xcb_disconnect ( c );
}
