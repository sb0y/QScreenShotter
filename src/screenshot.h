#ifndef SCREENSHOT_H
#define SCREENSHOT_H

#include "system.h"
#ifdef HAVE_X11
    #include "windowgrabberlinux.h"
#elif WIN32
    #include "windowgrabberwindows.h"
#endif
#include "desktopgrabber.h"
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

    grabberBase *wg;
    grabberBase *dg;
    grabberBase *rg;

private:

    grabberBase *currentGrabber;

signals:

public slots:
    void startCurrentGrabber();

};

#endif // SCREENSHOT_H
