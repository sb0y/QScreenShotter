#ifndef WINDOWGRABBERWINDOWS_H
#define WINDOWGRABBERWINDOWS_H

#include <QObject>
#include <QWidget>
#include <QDialog>
#include <QMouseEvent>
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
    void mousePressEvent( QMouseEvent *e );
    void mouseMoveEvent ( QMouseEvent *e );

signals:

public slots:
};

#endif // WINDOWGRABBERWINDOWS_H
