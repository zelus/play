include(../../common.pri)

TEMPLATE = lib
CONFIG += console
CONFIG -= qt

TARGET = $$LIB_DIR/core/core

INCLUDEPATH += $$INCLUDE_DIR/core
DEPENDPATH += $$INCLUDE_DIR/core

OBJECTS_DIR = $$BUILD_DIR/core/objs
MOC_DIR = $$BUILD_DIR/core/mocs
UI_DIR = $$BUILD_DIR/core/uics

SOURCES += \
	Folder.cpp \
	Movie.cpp \
	Item.cpp \
	ItemManager.cpp \
	CoreException.cpp \
    ItemVisitor.cpp \
    ItemSearcher.cpp \
    IdItemSearcher.cpp
	


HEADERS += \
    Folder.h \
    Movie.h \
    Item.h \
    ItemManager.h \
    CoreException.h \
    ItemVisitor.h \
    ItemSearcher.h \
    IdItemSearcher.h

# Doxygen target
dox.target = doc
dox.commands = doxygen Doxyfile
dox.depends = $$SOURCES

QMAKE_EXTRA_TARGETS += dox
QMAKE_POST_LINK = make doc
