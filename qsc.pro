#-------------------------------------------------
#
# Project created by QtCreator 2014-12-23T17:33:51
#
#-------------------------------------------------

greaterThan ( QT_MAJOR_VERSION, 4 )
{
    QT += widgets
    DEFINES += HAVE_QT5
    unix:QT += x11extras
    win32:QT += winextras
}

unix:!mac:DEFINES += HAVE_X11
QT += core gui

TARGET = qsc
TEMPLATE = app
unix:!mac:LIBS += -lX11 # TODO: remove
unix:!mac:LIBS += -lxcb
unix:!mac:LIBS += -lXfixes

win32:LIBS += -lgdiplus

include ( src/common.pri )

RESOURCES += \
    icons.qrc
