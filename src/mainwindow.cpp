#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "core.h"
#include "qdebug.h"
#include "menubutton.h"

MainWindow::MainWindow ( QWidget *parent ) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi ( this );

    setWindowTitle ( "" );

    //qApp->installEventFilter ( this );
    setMouseTracking ( true );
    selectedAction = NULL;

    core *c = system::getCore();

    ui->shootMode->setFixedWidth ( 22 );

    shootMenu = ui->shootMode->getMenu();
    shootMenu->addAction ( new QAction ( QObject::tr ( "Full screen" ), shootMenu ) );
    shootMenu->addAction ( new QAction ( QObject::tr ( "Window under mouse" ), shootMenu ) );
    shootMenu->addAction ( new QAction ( QObject::tr ( "Area of the screen" ), shootMenu ) );

    QObject::connect ( shootMenu, SIGNAL ( triggered ( QAction* ) ), this, SLOT ( changeShootMode ( QAction* ) ) );
    QObject::connect ( ui->shootButton, SIGNAL ( clicked() ), c, SLOT ( mainAction() ) );

    QObject::connect ( ui->buttonExit, SIGNAL ( clicked() ), c, SLOT ( toggleVisability() ) );
    QObject::connect ( ui->actionExit, SIGNAL ( triggered(bool) ), qApp, SLOT ( quit() ) );
    QObject::connect ( ui->actionAbout, SIGNAL ( triggered(bool) ), c, SLOT ( showAbout() ) );
    QObject::connect ( ui->actionAbout_Qt, SIGNAL ( triggered ( bool ) ), qApp, SLOT ( aboutQt() ) );

    QMenu *menu = ui->buttonExport->getMenu();

    QAction *file = new QAction ( QObject::tr ( "To File ..." ), menu );
    QAction *web = new QAction ( QObject::tr ( "To WEB" ), menu );
    menu->addAction ( file );
    menu->addAction ( web );

    QObject::connect ( file, SIGNAL ( triggered ( bool ) ), this, SLOT ( openFileDialog() ) );
    QObject::connect ( web, SIGNAL ( triggered ( bool ) ), c, SLOT ( exportToWEB() ) );

    QObject::connect ( ui->actionSettings, SIGNAL ( triggered ( bool ) ), c, SLOT ( openSettingsDialog() ) );

//    c->rect.draw();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete shootMenu;
    ui = NULL;
}

int MainWindow::init ( core *core )
{
    main = core;
    setMainAction ( DEFAULT );

    return 1;
}

void MainWindow::mouseMoveEvent ( QMouseEvent * )
{
    //qDebug() << "here";
}

void MainWindow::setMainAction ( enum MainWindow::actions action )
{
    int selectedIndex = 0;

    if ( NULL != selectedAction )
    {
        selectedIndex = shootMenu->actions().indexOf ( selectedAction );
        ui->shootButton->setText ( selectedAction->text() );

    } else {
        ui->shootButton->setText ( shootMenu->actions().first()->text() );
    }

    switch ( action )
    {
        case MainWindow::DEFAULT:
            action = static_cast < MainWindow::actions > ( selectedIndex );
        break;
        case MainWindow::TAKE_WINDOW:
            action = MainWindow::TAKE_WINDOW;
        break;
        case MainWindow::TAKE_RECTANGLE:
            action = MainWindow::TAKE_RECTANGLE;
        break;
        case MainWindow::TAKE_AREA:
            action = MainWindow::TAKE_AREA;
        break;
    }

    this->action = action;
    system::getCore()->action = action;
}

void MainWindow::setScreenPic ( QPixmap &pic )
{
    QSize size = ui->mainPic->size();
    ui->mainPic->setPixmap ( pic.scaled ( size.width(), size.height(), Qt::KeepAspectRatio, Qt::SmoothTransformation ) );
}

void MainWindow::resizeEvent ( QResizeEvent *event )
{
    if ( !system::getCore()->picture.isNull() )
    {
        QSize size = ui->mainPic->size();
        ui->mainPic->setPixmap ( system::getCore()->picture.scaled ( size.width(), size.height(), Qt::KeepAspectRatio, Qt::SmoothTransformation ) );
    }

    event->ignore();
}

int MainWindow::setLabelText ( QString text )
{
    //ui->mainPic->setStyleSheet (
    //"background: qlineargradient(x1:0,y1:0,x2:0,y2:1, stop:0 #75FF77,stop: 1 #B3FFB8);border-width: 1px; border-color: #d91414; border-style: solid; padding: 5px; padding-left:10px; padding-right:10px; border-radius: 3px; color:#000;font-size:20px;"
    //);
    ui->mainPic->setText ( text );

    return 1;
}

void MainWindow::openFileDialog()
{
    QString dirPath = QDir::homePath(),
            file = dirPath + "/screenshot.png",
            fileName;

    QFileInfo finfo ( file );

    if ( finfo.exists() )
    {
        fileName = dirPath + "/" + system::makeNewNameFromOld ( finfo );
        fileName += ".png";
    } else {
        fileName = file;
    }

    fileName = QFileDialog::getSaveFileName ( this, QObject::tr ( "Save File"),
                                              fileName, QObject::tr ( "PNG images (*.png)" ) );

    if ( fileName.isEmpty() )
    {
        return;
    }

    if ( fileName.right ( 4 ) != ".png" )
    {
        fileName += ".png";

    }

    QImageWriter imagefile;
    imagefile.setFileName ( fileName );
    imagefile.setFormat ( "PNG" );
    imagefile.setQuality ( 100 );
    imagefile.write ( system::getCore()->picture.toImage() );
}

void MainWindow::paintEvent(QPaintEvent *)
{

}

void MainWindow::keyPressEvent ( QKeyEvent *e )
{
    e->ignore();
}

void MainWindow::changeShootMode ( QAction *a )
{
    selectedAction = a;
    setMainAction();
}

/*void MainWindow::showEvent ( QShowEvent *e )
{
    if ( NULL == system::getCore()->sc )
    {
        system::getCore()->sc = new screenshot ( system::getCore() );
    }

    system::getCore()->sc->shootDesktop ( true );
    QMainWindow::showEvent ( e );
}*/

/*void MainWindow::setVisible ( bool visible )
{
    QWidget::setVisible ( visible );

}*/

/*bool MainWindow::eventFilter ( QObject *obj, QEvent *event )
{
    QMouseEvent *mouseEvent = NULL;

    switch ( event->type() )
    {
        case QEvent::MouseButtonRelease:
            mouseEvent = static_cast < QMouseEvent* > ( event );
            qDebug() << QString("Mouse move (%1,%2)").arg(mouseEvent->globalPos().x()).arg(mouseEvent->globalPos().y());


        break;
        default:
        break;
    }

    return false;
}*/

