#ifndef QTTHREAD_H
#define QTTHREAD_H

#include <QObject>
#include <QThread>
#include <QTimer>
#include "mousespy.h"
#include <qdebug.h>

class threadWorker : public QObject
{
    Q_OBJECT
private slots:
    void onTimeout()
    {
        qDebug()<<"Worker::onTimeout get called from?: "<<QThread::currentThreadId();
    }

    void start()
    {

    }
};

class QTthread : public QThread
{
    Q_OBJECT
private:
    mouseSpy *worker;

public:
    QTthread();
    ~QTthread();
    void setWorker ( mouseSpy *w );

public slots:
    void run();
    void stop();
    void start();

signals:
    void finished();
};

#endif // THREAD_H
