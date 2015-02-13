#ifndef X11INFO_H
#define X11INFO_H

typedef struct _XDisplay Display;

class X11Info
{
    static Display *_display;
public:
    static Display* display();
    static unsigned long appRootWindow(int screen = -1);
};

#endif // X11INFO_H
