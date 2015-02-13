#ifndef XWINDOWRECTANGLE_H
#define XWINDOWRECTANGLE_H

#include <QObject>
#include <QDebug>
#include <xcb/xcb.h>

class XWindowRectangle : public QObject
{
    Q_OBJECT
    int X, Y;
    uint W, H;

public:

    xcb_connection_t    *c;
    xcb_screen_t        *screen;
    xcb_generic_event_t *e;
    uint32_t             mask;
    xcb_gcontext_t    gc;    /* the returned default graphic context */
    xcb_drawable_t wnd;
    bool drown;
    xcb_window_t window;

    explicit XWindowRectangle(QObject *parent = 0);
    ~XWindowRectangle();
    void draw();
    void redraw();
    void setXY ( int x, int y );
    void setWH ( int w, int h );
    void clear();
    void waitEvent();

signals:

public slots:

};

#endif // XWINDOWRECTANGLE_H
