include(../../common.pri)

TEMPLATE = lib

QT+=widgets

TARGET = $$LIB_DIR/ui/ui

INCLUDEPATH += $$INCLUDE_DIR/ui
VPATH += $$INCLUDE_DIR/ui
#DEPENDPATH += $$INCLUDE_DIR/ui

OBJECTS_DIR = $$BUILD_DIR/ui/objs
MOC_DIR = $$BUILD_DIR/ui/mocs
UI_DIR = $$BUILD_DIR/ui/uics

SOURCES += \ 
    Workbench.cpp

HEADERS += \
    Workbench.h
