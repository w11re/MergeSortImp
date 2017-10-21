TEMPLATE = app

include(../defaults.pri)

CONFIG += console
CONFIG += c++14
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += $$PWD/../dependencies/Catch

macx{
QMAKE_CXXFLAGS += -stdlib=libc++
}

QMAKE_CXXFLAGS += -Wall

HEADERS += ../src/darray.h

SOURCES += main.cpp \
