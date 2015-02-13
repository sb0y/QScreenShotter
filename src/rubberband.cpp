#include "rubberband.h"
#include "core.h"

rubberBand::rubberBand(QWidget *parent) :
    QWidget(parent)
{
    // tell QSizeGrip to resize this widget instead of top-level window
    setWindowFlags ( Qt::SubWindow );
    _rubberBand = new QRubberBand ( QRubberBand::Rectangle, this );
    QPalette p ( parent->palette() );
   // QColor color ( Qt::transparent );
    //color.setAlpha ( 100 );
   //p.setBrush ( QPalette::Highlight, QBrush ( color ) );
    _rubberBand->setPalette ( p );
    _rubberBand->setStyleSheet ( "border: 1px solid black;" );

    layout = new QHBoxLayout ( _rubberBand );
    layout->setContentsMargins ( 0, 0, 0, 0 );

    //QSizeGrip *grip1 = new QSizeGrip ( this );
    //QSizeGrip *grip2 = new QSizeGrip ( this );

    //layout->addWidget ( grip1, 0, Qt::AlignLeft | Qt::AlignTop );

    //layout->addWidget ( grip2, 0, Qt::AlignRight | Qt::AlignBottom );

    label = new QLabel ( this );
    layout->addWidget ( label, 1, Qt::AlignCenter | Qt::AlignHCenter );

    _rubberBand->move ( 0, 0 );
    _rubberBand->show();
    show();
}

rubberBand::~rubberBand()
{
   delete _rubberBand;
}

void rubberBand::resizeEvent ( QResizeEvent *e )
{
    pixmap = static_cast < rectangleGrabber* > ( parent() )->pixmap.copy ( x(), y(), width(), height() );
    label->setPixmap ( pixmap );

    _rubberBand->resize ( size() );

    e->accept();
}
