# Another Kote's Software
# GAT
# Server

QT       += core gui network widgets

TARGET = GATServer
TEMPLATE = app
CONFIG += c++11

INCLUDEPATH += Server

SOURCES += Server/main.cpp \
           Server/view/private/MainScreen.cpp

HEADERS += Server/view/MainScreen.hpp

TRANSLATIONS += Server/main_ru.ts Server/main_en.ts

#release:DESTDIR = ../../gat_builds/release
#release:OBJECTS_DIR = ../../gat_builds/release/.obj
#release:MOC_DIR = ../../gat_builds/release/.moc

#debug:DESTDIR = ../../gat_builds/debug
#debug:OBJECTS_DIR = ../../gat_builds/debug/.obj
#Debug:MOC_DIR = ../../gat_builds/debug/.moc
