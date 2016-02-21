#-------------------------------------------------
#
# Project created by QtCreator 2016-02-21T16:02:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sma_graph
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ../Colonized_planet.cpp \
    ../Faction.cpp \
    ../Free_planet.cpp \
    ../Mother_land.cpp \
    ../Virtual_planet.cpp \
    ../World.cpp

HEADERS  += mainwindow.h \
    ../Colonized_planet.hpp \
    ../Faction.hpp \
    ../Free_planet.hpp \
    ../Mother_land.hpp \
    ../Virtual_planet.hpp \
    ../World.hpp

FORMS    += mainwindow.ui

DISTFILES += \
    ../Petite note.txt \
    ../Makefile
