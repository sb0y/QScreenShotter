#ifndef QLINEEDITFOCUS_H
#define QLINEEDITFOCUS_H

#include <QLineEdit>
#include <QMouseEvent>

class QLineEditFocus : public QLineEdit
{
    Q_OBJECT
public:
    explicit QLineEditFocus(QWidget *parent = 0);

protected:
    void mousePressEvent ( QMouseEvent *e );


signals:

public slots:

};

#endif // QLINEEDITFOCUS_H
