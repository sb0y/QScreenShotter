#ifndef EXPORTRESULT_H
#define EXPORTRESULT_H

#include <QDialog>
#include <QFormLayout>
#include <QGridLayout>
#include <QToolButton>
#include <QPropertyAnimation>
#include <QSignalMapper>
#include <QClipboard>
#include "qplaintexteditfocus.h"

namespace Ui {
class exportResult;
}

class exportResult : public QDialog
{
    Q_OBJECT

    enum ClipboardNums
    {
        Link = 0,
        DirectLink = 1,
        HTMLCODE = 2,
        HTMLCODETHUMBNAIL = 3,
        BBCODE = 4,
        BBCODETHUMBNAIL = 5
    };

public:
    explicit exportResult ( QWidget *parent = 0 );
    ~exportResult();

    void setResult ( QString big, QString small, QString userID );
    void makeEasy();
    void makeHard();

    QSignalMapper *clipMapper;


public slots:
    void updateLabels();
    void advancedButton();
    void copyToClipboard ( int num );

protected:

private:
    Ui::exportResult *ui;
    QString big, small, userID, base, baseCode;
    QGridLayout *advancedLayout;
};

#endif // EXPORTRESULT_H
