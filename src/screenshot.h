#ifndef SCREENSHOT_H
#define SCREENSHOT_H

#include "system.h"
#include "windowgrabberlinux.h"
#include "desktopgrabberlinux.h"
#include "rectanglegrabber.h"
class core;

class screenshot : public system
{
    Q_OBJECT
public:
    core *main;
    int init();

    explicit screenshot ( core *c );
    ~screenshot();

    int shootWindow();
    int shootDesktop ( bool now = false );
    int shootRectangle();

private:
    windowGrabberLinux *wgl;
    desktopGrabberLinux *dgl;
    rectangleGrabber *rg;

signals:

public slots:

};

#endif // SCREENSHOT_H
