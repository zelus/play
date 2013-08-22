include(../../common.pri)

TEMPLATE = app
CONFIG += console
CONFIG += qt

INCLUDEPATH += $$INCLUDE_DIR/core
DEPENDPATH += $$INCLUDE_DIR/core

LIBS += -lcppunit -lqxcppunitd -L$$LIB_DIR/core -lcore
TARGET = ../../bin/test

OBJECTS_DIR = $$BUILD_DIR/test/objs
MOC_DIR = $$BUILD_DIR/test/mocs
UI_DIR = $$BUILD_DIR/test/uics

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
