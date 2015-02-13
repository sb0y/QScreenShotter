#ifndef MENUBUTTON_H
#define MENUBUTTON_H

#include <QAbstractButton>
#include <QStylePainter>
#include <QMenu>
#include "mainwindow.h"

class menuButton : public QAbstractButton
{
    Q_OBJECT
public:
    explicit menuButton(QWidget *parent = 0);
    void paintEvent(QPaintEvent *e);
    QSize sizeHint() const;
    QMenu* getMenu();

protected:
    QMenu *menu;
    MainWindow *mainw;
    void mousePressEvent ( QMouseEvent *e );
    QStyleOptionButton options;
   // bool event ( QEvent *e );

signals:

public slots:
    void toUp();

};

#endif // MENUBUTTON_H
