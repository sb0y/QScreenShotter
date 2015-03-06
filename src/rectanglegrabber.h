#ifndef RECTANGLEGRABBER_H
#define RECTANGLEGRABBER_H

#include "grabberbase.h"
#include <QObject>
#include <QApplication>
#include <QScreen>
#include <QDialog>
#include <QLabel>
#include <QHBoxLayout>
#include <QDesktopWidget>
#include <QStaticText>
#include <QPainter>
#include <QTimer>
#include "rubberband.h"
#include "grabberbasedialog.h"

class rectangleGrabber : public grabberBaseDialog
{
    Q_OBJECT
private:
    rubberBand *band;

public:
    explicit rectangleGrabber();
    virtual ~rectangleGrabber();

    void done();
    void save();
    void prepare();
    QPixmap* pixmap();
    WId winId();

    bool isBannerShown;
    void drawScreen ( bool banner = true );
    void beginSelection ( QPoint );

    QRect screen;
    QLabel *label;
    QPixmap _pixmap;
    QHBoxLayout *layout;

signals:

public slots:
    void start();

protected:
    void mousePressEvent( QMouseEvent *e );
    void mouseMoveEvent ( QMouseEvent *e );
    void keyPressEvent ( QKeyEvent *e );
    void showEvent ( QShowEvent *e );

};

#endif // RECTANGLEGRABBER_H
