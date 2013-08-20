TEMPLATE = app
CONFIG += console
CONFIG -= qt

include(../../include/core.pri)

SOURCES += \
	main.cpp \
	Folder.cpp \
	Movie.cpp \
	Item.cpp \
	ItemManager.cpp \
	CoreException.cpp
	


HEADERS += \
	Folder.h \
    Movie.h \
    
