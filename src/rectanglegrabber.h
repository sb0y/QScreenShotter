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

class rectangleGrabber : public grabberBase
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

    bool isBannerShown;
    void drawScreen ( bool banner = true );
    void beginSelection ( QPoint );

    QRect screen;
    QLabel *label;
    QPixmap pixmap;
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
