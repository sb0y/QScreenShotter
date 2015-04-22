#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include "core.h"

settingsDialog::settingsDialog ( QWidget *parent ) :
    QDialog ( parent ),
    ui ( new Ui::settingsDialog )
{
    ui->setupUi ( this );

    setAttribute ( Qt::WA_DeleteOnClose );
    setWindowTitle ( QObject::tr ( "Settings" ) );

    ui->lineToken->setText ( system::getCore()->settings->value ( "WEB/accessToken" ).toString() );
    ui->lineSite->setText ( system::getCore()->settings->value ( "WEB/site" ).toString() );

    ui->timeout->setValue ( system::getCore()->settings->value ( "main/timeout" ).toInt() );

    QObject::connect ( ui->buttonBox, SIGNAL ( accepted() ), this, SLOT ( save() ) );
    QObject::connect ( ui->commandLinkButton, SIGNAL ( clicked() ), this, SLOT ( goForToken() ) );
}

settingsDialog::~settingsDialog()
{
    system::getCore()->windows [ "settingsDialog" ] = NULL;
    deleteLater();
    delete ui;
}

void settingsDialog::save()
{
    system::getCore()->settings->setValue ( "WEB/accessToken", ui->lineToken->text() );
    system::getCore()->settings->sync();
    close();
}

void settingsDialog::goForToken()
{
    QUrl url;
    url.setScheme ( "http" );
    url.setHost ( ui->lineSite->text() );
    url.setPath ( "/screenshot/token" );

    QDesktopServices::openUrl ( url );
}

void settingsDialog::processHTML()
{

}

void settingsDialog::activateTab ( int tabIndex )
{
    if ( tabIndex != -1 )
        ui->tabWidget->setCurrentIndex ( tabIndex );
}
