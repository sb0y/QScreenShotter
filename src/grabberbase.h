#ifndef GRABBERBASE_H
#define GRABBERBASE_H

#include <QDialog>
#include <QTimer>
#include <QTimerEvent>
#include <qdebug.h>
#include <QRect>
#include <QScreen>
#include <QApplication>

class grabberBase
{
public:

    explicit grabberBase();
    virtual ~grabberBase();
    virtual void done() = 0;
    virtual void prepare() = 0;

    virtual void start() = 0;
    virtual QPixmap* pixmap() = 0;

protected:
};

#endif // GRABBERBASE_H
