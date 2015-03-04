#ifndef WINDOWSWINDOW_H
#define WINDOWSWINDOW_H

#ifdef WIN32
    #define OEMRESOURCE
    #include <windows.h>
    #include <Winuser.h>
    #include <qt_windows.h>
    #include <QtWinExtras>
    #include "mousespy.h"
#endif
#include <QDialog>
#include "windowgrabberwindows.h"
#include <assert.h>

class windowGrabberWindows;

class windowsWindow : public QDialog
{
    Q_OBJECT
public:
    explicit windowsWindow();
    ~windowsWindow();

    windowGrabberWindows *owner;

    void setOwner ( windowGrabberWindows *w );

    void mouseMoveEvent ( QMouseEvent *e );
    void mousePressEvent ( QMouseEvent *e );
    bool eventFilter ( QObject *o, QEvent *e );

signals:

public slots:
};

#endif // WINDOWSWINDOW_H
