TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

QT += Ybasis

LIBS += ../libYbasis.so.1.0.0

LIBS += Ybasis

SOURCES += main.cpp

TARGET = GameGate
