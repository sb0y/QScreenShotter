#ifndef WINDOWSWINDOW_H
#define WINDOWSWINDOW_H

#ifdef WIN32
    #define OEMRESOURCE
    #include <windows.h>
    #include <objidl.h>
    #include <gdiplus.h>
    //using namespace Gdiplus;
    //#pragma comment (lib,"Gdiplus.lib")
    #include <Winuser.h>
    #include <qt_windows.h>
    #include <QtWinExtras>
    #include "mousespy.h"
#endif
#include <QDialog>
#include "windowgrabberwindows.h"
#include <assert.h>
#include <iostream>

class windowGrabberWindows;

class windowsWindow : public QDialog
{
    Q_OBJECT
public:
    explicit windowsWindow();
    ~windowsWindow();

    int mm;
    HWND highlightedWindow;
    RECT highlightedWindowRECT;

    windowGrabberWindows *owner;

    void setOwner ( windowGrabberWindows *w );

    void mouseMoveEvent ( QMouseEvent *e );
    void mousePressEvent ( QMouseEvent *e );
    bool eventFilter ( QObject *o, QEvent *e );
    bool drawRectangle (int x, int y, int w, int h );
    void eraseRectangle();

    void mouseTick();

protected:
    void timerEvent(QTimerEvent *event);

signals:

public slots:
};

#endif // WINDOWSWINDOW_H
