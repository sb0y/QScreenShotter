#ifndef WEBEXPORT_H
#define WEBEXPORT_H

#include <QObject>
#include <QPixmap>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QBuffer>
#include <QHttpMultiPart>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonArray>
#include <qdebug.h>
#define URL "http://bagrintsev.me/screenshot/upload"

class WEBExport : public QObject
{
    Q_OBJECT
public:
    explicit WEBExport(QObject *parent = 0);
    void setPixmap ( QPixmap *p );
    void exec();
    void pixmapToByteArray();
    void stop();

    QNetworkReply *reply;
    QByteArray bytes;
    QPixmap *pixmap;
    QNetworkAccessManager net;
    QHttpMultiPart *multipart;

signals:

public slots:
    void replyFinished ( QNetworkReply * );
    void replyError ( QNetworkReply::NetworkError );
    void slotReadyRead();

};

#endif // WEBEXPORT_H
