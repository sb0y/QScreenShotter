#include "webexport.h"
#include "core.h"

WEBExport::WEBExport(QObject *parent) :
    QObject(parent)
{
    pixmap = NULL;
    reply = NULL;
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
    qDebug() << reply->readAll();
}

void WEBExport::replyError ( QNetworkReply::NetworkError reply )
{
    qDebug() << "error " << reply;
}

void WEBExport::exec()
{
    QString token = system::getCore()->settings->value ( "WEB/accessToken" ).toString();

    if ( token.isEmpty() )
    {
        QMessageBox messageBox;
        messageBox.critical ( getWindow ( "main", MainWindow* ),
                              "Error",
                              "An error has occured!\n\nCheck your program settings. Token can not be empty." );

        messageBox.setFixedSize ( 500, 200 );
        return;
    }

    QNetworkRequest request;
    request.setUrl ( QUrl ( URL ) );

    QHttpMultiPart *multiPart = new QHttpMultiPart ( QHttpMultiPart::FormDataType );
    QHttpPart textPart;
    textPart.setHeader ( QNetworkRequest::ContentDispositionHeader, QVariant ( "form-data; name=\"token\"" ) );
    textPart.setBody ( token.toStdString().c_str() );

    pixmapToByteArray();

    QHttpPart imagePart;
    imagePart.setHeader ( QNetworkRequest::ContentTypeHeader, QVariant ( "image/png" ) );
    imagePart.setHeader ( QNetworkRequest::ContentDispositionHeader, QVariant ( "form-data; name=\"files[]\"; filename=\"screenshot.png\"" ) );
    imagePart.setBody ( bytes );

    multiPart->append ( textPart );
    multiPart->append ( imagePart );

    reply = net.post ( request, multiPart );

    QObject::connect ( reply, SIGNAL ( uploadProgress ( qint64, qint64 ) ), parent(), SLOT ( updateProgress ( qint64, qint64 ) ) );
    QObject::connect ( &net, SIGNAL ( finished ( QNetworkReply* ) ), this, SLOT ( replyFinished ( QNetworkReply* ) ) );
    QObject::connect ( reply, SIGNAL ( error ( QNetworkReply::NetworkError ) ), this, SLOT ( replyError ( QNetworkReply::NetworkError ) ) );
    QObject::connect ( reply, SIGNAL ( readyRead() ), this, SLOT ( slotReadyRead() ) );
}

void WEBExport::stop()
{
    reply->abort();
    delete reply;
    reply = NULL;
    pixmap = NULL;
}

void WEBExport::slotReadyRead()
{
    //Debug() << "ready read";
}
