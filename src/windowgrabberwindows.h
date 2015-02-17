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
#endif
#include "grabberbase.h"

class windowGrabberWindows : public grabberBase
{
    Q_OBJECT
public:
    explicit windowGrabberWindows();
    ~windowGrabberWindows();

    void start();
    void prepare();
    void done();
    void save();

protected:
    void mousePressEvent( QMouseEvent * );
    void mouseMoveEvent ( QMouseEvent * );
    bool eventFilter ( QObject *, QEvent * );
   // void showEvent ( QShowEvent * );

signals:

public slots:
};

#endif // WINDOWGRABBERWINDOWS_H
