#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include "core.h"

settingsDialog::settingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::settingsDialog)
{
    ui->setupUi ( this );

    setWindowTitle ( QObject::tr ( "Settings" ) );

    ui->lineToken->setText ( system::getCore()->settings->value ( "WEB/accessToken" ).toString() );
    ui->lineSite->setText ( system::getCore()->settings->value ( "WEB/site" ).toString() );

    QObject::connect ( ui->buttonBox, SIGNAL ( accepted() ), this, SLOT ( save() ) );
    QObject::connect ( ui->commandLinkButton, SIGNAL ( clicked() ), this, SLOT ( goForToken() ) );
}

settingsDialog::~settingsDialog()
{
    delete ui;
}

void settingsDialog::save()
{
    system::getCore()->settings->setValue ( "WEB/accessToken", ui->lineToken->text() );
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
