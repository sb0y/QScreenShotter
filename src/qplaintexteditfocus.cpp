#include "qplaintexteditfocus.h"

QPlainTextEditFocus::QPlainTextEditFocus(QWidget *parent) :
    QPlainTextEdit(parent)
{
}

void QPlainTextEditFocus::mousePressEvent ( QMouseEvent *e )
{
    selectAll();
    e->ignore();
}
