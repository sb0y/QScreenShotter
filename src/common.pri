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
    src/customframe.cpp \
    src/desktopgrabber.cpp \
    src/qtthread.cpp \
    src/grabberbasedialog.cpp \
    src/webexport.cpp \
    src/settingsdialog.cpp \
    src/qlineeditfocus.cpp \
    src/exportdialog.cpp \
    src/exportresult.cpp

HEADERS  += src/mainwindow.h \
    src/core.h \
    src/system.h \
    src/screenshot.h \
    src/aboutdialog.h \
    src/menubutton.h \
    src/grabberbase.h \
    src/rectanglegrabber.h \
    src/rubberband.h \
    src/customframe.h \
    src/desktopgrabber.h \
    src/qtthread.h \
    src/grabberbasedialog.h \
    src/webexport.h \
    src/settingsdialog.h \
    src/qlineeditfocus.h \
    src/exportdialog.h \
    src/exportresult.h

unix:!mac:HEADERS  += src/windowgrabberlinux.h \
    src/x11info.h \
    #src/xwindowrectangle.h \
    src/neweventfilter.h

unix:!mac:SOURCES += src/windowgrabberlinux.cpp \
    src/x11info.cpp \
    #src/xwindowrectangle.cpp \
    src/neweventfilter.cpp

win32:HEADERS += src/windowgrabberwindows.h \
                src/neweventfilter.h \
                src/mousespy.h \
                src/windowswindow.h

win32:SOURCES += src/windowgrabberwindows.cpp \
                src/neweventfilter.cpp \
                src/mousespy.cpp \
                src/windowswindow.cpp


FORMS    += src/mainwindow.ui \
    src/aboutdialog.ui \
    src/settingsdialog.ui \
    src/exportdialog.ui \
    src/exportresult.ui
