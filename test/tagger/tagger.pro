TEMPLATE = app
CONFIG += console
CONFIG += qt

include(../../common.pri)
LIBS = -lcppunit -lqxcppunitd

HEADERS += \
    TestTag.h

SOURCES += \
    TestTag.cpp \
    main.cpp
