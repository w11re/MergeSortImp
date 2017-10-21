include(../defaults.pri)

CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++14

TARGET   = darray
TEMPLATE = lib

macx{
QMAKE_CXXFLAGS += -stdlib=libc++
}

QMAKE_CXXFLAGS += -Wall

HEADERS += \
    sort.h

