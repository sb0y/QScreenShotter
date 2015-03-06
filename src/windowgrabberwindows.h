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
#include <algorithm>
#include <memory>
#include <vector>

class windowsWindow;

class windowGrabberWindows : public QObject, public grabberBase//, public grabberBaseDialog
{
    Q_OBJECT
public:

    windowsWindow *wnd;

    explicit windowGrabberWindows();
    virtual ~windowGrabberWindows();

    struct winInfo
    {
        winInfo ( HWND wid, RECT *r )
        {
            winId = wid;
            rect = r;
        }

        RECT *rect;
        HWND winId;
    };

    std::vector < winInfo > windows;

    void start();
    void prepare();
    void done();
    void save();
    QPixmap* pixmap();
    WId winId();

    void windowUnderCursor ( bool includeDecorations = true );

    //LRESULT CALLBACK mouseProc (int nCode, WPARAM wParam, LPARAM lParam);
    void WINAPI myMouseLogger();
    void getAllAvailableWindows();

    static BOOL CALLBACK EnumWindowsProc ( HWND hWnd, LPARAM lParam );

protected:
    void mousePressEvent( QMouseEvent * );
    void mouseMoveEvent ( QMouseEvent * );
   // void showEvent ( QShowEvent * );

private:
    static windowGrabberWindows *self;

signals:

public slots:
};

#endif // WINDOWGRABBERWINDOWS_H
