#include "webexport.h"

WEBExport::WEBExport(QObject *parent) :
    QObject(parent)
{
    pixmap = NULL;
    reply = NULL;
    request.setUrl ( QUrl ( URL ) );
    net.setNetworkAccessible ( QNetworkAccessManager::Accessible );
}

void WEBExport::setPixmap ( QPixmap *p )
{
    pixmap = p;
}


void WEBExport::pixmapToByteArray()
{
    if ( NULL == pixmap )
    {
        return;
    }

    QBuffer buffer ( &bytes );
    buffer.open ( QIODevice::WriteOnly );
    pixmap->save ( &buffer, "PNG" );
}

void WEBExport::replyFinished ( QNetworkReply *reply )
{
    qDebug() << "here";
    qDebug() << reply->readAll();
}

void WEBExport::replyError ( QNetworkReply::NetworkError reply )
{
    qDebug() << "error " << reply;
}

void WEBExport::exec()
{
    QHttpMultiPart *multiPart = new QHttpMultiPart ( QHttpMultiPart::FormDataType );
    QHttpPart textPart;
    textPart.setHeader ( QNetworkRequest::ContentDispositionHeader, QVariant ( "form-data; name=\"text\"" ) );
    textPart.setBody ( "my text" );

    pixmapToByteArray();

    QHttpPart imagePart;
    imagePart.setHeader ( QNetworkRequest::ContentTypeHeader, QVariant ( "image/png" ) );
    imagePart.setHeader ( QNetworkRequest::ContentDispositionHeader, QVariant ( "form-data; name=\"image\"" ) );
    imagePart.setBody ( bytes );

    multiPart->append ( textPart );
    multiPart->append ( imagePart );

    reply = net.post ( request, multiPart );

    QObject::connect ( &net, SIGNAL ( finished ( QNetworkReply* ) ), this, SLOT ( replyFinished ( QNetworkReply* ) ) );

    QObject::connect ( reply, SIGNAL ( error ( QNetworkReply::NetworkError ) ), this, SLOT ( replyError ( QNetworkReply::NetworkError ) ) );
    QObject::connect ( reply, SIGNAL ( readyRead() ), this, SLOT ( slotReadyRead() ) );
}
