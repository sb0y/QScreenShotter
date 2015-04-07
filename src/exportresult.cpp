#include "exportresult.h"
#include "ui_exportresult.h"
#include "core.h"

exportResult::exportResult(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::exportResult)
{
    ui->setupUi ( this );

    setWindowTitle ( "WEB Export Results" );
}

exportResult::~exportResult()
{
    delete ui;
    system::getCore()->windows [ "exportResult" ] = NULL;
}

void exportResult::setResult ( QString big, QString small, QString userID )
{
    this->big = big;
    this->small = small;
    this->userID = userID;

    base = "http://" + system::getCore()->settings->value ( "WEB/site" ).toString();
    QString baseCode = base + "/content/screenshots/" + userID + "/";

    ui->directLink->setText ( baseCode + big );
    ui->link->setText ( base + "/screenshot/display/" + userID + "/" + big + "/" + small );

    QObject::connect ( ui->link, SIGNAL ( textChanged ( const QString& ) ), this, SLOT ( updateLabels() ) );
    QObject::connect ( ui->directLink, SIGNAL ( textChanged ( const QString& ) ), this, SLOT ( updateLabels() ) );

    ui->htmlcodeThumbnail->setPlainText ( QString ( "<a href=\"%0\" title=\"Screenshot from QScreenShotter program\"><img alt=\"Screenshot\" src=\"%1\"></a>" )
                                          .arg ( baseCode + big ).arg ( baseCode + small ) );

    ui->bbcodeThumbnail->setPlainText ( QString ( "[url=%0][img]%1[/img][/url]" ).arg ( baseCode + big ).arg ( baseCode + small ) );

    ui->bbcode->setPlainText ( QString ( "[img]%0[/img]" ).arg ( ui->directLink->text() ) );
    ui->htmlcode->setPlainText ( QString ( "<img src=\"%0\" alt=\"Screenshot\" title=\"Screenshot from QScreenShotter program\">" ).arg ( ui->directLink->text() ) );

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
