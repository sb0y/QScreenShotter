#ifndef EXPORTRESULT_H
#define EXPORTRESULT_H

#include <QDialog>

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

public slots:
    void updateLabels();

protected:

private:
    Ui::exportResult *ui;
    QString big, small, userID, base;
};

#endif // EXPORTRESULT_H
