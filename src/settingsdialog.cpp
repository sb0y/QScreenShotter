#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include "core.h"

settingsDialog::settingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::settingsDialog)
{
    ui->setupUi ( this );

    setWindowTitle ( QObject::tr ( "Settings" ) );

    ui->lineEdit->setText( system::getCore()->settings->value ( "WEB/accessToken" ).toString() );

    QObject::connect ( ui->lineEdit, SIGNAL ( cursorPositionChanged ( int, int ) ), this, SLOT ( select() ) );
    QObject::connect ( ui->buttonBox, SIGNAL ( accepted() ), this, SLOT ( save() ) );
}

settingsDialog::~settingsDialog()
{
    delete ui;
}

void settingsDialog::save()
{
    system::getCore()->settings->setValue ( "WEB/accessToken", ui->lineEdit->text() );
    close();
}

void settingsDialog::select()
{
    ui->lineEdit->selectAll();
}
