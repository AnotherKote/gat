# Another Kote's Software
# GAT
# Common

RESOURCES += \
    resources/res.qrc

SOURCES += \
    Common/Commands/private/CmdShowMessage.cpp \
    Common/Commands/private/CmdGetProcessList.cpp \
    Common/private/ProtocolManager.cpp \
    Common/Commands/private/CmdIsProcessRunning.cpp \
    Common/Commands/private/CmdKillProcessByName.cpp \
    Common/private/CommandHelper.cpp

HEADERS += \
    Common/Commands/ICommand.hpp \
    Common/Commands/CmdShowMessage.hpp \
    Common/Commands/CmdGetProcessList.hpp \
    Common/ProtocolManager.hpp \
    Common/Commands/CmdIsProcessRunning.hpp \
    Common/Commands/CmdKillProcessByName.hpp \
    Common/CommandHelper.hpp
