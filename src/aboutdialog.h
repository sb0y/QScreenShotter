#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QDialog>
#include <QSysInfo>
#include <QtGlobal>
#ifdef HAVE_X11
    #include <sys/utsname.h>
#endif
#include <QApplication>

namespace Ui {
class aboutDialog;
}

class aboutDialog : public QDialog
{
    Q_OBJECT

public:
    explicit aboutDialog(QWidget *parent = 0);
    ~aboutDialog();

    QString getOS();

private:
    Ui::aboutDialog *ui;
};

#endif // ABOUTDIALOG_H
