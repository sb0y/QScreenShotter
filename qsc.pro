#-------------------------------------------------
#
# Project created by QtCreator 2014-12-23T17:33:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qsc
TEMPLATE = app
LIBS += -lX11 # TODO: remove
LIBS += -lxcb
LIBS += -lXfixes

include ( src/common.pri )

RESOURCES += \
    icons.qrc
