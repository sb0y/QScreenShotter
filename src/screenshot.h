#ifndef SCREENSHOT_H
#define SCREENSHOT_H

#include "system.h"
#ifdef HAVE_X11
    #include "windowgrabberlinux.h"
    #include "desktopgrabberlinux.h"
#endif
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
    grabberBase *wg;
    grabberBase *dg;
    grabberBase *rg;

signals:

public slots:

};

#endif // SCREENSHOT_H
