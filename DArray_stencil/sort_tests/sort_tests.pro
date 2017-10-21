TEMPLATE = app

include(../defaults.pri)

CONFIG += console
CONFIG += c++14
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += $$PWD/../sort_src

INCLUDEPATH += $$PWD/../dependencies/Catch

macx{
QMAKE_CXXFLAGS += -stdlib=libc++
}

QMAKE_CXXFLAGS += -Wall

HEADERS += ../sort_src/sort.h

SOURCES += \
    main.cpp


