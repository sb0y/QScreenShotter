#include "qlineeditfocus.h"
#include <qdebug.h>

QLineEditFocus::QLineEditFocus(QWidget *parent) :
    QLineEdit(parent)
{
}


void QLineEditFocus::mousePressEvent ( QMouseEvent *e )
{
    selectAll();
    e->ignore();
}

