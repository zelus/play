TEMPLATE = app
CONFIG += console
CONFIG += qt

include(../../common.pri)
LIBS = -lcppunit -lqxcppunitd

HEADERS += \
    TestTag.h \
    TestTagManager.h \
    MockTag.h \
    MockTagManager.h

SOURCES += \
    TestTag.cpp \
    main.cpp \
    TestTagManager.cpp \
    MockTag.cpp \
    MockTagManager.cpp
