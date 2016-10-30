#-------------------------------------------------
#
# Project created by QtCreator 2016-10-23T10:00:01
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SpriteEditor
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    spriteframe.cpp \
    spriteframecollection.cpp \
    spritecanvas.cpp \
    gifexporter.cpp

HEADERS  += mainwindow.h \
    spriteframe.h \
    spriteframecollection.h \
    spritecanvas.h \
    gifexporter.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc
