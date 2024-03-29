QT  += core gui network sql serialport

greaterThan(QT_MAJOR_VERSION,5): QT += core5compat
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
CONFIG += console

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    chartable.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    redcapella.cpp \
    registration.cpp

HEADERS += \
    chartable.h \
    login.h \
    mainwindow.h \
    redcapella.h \
    registration.h

FORMS += \
    login.ui \
    mainwindow.ui \
    registration.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
