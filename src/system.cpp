#include "system.h"
#include "core.h"
#include <qdebug.h>

core *system::main = NULL;
int system::argc = 0;
char **system::argv = NULL;

system::system(QObject *parent) :
    QObject(parent)
{
}

core* system::getCore()
{
    if ( NULL == system::main )
    {
        system::main = new core ( argc, argv );
    }

    return system::main;
}

void system::setArgs (int ac, char **av )
{
    argc = ac;
    argv = av;
}

QString system::makeNewNameFromOld ( QFileInfo &file )
{
    QDir ABSDir = file.absoluteDir();

    QString ABSfileName = file.absoluteFilePath(),
            fileName = file.baseName();

    QRegExp rx ( ".*" + QRegExp::escape ( fileName ) + ".*" );

    if ( !rx.isValid() )
    {
        qDebug() << "rx is not valid";
        return "";
    }

    QFileInfoList list = ABSDir.entryInfoList();
    QStringList resList;

    QString tmp;

    for ( int i = 0; list.size() > i; ++i )
    {
         QFileInfo fileInfo = list.at ( i );

         tmp = fileInfo.fileName();

         if ( tmp.contains ( rx ) )
         {
             resList << tmp;
         }

         tmp.clear();
   }

   int filePos = 1;
   bool isNum = false;

   for ( int i = 0; resList.size() > i; ++i )
   {
        tmp = resList [ i ].at ( resList [ i ].size() - 5 );
        filePos = tmp.toInt ( &isNum, 10 );

        if ( !isNum )
        {
            filePos = 0;
            continue;
        }
   }

   ++filePos;
   return ( fileName + QString::number ( filePos ) );
}
