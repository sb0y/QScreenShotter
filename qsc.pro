#-------------------------------------------------
#
# Project created by QtCreator 2014-12-23T17:33:51
#
#-------------------------------------------------

unix:!mac:DEFINES += HAVE_X11

QT += core gui

DEFINES += QT_NO_USING_NAMESPACE

greaterThan ( QT_MAJOR_VERSION, 4 ) : QT += widgets

unix
{
    greaterThan ( QT_MAJOR_VERSION, 4 ) : QT += x11extras
}

TARGET = qsc
TEMPLATE = app
LIBS += -lX11 # TODO: remove
LIBS += -lxcb
LIBS += -lXfixes

include ( src/common.pri )

RESOURCES += \
    icons.qrc
