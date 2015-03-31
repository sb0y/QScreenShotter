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

#unix:QMAKE_CXXFLAGS += -std=c++11 -std=gnu++11

unix:!mac:DEFINES += HAVE_X11
QT += core gui network

TARGET = qsc
TEMPLATE = app
unix:!mac:LIBS += -lX11 # TODO: remove
unix:!mac:LIBS += -lxcb
unix:!mac:LIBS += -lXfixes

win32:LIBS += -lgdiplus# -lmsimg32

include ( src/common.pri )

RESOURCES += \
    icons.qrc

VERSION = 0.0.0.2
QMAKE_TARGET_COMPANY = bagrintsev.me
QMAKE_TARGET_PRODUCT = QScreenShotter
QMAKE_TARGET_DESCRIPTION = Simple screenshot program
QMAKE_TARGET_COPYRIGHT = andrey@bagrintsev.me

HEADERS +=

SOURCES +=
