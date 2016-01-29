# Another Kote's Software
# GAT
# Server

QT       += core gui network widgets

TARGET = GATServer
TEMPLATE = app
CONFIG += c++11

INCLUDEPATH += Server

include(Common.pri)

SOURCES += \
    Server/main.cpp \
    Server/view/private/MainScreen.cpp \
    Server/view/private/CommandsManager.cpp \
    Server/view/private/ExtendParametrEdit.cpp \
    Server/model/private/Model.cpp \
    Server/controller/private/Controller.cpp \
    Server/controller/private/Server.cpp

HEADERS += \
    Server/view/MainScreen.hpp \
    Server/view/CommandsManager.hpp \
    Server/view/ExtendParametrEdit.hpp \
    Server/model/Model.hpp \
    Server/model/ICommandsModel.hpp \
    Server/model/IClientsModel.hpp \
    Server/controller/Controller.hpp \
    Server/controller/private/Server.hpp \
    Server/model/CommandResult.hpp
