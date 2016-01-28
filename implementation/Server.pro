# Another Kote's Software
# GAT
# Server

QT       += core gui network widgets

TARGET = GATServer
TEMPLATE = app
CONFIG += c++11

INCLUDEPATH += Server

SOURCES += \
    Server/main.cpp \
    Server/view/private/MainScreen.cpp \
    Server/view/private/CommandsManager.cpp \
    Server/view/private/ExtendParametrEdit.cpp \
    Common/Commands/private/CmdShowMessage.cpp \
    Common/Commands/private/CmdGetProcessList.cpp \
    Common/gen/private/GEN_CommandFactory.cpp \
    Common/gen/private/GEN_CommandsHelper.cpp \
    Server/model/private/Model.cpp \
    Server/controller/private/Controller.cpp \
    Server/controller/private/Server.cpp \
    Common/private/ProtocolManager.cpp \
    Common/Commands/private/CmdIsProcessRunning.cpp \
    Common/Commands/private/CmdKillProcessByName.cpp

HEADERS += \
    Server/view/MainScreen.hpp \
    Server/view/CommandsManager.hpp \
    Server/view/ExtendParametrEdit.hpp \
    Common/Commands/ICommand.hpp \
    Common/Commands/CmdShowMessage.hpp \
    Common/Commands/CmdGetProcessList.hpp \
    Common/gen/GEN_CommandFactory.hpp \
    Common/gen/GEN_CommandsHelper.hpp \
    Server/model/Model.hpp \
    Server/model/ICommandsModel.hpp \
    Server/model/IClientsModel.hpp \
    Server/controller/Controller.hpp \
    Server/controller/private/Server.hpp \
    Common/ProtocolManager.hpp \
    Server/model/CommandResult.hpp \
    Common/Commands/CmdIsProcessRunning.hpp \
    Common/Commands/CmdKillProcessByName.hpp

RESOURCES += \
    resources/res.qrc
