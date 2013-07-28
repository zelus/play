QMAKE_CXXFLAGS += -std=c++0x

INCLUDEPATH  += $$PWD/src/core/

SOURCES      += \
        $$PWD/src/core/Item.cpp \
        $$PWD/src/core/Folder.cpp \
        $$PWD/src/core/Movie.cpp \
        $$PWD/src/core/ItemManager.cpp \
        $$PWD/src/core/Tag.cpp \
        $$PWD/src/core/TagManager.cpp
	
HEADERS      += \
        $$PWD/src/core/Item.h \
        $$PWD/src/core/Folder.h \
        $$PWD/src/core/Movie.h \
        $$PWD/src/core/ItemManager.h \
        $$PWD/src/core/common.h \
        $$PWD/src/core/Tag.h \
        $$PWD/src/core/TagManager.h

