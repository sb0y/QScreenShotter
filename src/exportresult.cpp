#include "exportresult.h"
#include "ui_exportresult.h"
#include "core.h"

exportResult::exportResult(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::exportResult)
{
    ui->setupUi ( this );

    setWindowTitle ( "WEB Export Results" );
    advancedLayout = NULL;

    clipMapper = new QSignalMapper ( this );

    clipMapper->setMapping ( ui->pushButton, Link );
    clipMapper->setMapping ( ui->pushButton_2, DirectLink );
    QObject::connect ( ui->pushButton, SIGNAL ( clicked() ), clipMapper, SLOT ( map() ) );
    QObject::connect ( ui->pushButton_2, SIGNAL ( clicked() ), clipMapper, SLOT ( map() ) );
    QObject::connect ( clipMapper, SIGNAL ( mapped ( int ) ), this, SLOT ( copyToClipboard ( int ) ) );
}

exportResult::~exportResult()
{
    delete ui;
    system::getCore()->windows [ "exportResult" ] = NULL;
    delete advancedLayout;
    delete clipMapper;
}

void exportResult::setResult ( QString big, QString small, QString userID )
{
    this->big = big;
    this->small = small;
    this->userID = userID;

    base = "http://" + system::getCore()->settings->value ( "WEB/site" ).toString();
    baseCode = base + "/content/screenshots/" + userID + "/";

    ui->directLink->setText ( baseCode + big );
    ui->link->setText ( base + "/screenshot/display/" + userID + "/" + big + "/" + small );

    QObject::connect ( ui->link, SIGNAL ( textChanged ( const QString& ) ), this, SLOT ( updateLabels() ) );
    QObject::connect ( ui->directLink, SIGNAL ( textChanged ( const QString& ) ), this, SLOT ( updateLabels() ) );
    QObject::connect ( ui->advancedButton, SIGNAL ( clicked() ), this, SLOT ( advancedButton() ) );

    updateLabels();
}

void exportResult::updateLabels()
{
    QUrl link, directLink;

    link.setUrl ( ui->link->text() );
    directLink.setUrl ( ui->directLink->text() );

    if ( link.isValid() && !link.scheme().isEmpty() )
    {
        ui->linkLabel->setText ( QString ( "<a href=\"%0\">Link</a>" ).arg ( link.toString() ) );
    } else {
        ui->linkLabel->setText ( "Link" );
    }

    if ( directLink.isValid() && !directLink.scheme().isEmpty() )
    {
        ui->directLinkLabel->setText ( QString ( "<a href=\"%0\">Direct Link</a>" ).arg ( directLink.toString() ) );
    } else {
        ui->directLinkLabel->setText ( "Direct Link" );
    }
}

void exportResult::makeEasy()
{
    setSizePolicy ( QSizePolicy::Fixed, QSizePolicy::Preferred );

    QLayoutItem *item = NULL;

    while ( ( item = advancedLayout->itemAt ( 0 ) ) != 0 )
    {
        advancedLayout->removeItem ( item );
        delete item->widget();
        delete item;
        item = NULL;
    }

    ui->verticalLayout_2->removeItem ( advancedLayout );

    delete advancedLayout;
    advancedLayout = NULL;

    setFixedHeight ( 100 );

    ui->advancedButton->setText ( "Advanced" );
}


