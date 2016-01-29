# Another Kote's Software
# GAT
# Client

QT       += core gui network widgets

TARGET = GATClient
TEMPLATE = app
CONFIG += c++11

DEFINES += CLIENT

INCLUDEPATH += Client

include(Common.pri)

SOURCES += Client/main.cpp \
    Client/private/Invoker.cpp \
    Client/SystemTray.cpp \
    Client/windows/WinExecutor.cpp \
    Client/PopupMessage.cpp \
    Client/NetworkManager.cpp

HEADERS += Client/Invoker.hpp \
    Client/SystemTray.hpp \
    Client/windows/WinExecutor.hpp \
    Client/PopupMessage.hpp \
    Common/Commands/IExecutableCommand.hpp \
    Client/NetworkManager.hpp

