TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

QT += Ybasis

INCLUDEPATH += ../Ybasis

LIBS += ../libYbasis.so.1.0.0

SOURCES += main.cpp \
    ocicursor.cpp \
    ocidatabase.cpp

HEADERS += \
    ocicursor.h \
    ocidatabase.h


TARGET = GameManage
