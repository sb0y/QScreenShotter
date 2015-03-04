#ifndef WINDOWGRABBERWINDOWS_H
#define WINDOWGRABBERWINDOWS_H

#include <QObject>
#include <QWidget>
#include <QDialog>
#include <QMouseEvent>
#ifdef WIN32
    #define OEMRESOURCE
    #include <windows.h>
    #include <Winuser.h>
    #include <qt_windows.h>
    #include <QtWinExtras>
    #include "mousespy.h"
#endif
#include "grabberbase.h"
#include "qtthread.h"
#include "windowswindow.h"

class windowsWindow;

class windowGrabberWindows : public QObject, public grabberBase//, public grabberBaseDialog
{
    Q_OBJECT
public:

    windowsWindow *wnd;

    explicit windowGrabberWindows();
    virtual ~windowGrabberWindows();

    void start();
    void prepare();
    void done();
    void save();
    QPixmap* pixmap();

    void windowUnderCursor ( bool includeDecorations = true );

    //LRESULT CALLBACK mouseProc (int nCode, WPARAM wParam, LPARAM lParam);
    void WINAPI myMouseLogger();

protected:
    void mousePressEvent( QMouseEvent * );
    void mouseMoveEvent ( QMouseEvent * );
   // void showEvent ( QShowEvent * );

signals:

public slots:
};

#endif // WINDOWGRABBERWINDOWS_H
