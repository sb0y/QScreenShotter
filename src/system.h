#ifndef SYSTEM_H
#define SYSTEM_H

#include <QObject>
#include <QString>
#include <QFileInfo>
class core;

class system : public QObject
{
    Q_OBJECT

private:
    static core *instance;
    static int argc;
    static char **argv;

public:
    explicit system(QObject *parent = 0);
    static core* getCore();
    static void setArgs ( int argc, char **argv );
    static QString makeNewNameFromOld ( QFileInfo &file );

signals:

public slots:

};

#endif // SYSTEM_H
