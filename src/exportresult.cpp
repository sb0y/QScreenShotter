#include "exportresult.h"
#include "ui_exportresult.h"
#include "core.h"

exportResult::exportResult(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::exportResult)
{
    ui->setupUi ( this );

    setWindowTitle ( "Results" );
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

    ui->htmlcodeThumbnail->setPlainText ( QString ( "<a href=\"%0\" title=\"Screenshot from QScreenShotter program\"><img alt=\"Screenshot\" src=\"%1\"></a>" )
                                          .arg ( baseCode + big ).arg ( baseCode + small ) );

    ui->bbcodeThumbnail->setPlainText ( QString ( "[url=%0][img]%1[/img][/url]" ).arg ( baseCode + big ).arg ( baseCode + small ) );

    ui->bbcode->setPlainText ( QString ( "[img]%0[/img]" ).arg ( ui->directLink->text() ) );
    ui->htmlcode->setPlainText ( QString ( "<img src=\"%0\" alt=\"Screenshot\" title=\"Screenshot from QScreenShotter program\">" ).arg ( ui->directLink->text() ) );

}
