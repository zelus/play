include(../../common.pri)

TEMPLATE = app

INCLUDEPATH += $$INCLUDE_DIR/core \
               $$INCLUDE_DIR/ui
DEPENDPATH += $$INCLUDE_DIR/core \
              $$INCLUDE_DIR/ui

LIBS += -L$$LIB_DIR/core -lcore \
        -L$$LIB_DIR/ui -lui
TARGET = ../../bin/play

OBJECTS_DIR = $$BUILD_DIR/app/objs
MOC_DIR = $$BUILD_DIR/app/mocs
UI_DIR = $$BUILD_DIR/app/uics

SOURCES += main.cpp

HEADERS += 
