#include "rectanglegrabber.h"
#include "core.h"

rectangleGrabber::rectangleGrabber()
{
    band = NULL;

    setMouseTracking ( true );
    setWindowModality( Qt::WindowModal );
    setFixedSize ( screen.size().width(), screen.size().height() );
    layout = new QHBoxLayout ( this );

    setLayout ( layout );

    label = new QLabel ( this );
    layout->addWidget ( label );
    layout->setContentsMargins ( 0, 0, 0, 0 );

    isBannerShown = true;
}

void rectangleGrabber::drawScreen ( bool banner )
{
    QPixmap pm ( pixmap );

    QPainter p ( &pm );
    QBrush b ( QColor ( 0,0,0,128 ) ); // adjust color and alpha to taste
    p.setBrush ( b );
    p.drawRect ( 0, 0, screen.size().width(), screen.size().height() );

    QRect textBox = screen;
    textBox.setLeft ( 190 );
    textBox.setRight ( textBox.right() - 190 );
    textBox.setTop ( 20 );
    textBox.setHeight ( 110 );

    if ( banner )
    {
        QStaticText header ( "<h1>Select a rectangular area with the mouse</h1>" );
        header.setTextFormat ( Qt::RichText );
        header.setTextWidth ( textBox.width() - 10 );

        QStaticText subHeader ( "<h2>To take a picture, press <b>ENTER</b>. To cancel press <b>ESC</b>.</h2>" );
        subHeader.setTextFormat ( Qt::RichText );
        subHeader.setTextWidth ( textBox.width() - 10 );

        p.drawRoundedRect ( textBox, 6.0, 6.0 );
        p.setPen ( 0xCECECE );
        p.setRenderHint ( QPainter::Antialiasing, true );

        p.drawStaticText ( textBox.left() + 10, textBox.top() + 10, header );
        p.drawStaticText ( textBox.left() + 10, ( textBox.top() + header.size().height() - subHeader.size().height() ), subHeader );
    }

    p.end();
    label->setPixmap ( pm );

    isBannerShown = banner;
}

rectangleGrabber::~rectangleGrabber()
{
    delete band;
}

void rectangleGrabber::start()
{
    prepare();
}

void rectangleGrabber::prepare()
{
    pixmap = qApp->primaryScreen()->grabWindow ( QApplication::desktop()->winId() );
    screen = qApp->primaryScreen()->geometry();
    drawScreen();

    exec();
}

void rectangleGrabber::done()
{
    close();
    system::getCore()->toggleVisability();
}

void rectangleGrabber::beginSelection ( QPoint p )
{
    band = new rubberBand ( this );
    band->move ( p );
    band->resize ( 0, 0 );
}

void rectangleGrabber::mousePressEvent ( QMouseEvent *e )
{
    if ( e->button() == Qt::LeftButton &&
         e->type() == QEvent::MouseButtonPress )
    {
        if ( NULL != band )
        {
            delete band;
            band = NULL;
        }

        beginSelection ( e->globalPos() );

        if ( isBannerShown )
            drawScreen ( false );

    } else if ( e->button() == Qt::LeftButton &&
                e->type() == QEvent::MouseButtonRelease )
    {
        //delete band;
        //band = NULL;
    }

    e->accept();
}

void rectangleGrabber::keyPressEvent ( QKeyEvent *e )
{
    switch ( e->key() )
    {
        case Qt::Key_Escape:
            e->accept();
            done();
        break;

        case Qt::Key_Return:
        case Qt::Key_Enter:

            save();
            done();
            e->accept();

        break;

        default:
            e->ignore();
        break;
    }
}

void rectangleGrabber::mouseMoveEvent ( QMouseEvent *e )
{
    if ( NULL != band )
    {
        band->resize ( e->x() - band->x(), e->y() - band->y() );
    }

    e->accept();
}

void rectangleGrabber::save()
{
    system::getCore()->setPixmap ( band->pixmap );
    getWindow ( "main", MainWindow* )->setScreenPic ( band->pixmap );
}
