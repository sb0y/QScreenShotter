SOURCES += src/main.cpp\
        src/mainwindow.cpp \
        src/core.cpp \
        src/system.cpp \
    src/screenshot.cpp \
    src/aboutdialog.cpp \
    src/menubutton.cpp \
    src/grabberbase.cpp \
    src/rectanglegrabber.cpp \
    src/rubberband.cpp \
    src/customframe.cpp

HEADERS  += src/mainwindow.h \
    src/core.h \
    src/system.h \
    src/screenshot.h \
    src/aboutdialog.h \
    src/menubutton.h \
    src/grabberbase.h \
    src/rectanglegrabber.h \
    src/rubberband.h \
    src/customframe.h

unix:!mac:HEADERS  += src/desktopgrabberlinux.h \
    src/windowgrabberlinux.h \
    src/x11info.h \
    src/xwindowrectangle.h \
    src/neweventfilter.h

unix:!mac:SOURCES += src/desktopgrabberlinux.cpp \
    src/windowgrabberlinux.cpp \
    src/x11info.cpp \
    src/xwindowrectangle.cpp \
    src/neweventfilter.cpp

FORMS    += src/mainwindow.ui \
    src/aboutdialog.ui
