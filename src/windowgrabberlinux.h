#ifndef WINDOWGRABBER_LINUX_H
#define WINDOWGRABBER_LINUX_H

#include "system.h"

#include <QBitmap>
#include <QPainter>
#include <QPixmap>
#include <QPoint>
#include <QBrush>
#include <QMouseEvent>
#include <QGuiApplication>
#ifdef HAVE_X11
    #include <xcb/xcb.h>
#endif
#include <QPaintEvent>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QHBoxLayout>
#include <QLabel>
#include "grabberbase.h"
#include "grabberbasedialog.h"

class core;

class windowGrabberLinux : public grabberBaseDialog
{
    Q_OBJECT
public:
    QGraphicsScene *scene;
    QGraphicsView *view;

    explicit windowGrabberLinux();
    virtual ~windowGrabberLinux();

    void prepare();
    void windowUnderCursor();
    void done();
    QPixmap *pixmap();

    void drawOnLayer ( int x, int y, int w, int h );

    QPixmap _pixmap;
    QHBoxLayout *layout;
    QLabel *label;

    QDialog *splashWnd;
    QPainter painter;
    QPen pen;
    QBrush brush;

protected:
    void mousePressEvent( QMouseEvent *e );
    void paintEvent ( QPaintEvent *e );
    void mouseMoveEvent ( QMouseEvent *e );
    void keyPressEvent ( QKeyEvent *e );
    bool eventFilter ( QObject *, QEvent * );
    void showEvent (QShowEvent *);

signals:

public slots:
    void start();
    void mouseTick();

};

#endif // WINDOWGRABBER_LINUX_H
