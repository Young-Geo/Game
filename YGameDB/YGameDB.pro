TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

QT += Ybasis

INCLUDEPATH += ../Ybasis
#SOURCES += ../Ybasis

LIBS += ../libYbasis.so.1.0.0 -lmysqlclient -levent

SOURCES += main.cpp \
    ocicursor.cpp \
    ocidatabase.cpp \
    work.cpp \
    DBYS.cpp \
    DBconfig.cpp

HEADERS += \
    ocicursor.h \
    ocidatabase.h \
    work.h \
    DBYS.h \
    DBconfig.h


TARGET = GameManage
