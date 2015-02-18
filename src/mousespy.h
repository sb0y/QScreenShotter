#ifndef MOUSESPY_H
#define MOUSESPY_H

#include <QObject>
#include <QThread>
#ifdef WIN32
    #define OEMRESOURCE
    #include <windows.h>
    #include <Winuser.h>
    #include <qt_windows.h>
    #include <QtWinExtras>
#endif

class mouseSpy : public QObject
{
    Q_OBJECT
public:
    explicit mouseSpy(QObject *parent = 0);
    ~mouseSpy();

    void WINAPI myMouseLogger();
    void start();

signals:

public slots:
};

#endif // MOUSESPY_H
