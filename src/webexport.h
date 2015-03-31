#ifndef WEBEXPORT_H
#define WEBEXPORT_H

#include <QObject>
#include <QPixmap>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QBuffer>
#include <QHttpMultiPart>
#define URL "http://localhost"

class WEBExport : public QObject
{
    Q_OBJECT
public:
    explicit WEBExport(QObject *parent = 0);
    void setPixmap ( QPixmap *p );
    void exec();
    void pixmapToByteArray();

    QNetworkReply *reply;
    QByteArray bytes;
    QPixmap *pixmap;
    QNetworkAccessManager net;
    QNetworkRequest request;
    QHttpMultiPart *multipart;

signals:

public slots:
    void replyFinished ( QNetworkReply * );
    void replyError ( QNetworkReply::NetworkError );
    void slotReadyRead() { qDebug() << "ready read"; }

};

#endif // WEBEXPORT_H
