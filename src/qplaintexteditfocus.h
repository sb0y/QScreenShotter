#ifndef QPLAINTEXTEDITFOCUS_H
#define QPLAINTEXTEDITFOCUS_H

#include <QWidget>
#include <QPlainTextEdit>

class QPlainTextEditFocus : public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit QPlainTextEditFocus(QWidget *parent = 0);

protected:
    void mousePressEvent ( QMouseEvent *e );

signals:

public slots:

};

#endif // QPLAINTEXTEDITFOCUS_H
