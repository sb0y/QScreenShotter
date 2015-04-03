#include "exportresult.h"
#include "ui_exportresult.h"

exportResult::exportResult(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::exportResult)
{
    ui->setupUi(this);
}

exportResult::~exportResult()
{
    delete ui;
}
