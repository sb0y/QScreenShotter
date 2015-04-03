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
    explicit exportResult(QWidget *parent = 0);
    ~exportResult();

private:
    Ui::exportResult *ui;
};

#endif // EXPORTRESULT_H
