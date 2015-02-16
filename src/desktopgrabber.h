#ifndef DESKTOPGRABBER_H
#define DESKTOPGRABBER_H

#include "grabberbase.h"
#include <QMouseEvent>

class core;

class desktopGrabber : public grabberBase
{
    Q_OBJECT
private:
public:
    explicit desktopGrabber();
    virtual ~desktopGrabber();
    void prepare();
    void done();

protected:
    void mousePressEvent( QMouseEvent *event );

signals:

public slots:
    void start();

};

#endif // DESKTOPGRABBER_H
