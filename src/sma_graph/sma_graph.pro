#-------------------------------------------------
#
# Project created by QtCreator 2016-02-21T16:02:19
#
#-------------------------------------------------

QT       += core gui

CONFIG += c++11

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
    ../World.cpp \
    displayer.cpp \
    ../Neutral_faction.cpp \
    qplanet.cpp

HEADERS  += mainwindow.h \
    ../Colonized_planet.hpp \
    ../Faction.hpp \
    ../Free_planet.hpp \
    ../Mother_land.hpp \
    ../Virtual_planet.hpp \
    ../World.hpp \
    displayer.h \
    ../Neutral_faction.hpp \
    qplanet.h

FORMS    += mainwindow.ui

DISTFILES += \
    ../Petite note.txt \
    ../Makefile
