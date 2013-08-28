TEMPLATE = subdirs
SUBDIRS = \
        $$PWD/src/core \
        $$PWD/src/ui
	
CONFIG += ordered
SUBDIRS += \
	$$PWD/src/app
