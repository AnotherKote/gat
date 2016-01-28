# Another Kote's Software
# GAT
# Client

QT       += core gui network widgets

TARGET = GATClient
TEMPLATE = app
CONFIG += c++11

DEFINES += CLIENT

INCLUDEPATH += Client

SOURCES += \
    Client/main.cpp \
    Client/private/Invoker.cpp \
    Client/SystemTray.cpp \
    Client/windows/WinExecutor.cpp \
    Client/PopupMessage.cpp \
    Common/Commands/private/CmdGetProcessList.cpp \
    Common/Commands/private/CmdShowMessage.cpp \
    Common/gen/private/GEN_CommandsHelper.cpp \
    Common/gen/private/GEN_CommandFactory.cpp \
    Client/NetworkManager.cpp \
    Common/private/ProtocolManager.cpp \
    Common/Commands/private/CmdIsProcessRunning.cpp \
    Common/Commands/private/CmdKillProcessByName.cpp

HEADERS += \
    Client/Invoker.hpp \
    Client/SystemTray.hpp \
    Client/windows/WinExecutor.hpp \
    Client/PopupMessage.hpp \
    Common/Commands/IExecutableCommand.hpp \
    Common/Commands/CmdGetProcessList.hpp \
    Common/Commands/CmdShowMessage.hpp \
    Common/Commands/ICommand.hpp \
    Common/gen/GEN_CommandFactory.hpp \
    Common/gen/GEN_CommandsHelper.hpp \
    Client/NetworkManager.hpp \
    Common/ProtocolManager.hpp \
    Common/Commands/CmdIsProcessRunning.hpp \
    Common/Commands/CmdKillProcessByName.hpp

RESOURCES += \
    resources/res.qrc
