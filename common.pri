QMAKE_CXXFLAGS += -std=c++0x

INCLUDEPATH  += $$PWD/src/core/

SOURCES      += \
	$$PWD/src/core/item.cpp \
	$$PWD/src/core/folder.cpp \
	$$PWD/src/core/movie.cpp \
        $$PWD/src/core/itemmanager.cpp \
	$$PWD/src/core/tag.cpp \
	$$PWD/src/core/tagmanager.cpp
	
HEADERS      += \
	$$PWD/src/core/item.h \
    $$PWD/src/core/folder.h \
    $$PWD/src/core/movie.h \
    $$PWD/src/core/itemmanager.h \
    $$PWD/src/core/common.h \
    $$PWD/src/core/tag.h \
    $$PWD/src/core/tagmanager.h

