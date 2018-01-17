TEMPLATE = lib
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
TARGET = ../Ybasis
LIBS += -lmsgpack
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
    Ypackage.h \
    Ychain.hpp \
    YSocketClient.h \
    Yuser.h

SOURCES += \
    Ywork.cpp \
    Ylog.cpp \
    Ytime.cpp \
    Yconfig.cpp \
    YS.cpp \
    Ysocket.cpp \
    Ymsgtool.cpp \
    Ypackage.cpp \
    YSocketClient.cpp \
    Yuser.cpp \
    Ybasis.cpp
