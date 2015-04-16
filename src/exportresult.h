#ifndef EXPORTRESULT_H
#define EXPORTRESULT_H

#include <QDialog>
#include <QFormLayout>
#include <QGridLayout>
#include <QToolButton>
#include <QPropertyAnimation>
#include "qplaintexteditfocus.h"

namespace Ui {
class exportResult;
}

class exportResult : public QDialog
{
    Q_OBJECT

public:
    explicit exportResult ( QWidget *parent = 0 );
    ~exportResult();

    void setResult ( QString big, QString small, QString userID );
    void makeEasy();
    void makeHard();

public slots:
    void updateLabels();
    void advancedButton();

protected:

private:
    Ui::exportResult *ui;
    QString big, small, userID, base, baseCode;
    QGridLayout *advancedLayout;
};

#endif // EXPORTRESULT_H
