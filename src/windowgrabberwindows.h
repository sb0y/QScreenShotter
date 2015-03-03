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

class windowGrabberWindows : public QObject, public grabberBase//, public grabberBaseDialog
{
    Q_OBJECT
public:

    QDialog *wnd;

    explicit windowGrabberWindows();
    virtual ~windowGrabberWindows();

    void start();
    void prepare();
    void done();
    void save();
    QPixmap* pixmap();

    //LRESULT CALLBACK mouseProc (int nCode, WPARAM wParam, LPARAM lParam);
    void WINAPI myMouseLogger();

protected:
    void mousePressEvent( QMouseEvent * );
    void mouseMoveEvent ( QMouseEvent * );
    bool eventFilter ( QObject *, QEvent * );
   // void showEvent ( QShowEvent * );

signals:

public slots:
};

#endif // WINDOWGRABBERWINDOWS_H
