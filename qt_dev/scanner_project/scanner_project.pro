#-------------------------------------------------
#
# Project created by QtCreator 2016-11-02T14:22:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = scanner_project
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    copyfile.cpp \
    logger.cpp \
    scanner.cpp

HEADERS  += mainwindow.h \
    copyfile.h \
    scanner.h \
    logger.h

FORMS    += mainwindow.ui

LIBS = -lsane
