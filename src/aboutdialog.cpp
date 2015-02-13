#include "aboutdialog.h"
#include "ui_aboutdialog.h"

aboutDialog::aboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::aboutDialog)
{
    ui->setupUi ( this );
    setWindowTitle ( QObject::tr ( "About the program" ) );
}

aboutDialog::~aboutDialog()
{
    delete ui;
}
