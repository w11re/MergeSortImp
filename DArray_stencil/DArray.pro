TEMPLATE = subdirs
CONFIG += ordered
SUBDIRS = \
    sort_tests \
    tests

OTHER_FILES += \
    defaults.pri

QMAKE_CXXFLAGS += -O0
