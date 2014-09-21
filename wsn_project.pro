#-------------------------------------------------
#
# Project created by QtCreator 2014-07-10T09:45:01
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = wsn_project
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    gamedata.cpp \
    sensor.cpp \
    drawfield.cpp \
    game.cpp \
    gameconstants.cpp \
    coordinates.cpp

HEADERS  += mainwindow.h \
    gamedata.h \
    sensor.h \
    drawfield.h \
    game.h \
    gameconstants.h \
    exceptions.h \
    macros.h \
    coordinates.h

FORMS    += mainwindow.ui