void exportResult::makeHard()
{
    setSizePolicy ( QSizePolicy::Fixed, QSizePolicy::Preferred );
    setFixedHeight ( size().height() );

    QPropertyAnimation *animation = new QPropertyAnimation ( this, "minimumHeight" );
    animation->setDuration ( 700 );
    animation->setStartValue ( size().height() );
    animation->setEndValue ( 500 );
    animation->start();

    advancedLayout = new QGridLayout;

    QLabel *htmlcodeThumbnailLabel = new QLabel ( "HTML Thumbnail", this );
    QLabel *htmlcodeLabel = new QLabel ( "HTML", this );

    QLabel *bbcodeThumbnailLabel = new QLabel ( "BB Thumbnail", this );
    QLabel *bbcodeLabel = new QLabel ( "BB", this );

    QPlainTextEditFocus *htmlcode = new QPlainTextEditFocus ( this );
    QPlainTextEditFocus *htmlcodeThumbnail = new QPlainTextEditFocus ( this );

    QPlainTextEditFocus *bbcode = new QPlainTextEditFocus ( this );

    QPlainTextEditFocus *bbcodeThumbnail = new QPlainTextEditFocus ( this );

    QPushButton *htmlCodeC = new QPushButton ( this );
    htmlCodeC->setIcon ( QIcon ( ":/icons/images/clipboard.png" ) );
    QPushButton *htmlCodeThumbnailC = new QPushButton ( this );
    htmlCodeThumbnailC->setIcon ( QIcon ( ":/icons/images/clipboard.png" ) );
    QPushButton *bbCodeC = new QPushButton ( this );
    bbCodeC->setIcon ( QIcon ( ":/icons/images/clipboard.png" ) );
    QPushButton *bbCodeThumbnailC = new QPushButton ( this );
    bbCodeThumbnailC->setIcon ( QIcon ( ":/icons/images/clipboard.png" ) );

    clipMapper->setMapping ( htmlCodeC, HTMLCODE );
    QObject::connect ( htmlCodeC, SIGNAL ( clicked() ), clipMapper, SLOT ( map() ) );

    clipMapper->setMapping ( htmlCodeThumbnailC, HTMLCODETHUMBNAIL );
    QObject::connect ( htmlCodeThumbnailC, SIGNAL ( clicked() ), clipMapper, SLOT ( map() ) );

    clipMapper->setMapping ( bbCodeC, BBCODE );
    QObject::connect ( bbCodeC, SIGNAL ( clicked() ), clipMapper, SLOT ( map() ) );

    clipMapper->setMapping ( bbCodeThumbnailC, BBCODETHUMBNAIL );
    QObject::connect ( bbCodeThumbnailC, SIGNAL ( clicked() ), clipMapper, SLOT ( map() ) );

    htmlcodeThumbnail->setPlainText ( QString ( "<a href=\"%0\" title=\"Screenshot from QScreenShotter program\"><img alt=\"Screenshot\" src=\"%1\"></a>" )
                                          .arg ( baseCode + big ).arg ( baseCode + small ) );

    bbcodeThumbnail->setPlainText ( QString ( "[url=%0][img]%1[/img][/url]" ).arg ( baseCode + big ).arg ( baseCode + small ) );

    bbcode->setPlainText ( QString ( "[img]%0[/img]" ).arg ( ui->directLink->text() ) );
    htmlcode->setPlainText ( QString ( "<img src=\"%0\" alt=\"Screenshot\" title=\"Screenshot from QScreenShotter program\">" ).arg ( ui->directLink->text() ) );

    advancedLayout->addWidget ( htmlcodeLabel, 0, 0 );
    advancedLayout->addWidget ( htmlcode, 0, 1 );
    advancedLayout->addWidget ( htmlCodeC, 0, 2 );

    clipMapper->setMapping ( htmlCodeC, HTMLCODE );
    QObject::connect ( htmlCodeC, SIGNAL ( clicked() ), clipMapper, SLOT ( map() ) );

    advancedLayout->addWidget ( htmlcodeThumbnailLabel, 1, 0 );
    advancedLayout->addWidget ( htmlcodeThumbnail, 1, 1 );
    advancedLayout->addWidget ( htmlCodeThumbnailC, 1, 2 );

    clipMapper->setMapping ( htmlCodeThumbnailC, HTMLCODETHUMBNAIL );
    QObject::connect ( htmlCodeThumbnailC, SIGNAL ( clicked() ), clipMapper, SLOT ( map() ) );

    advancedLayout->addWidget ( bbcodeLabel, 2, 0 );
    advancedLayout->addWidget ( bbcode, 2, 1 );
    advancedLayout->addWidget ( bbCodeC, 2, 2 );

    clipMapper->setMapping ( bbCodeC, BBCODE );
    QObject::connect ( bbCodeC, SIGNAL ( clicked() ), clipMapper, SLOT ( map() ) );

    advancedLayout->addWidget ( bbcodeThumbnailLabel, 3, 0 );
    advancedLayout->addWidget ( bbcodeThumbnail, 3, 1 );
    advancedLayout->addWidget ( bbCodeThumbnailC, 3, 2 );

    clipMapper->setMapping ( bbCodeThumbnailC, BBCODETHUMBNAIL );
    QObject::connect ( bbCodeThumbnailC, SIGNAL ( clicked() ), clipMapper, SLOT ( map() ) );

    ui->verticalLayout_2->insertLayout ( 1, advancedLayout, 1 );

    ui->advancedButton->setText ( "Simple" );
}

void exportResult::advancedButton()
{
    if ( NULL == advancedLayout )
    {
        makeHard();
    } else {
        makeEasy();
    }

}

void exportResult::copyToClipboard  ( int num )
{
    QClipboard *c = QApplication::clipboard();

    switch ( num )
    {
        case Link:

            c->setText ( ui->link->text() );
            system::getCore()->trayIcon->showMessage ( "QSreenShotter Info Message", "Link to your screenshot is successfully copied to Clipboard." );

        break;

        case DirectLink:

            c->setText ( ui->directLink->text() );
            system::getCore()->trayIcon->showMessage ( "QSreenShotter Info Message", "Direct link to your screenshot is successfully copied to Clipboard." );

        break;

        case HTMLCODE:

            c->setText ( static_cast < QPlainTextEditFocus* > ( advancedLayout->itemAtPosition ( 0, 1 )->widget() )->toPlainText() );
            system::getCore()->trayIcon->showMessage ( "QSreenShotter Info Message", "HTML code with your screenshot is successfully copied to Clipboard." );

        break;

        case HTMLCODETHUMBNAIL:

            c->setText ( static_cast < QPlainTextEditFocus* > ( advancedLayout->itemAtPosition ( 1, 1 )->widget() )->toPlainText() );
            system::getCore()->trayIcon->showMessage ( "QSreenShotter Info Message", "HTML code with preview, linked to your screenshot is successfully copied to Clipboard." );

        break;

        case BBCODE:

            c->setText ( static_cast < QPlainTextEditFocus* > ( advancedLayout->itemAtPosition ( 2, 1 )->widget() )->toPlainText() );
            system::getCore()->trayIcon->showMessage ( "QSreenShotter Info Message", "BB code with your screenshot is successfully copied to Clipboard." );

        break;

        case BBCODETHUMBNAIL:

            c->setText ( static_cast < QPlainTextEditFocus* > ( advancedLayout->itemAtPosition ( 3, 1 )->widget() )->toPlainText() );
            system::getCore()->trayIcon->showMessage ( "QSreenShotter Info Message", "BB code with preview, linked to your screenshot is successfully copied to Clipboard." );

        break;

        default:
        break;
    }
}
