#-------------------------------------------------
#
# Project created by QtCreator 2014-12-23T17:33:51
#
#-------------------------------------------------

greaterThan ( QT_MAJOR_VERSION, 4 )
{
    QT += widgets
    DEFINES += HAVE_QT5
}

unix:!mac:DEFINES += HAVE_X11
greaterThan ( QT_MAJOR_VERSION, 4 ) : unix:QT += x11extras
QT += core gui

TARGET = qsc
TEMPLATE = app
unix:!mac:LIBS += -lX11 # TODO: remove
unix:!mac:LIBS += -lxcb
unix:!mac:LIBS += -lXfixes

include ( src/common.pri )

RESOURCES += \
    icons.qrc
