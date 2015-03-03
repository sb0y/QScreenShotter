#ifndef DESKTOPGRABBER_H
#define DESKTOPGRABBER_H

#include "grabberbase.h"
#include "grabberbasedialog.h"
#include <QMouseEvent>

class core;

class desktopGrabber : public grabberBaseDialog
{
    Q_OBJECT
private:
public:
    explicit desktopGrabber();
    virtual ~desktopGrabber();
    void prepare();
    void done();
    QPixmap* pixmap();

protected:
    void mousePressEvent( QMouseEvent * event );
    void showEvent ( QShowEvent * );
    void hideEvent ( QHideEvent * );

signals:

public slots:
    void start();

};

#endif // DESKTOPGRABBER_H
