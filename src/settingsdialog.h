#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QDesktopServices>

namespace Ui {
class settingsDialog;
}

class settingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit settingsDialog(QWidget *parent = 0);
    ~settingsDialog();

    void processHTML();

private:
    Ui::settingsDialog *ui;

public slots:
    void save();
    void goForToken();
};

#endif // SETTINGSDIALOG_H
