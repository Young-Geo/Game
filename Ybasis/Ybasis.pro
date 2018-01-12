TEMPLATE = lib
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
TARGET = ../Ybasis
HEADERS += \
    Ybasis.h \
    Ywork.h \
    Ylog.h \
    Yalone.hpp \
    Ytime.h \
    Yconfig.h \
    YS.h \
    Ysocket.h \
    Ymsgtool.h \
    Ychain.h \
    Ypackage.h

SOURCES += \
    Ybsis.cpp \
    Ywork.cpp \
    Ylog.cpp \
    Ytime.cpp \
    Yconfig.cpp \
    YS.cpp \
    Ysocket.cpp \
    Ymsgtool.cpp \
    Ychain.cpp \
    Ypackage.cpp
