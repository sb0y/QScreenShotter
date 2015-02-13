SOURCES += src/main.cpp\
        src/mainwindow.cpp \
        src/core.cpp \
        src/system.cpp \
    src/screenshot.cpp \
    src/aboutdialog.cpp \
    src/menubutton.cpp \
    src/grabberbase.cpp \
    src/desktopgrabberlinux.cpp \
    src/windowgrabberlinux.cpp \
    src/xwindowrectangle.cpp \
    src/neweventfilter.cpp \
    src/rectanglegrabber.cpp \
    src/rubberband.cpp \
    src/customframe.cpp \
    src/x11info.cpp

HEADERS  += src/mainwindow.h \
    src/core.h \
    src/system.h \
    src/screenshot.h \
    src/aboutdialog.h \
    src/menubutton.h \
    src/grabberbase.h \
    src/desktopgrabberlinux.h \
    src/windowgrabberlinux.h \
    src/xwindowrectangle.h \
    src/neweventfilter.h \
    src/rectanglegrabber.h \
    src/rubberband.h \
    src/customframe.h \
    src/x11info.h

FORMS    += src/mainwindow.ui \
    src/aboutdialog.ui

OTHER_FILES += \
    src/test.qml
