#ifndef CUSTOMFRAME_H
#define CUSTOMFRAME_H

#include <QFrame>
#include <QPaintEvent>
#include <QWidget>
#include <QPainter>
#include <QPaintEngine>

class customFrame : public QWidget
{
    Q_OBJECT
public:
    explicit customFrame(QWidget *parent = 0, QFlags<Qt::WindowType> = 0);


protected:
    void paintEvent ( QPaintEvent * );

signals:

public slots:
    void repaint (int x, int y, int w, int h);
};

#endif // CUSTOMFRAME_H
