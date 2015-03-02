#include "qtthread.h"

QTthread::QTthread()
{
    worker = NULL;
}

QTthread::~QTthread()
{

}

void QTthread::run()
{
    qDebug()<<"From work thread: "<<currentThreadId();
    QTimer timer;
    connect(&timer, SIGNAL(timeout()), worker, SLOT(onTimeout()));
    timer.start(1000);

    exec();
}

void QTthread::stop()
{
    delete worker;
}

void QTthread::start()
{
}

void QTthread::setWorker ( QObject *w )
{
    worker = w;
}
