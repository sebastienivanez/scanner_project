#-------------------------------------------------
#
# Project created by QtCreator 2016-11-12T12:01:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Scanner_interface
TEMPLATE = app


SOURCES += main.cpp\
        startup_window.cpp \
    scanner_window.cpp \
    usbsave_window.cpp \
    mail_window.cpp \
    scan_option_win.cpp

HEADERS  += startup_window.h \
    scanner_window.h \
    usbsave_window.h \
    mail_window.h \
    scan_option_win.h

FORMS    += startup_window.ui \
    scanner_window.ui \
    usbsave_window.ui \
    mail_window.ui \
    scan_option_win.ui
