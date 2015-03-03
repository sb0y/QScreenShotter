#ifndef QTTHREAD_H
#define QTTHREAD_H

#include <QObject>
#include <QThread>
#include <QTimer>
#ifdef WIN32
    #include "mousespy.h"
#endif
#include <qdebug.h>

class threadWorker : public QObject
{
    Q_OBJECT
private slots:
    void onTimeout()
    {
        qDebug() << "Worker::onTimeout get called from?: " << QThread::currentThreadId();
    }

    void start()
    {

    }
};

class QTthread : public QThread
{
    Q_OBJECT
private:
    QObject *worker;

public:
    QTthread();
    ~QTthread();
    void setWorker (QObject *w );

public slots:
    void run();
    void stop();
    void start();

signals:
    void finished();
};

#endif // THREAD_H
