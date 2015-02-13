#include "customframe.h"
#include <QDebug>
#include <QCoreApplication>

customFrame::customFrame(QWidget *parent, QFlags<Qt::WindowType> f) :
    QWidget(parent, f)
{
    //setAutoFillBackground ( false );
    //setAttribute( Qt::WA_TranslucentBackground, true );
    //setAttribute( Qt::WA_NoSystemBackground, true );
    //setAttribute ( Qt::WA_PaintOnScreen, true );
    //QCoreApplication::setAttribute ( Qt::AA_NativeWindows, true );
    //setGeometry ( 50, 50, 200, 200 );
    show();
}

void customFrame::paintEvent ( QPaintEvent *e )
{
    qDebug() << "paintEvent";
    e->ignore();
    QPainter painter(this);
     painter.setPen ( Qt::red );
     painter.drawRect(rect());
}

void customFrame::repaint(int x, int y, int w, int h)
{
    qDebug() << "repaint";
    QPainter painter(this);
    painter.setPen(Qt::red);
    painter.drawRect ( 50, 50, 200, 200 );
    painter.end();
}
