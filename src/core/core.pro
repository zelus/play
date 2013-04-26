TEMPLATE = app
CONFIG += console
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++0x

SOURCES += main.cpp \
    item.cpp \
    folder.cpp \
    movie.cpp

HEADERS += \
    item.h \
    folder.h \
    movie.h
