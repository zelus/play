TEMPLATE = app
CONFIG += console
CONFIG += qt

include(../../common.pri)

LIBS = -lcppunit -lqxcppunitd

SOURCES += main.cpp \
    test_itemmanager.cpp \
    test_item.cpp \
    test_movie.cpp \
    test_folder.cpp \
    mock_item.cpp

HEADERS += \
    test_itemmanager.h \
    test_item.h \
    test_movie.h \
    test_folder.h \
    mock_item.h
