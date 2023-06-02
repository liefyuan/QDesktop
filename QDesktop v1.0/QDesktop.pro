#-------------------------------------------------
#
# Project created by QtCreator 2018-11-06T15:59:36
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QDesktop
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    weather.cpp \
    evenfilter.cpp \
    appinit.cpp

HEADERS  += mainwindow.h \
    weather.h \
    evenfilter.h \
    appinit.h \
    config.h

RESOURCES += \
    resource.qrc
