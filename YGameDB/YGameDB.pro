TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += ../Ybasis

SOURCES += main.cpp \
    ocicursor.cpp \
    ocidatabase.cpp

HEADERS += \
    ocicursor.h \
    ocidatabase.h