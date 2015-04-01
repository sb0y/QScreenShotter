#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QPushButton>
#include <QComboBox>
#include "system.h"
#include <QPixmap>
#include <QResizeEvent>
#include <QStyle>
#include <QDialog>
#include <QMenu>
#include <QFileDialog>
#include <QDir>
#include <QFileInfoList>
#include <QFileInfo>
#include <QStringList>
#include <QFile>
#include <QImageWriter>
#include <qdebug.h>
#include "screenshot.h"
#include "settingsdialog.h"

class core;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    enum actions {
        DEFAULT = -1,
        TAKE_AREA = 0,
        TAKE_WINDOW = 1,
        TAKE_RECTANGLE = 2
    };

    actions action;

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    int init ( core *c );
    void setScreenPic ( QPixmap &pic );
    int setLabelText ( QString text );

public slots:
    void setMainAction ( enum actions action = DEFAULT );
    void openFileDialog();
    void openSettingsDialog();
    //void setVisible ( bool visible );

signals:

private:
    Ui::MainWindow *ui;
    core *main;
    void resizeEvent ( QResizeEvent *event );
    void paintEvent ( QPaintEvent *);
    void keyPressEvent ( QKeyEvent *e );
    void mouseMoveEvent ( QMouseEvent *e );
    //bool eventFilter ( QObject *obj, QEvent *event );

protected:
    //void showEvent ( QShowEvent *e );
};

#endif // MAINWINDOW_H
