#ifndef RUBBERBAND_H
#define RUBBERBAND_H

#include <QWidget>
#include <QHBoxLayout>
#include <QSizeGrip>
#include <QRubberBand>
#include <QResizeEvent>
#include <QLabel>

class rubberBand : public QWidget
{
    Q_OBJECT

public:
    explicit rubberBand(QWidget *parent = 0);
    ~rubberBand();

     QPixmap pixmap;

private:
    void resizeEvent ( QResizeEvent *e );
    QHBoxLayout *layout;
    QLabel *label;
    QRubberBand *_rubberBand;

signals:

public slots:

};

#endif // RUBBERBAND_H
