QMAKE_CXXFLAGS += -std=c++0x

DEPENDPATH += $$PWD/src/core/
DEPENDPATH += $$PWD/src/tagger/

INCLUDEPATH  += $$PWD/src/core/
INCLUDEPATH  += $$PWD/src/tagger/

include(src/tagger/tagger.pri)

SOURCES      += \
        $$PWD/src/core/Item.cpp \
        $$PWD/src/core/Folder.cpp \
        $$PWD/src/core/Movie.cpp \
        $$PWD/src/core/ItemManager.cpp \
    ../../src/core/CoreException.cpp
	
HEADERS      += \
        $$PWD/src/core/Item.h \
        $$PWD/src/core/Folder.h \
        $$PWD/src/core/Movie.h \
        $$PWD/src/core/ItemManager.h \
        $$PWD/src/core/common.h \
    ../../src/core/CoreException.h
