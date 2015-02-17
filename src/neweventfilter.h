#ifndef NEWEVENTFILTER_H
#define NEWEVENTFILTER_H

#include <QAbstractNativeEventFilter>
#include <QObject>
#ifdef HAVE_X11
    #include <xcb/xcb.h>
#elif WIN32
    #include <windows.h>
#endif

class NewEventFilter : public QAbstractNativeEventFilter
{
public:
    explicit NewEventFilter();
    virtual bool nativeEventFilter(const QByteArray &eventType, void *message, long *) Q_DECL_OVERRIDE;
signals:

public slots:

};

#endif // NEWEVENTFILTER_H
