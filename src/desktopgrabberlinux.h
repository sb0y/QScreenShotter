#ifndef DESKTOPGRABBER_LINUX_H
#define DESKTOPGRABBER_LINUX_H

//#include "grabberbase.h"
#include <QMouseEvent>

class core;

class desktopGrabberLinux : public QObject// : public grabberBase
{
    Q_OBJECT
private:
public:
    explicit desktopGrabberLinux();
    virtual ~desktopGrabberLinux();
    void prepare();
    void done();

protected:
    void mousePressEvent( QMouseEvent *event );

signals:

public slots:
    void start();

};

#endif // DESKTOPGRABBER_LINUX_H
