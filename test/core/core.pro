TEMPLATE = app
CONFIG += console
CONFIG += qt

include(../../common.pri)

LIBS = -lcppunit -lqxcppunitd

SOURCES += main.cpp \
    MockItem.cpp \
    TestFolder.cpp \
    TestItem.cpp \
    TestItemManager.cpp \
    TestMovie.cpp

HEADERS += \
    TestFolder.h \
    MockItem.h \
    TestItem.h \
    TestItemManager.h \
    TestMovie.h
