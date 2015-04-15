#include "menubutton.h"
#include <QStyleOptionButton>
#include <qdebug.h>

menuButton::menuButton(QWidget *parent)
{
    mainw = static_cast < MainWindow* > ( parent );
    options.features = QStyleOptionButton::None;
    setFocusPolicy ( Qt::NoFocus );

    menu = new QMenu ( this );

    QObject::connect ( menu, SIGNAL ( aboutToHide() ), this, SLOT ( toUp() ) );
}


void menuButton::mousePressEvent ( QMouseEvent *e )
{
    Q_UNUSED ( e );

    setDown ( true );
    QRect rect = contentsRect();
    QPoint pos = mapToGlobal ( rect.topLeft() );
    menu->move ( pos.x(), ( pos.y() - menu->sizeHint().height() ) );
    menu->show();
}

void menuButton::paintEvent ( QPaintEvent *e )
{
    QStylePainter p ( this );

    options.initFrom ( this );
    options.text = text();
    options.icon = icon();

    QSize sz ( size() );
    sz.setHeight ( sz.height() - 7 );
    sz.setWidth ( sz.width() - 7 );

    options.iconSize = sz;
    options.state |= isDown() ? QStyle::State_On : QStyle::State_Off;

    p.drawControl ( QStyle::CE_PushButton, options );

    e->accept();
}

QSize menuButton::sizeHint() const
{
    QSize size ( 0, 22 );
    return size;
}

void menuButton::toUp()
{
    setDown ( false );
}

QMenu* menuButton::getMenu()
{
    return menu;
}

/*bool menuButton::event(QEvent *e)
{
    return true;
}*/
