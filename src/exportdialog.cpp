#include "exportdialog.h"
#include "ui_exportdialog.h"
#include "core.h"

exportDialog::exportDialog(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::exportDialog)
{
    ui->setupUi ( this );

    //ui->progressBar->setMaximum ( 100 );
    //ui->progressBar->setMaximum ( 0 );

    setWindowTitle ( "Exporting file to WEB" );

    QObject::connect ( ui->cancelButton, SIGNAL ( clicked() ), this, SLOT ( emergencyShutdown() ) );

    system::getCore()->exp.setPixmap ( &system::getCore()->picture );
    system::getCore()->exp.setParent ( this );
    system::getCore()->exp.exec();
}

exportDialog::~exportDialog()
{
    delete ui;
}

void exportDialog::updateProgress ( qint64 bytesReceived, qint64 bytesTotal )
{
    if ( bytesReceived <= 0 )
    {
        return;
    }

    qint64 p = ( bytesTotal / bytesReceived ) * 100;

    ui->progressBar->setValue ( p );

    if ( p >= 100 )
    {
        close();
    }
}

void exportDialog::emergencyShutdown()
{
    QMessageBox::StandardButton reply;

    reply = QMessageBox::question ( this, "You sure?", "This will cancel your upload. You sure?",
                                    QMessageBox::Yes | QMessageBox::No );

    if ( reply == QMessageBox::Yes )
    {
        system::getCore()->exp.stop();
        close();
    }
}
