QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Functions.cpp \
    Instrument.cpp \
    User.cpp \
    guitarpage.cpp \
    katalog.cpp \
    main.cpp \
    mainmenu.cpp \
    mainwindow.cpp \
    removingdialog.cpp \
    search.cpp

HEADERS += \
    Header.h \
    guitarpage.h \
    katalog.h \
    mainmenu.h \
    mainwindow.h \
    removingdialog.h \
    search.h

FORMS += \
    guitarpage.ui \
    katalog.ui \
    mainmenu.ui \
    mainwindow.ui \
    removingdialog.ui \
    search.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
