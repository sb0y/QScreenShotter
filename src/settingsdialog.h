#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>

namespace Ui {
class settingsDialog;
}

class settingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit settingsDialog(QWidget *parent = 0);
    ~settingsDialog();

private:
    Ui::settingsDialog *ui;

public slots:
    void save();
    void select();
};

#endif // SETTINGSDIALOG_H
