#ifndef GRABBERBASE_H
#define GRABBERBASE_H

#include <QDialog>
#include <QTimer>
#include <QTimerEvent>
#include <qdebug.h>
#include <QRect>
#include <QScreen>
#include <QApplication>

class grabberBase : public QDialog
{
    Q_OBJECT
public:

    explicit grabberBase();
    virtual ~grabberBase();
    virtual void done() = 0;
    virtual void prepare() = 0;

protected:

private:

signals:

public slots:
    virtual void start() = 0;
};

#endif // GRABBERBASE_H
