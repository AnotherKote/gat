#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include <QMainWindow>

class ICommandsModel;
class IClientsModel;
class QComboBox;
class QPushButton;
class QListWidget;
class CommandsManager;

class MainScreen : public QMainWindow
{
   Q_OBJECT

   QComboBox *m_pUserCommands;
   QPushButton *m_pFire;
   QPushButton *m_pManageCommands;
   QListWidget *m_pClientsList;
   CommandsManager *m_pCommandsManager;
   ICommandsModel *m_pCmdModel;
   IClientsModel *m_pClientsModel;

   void createWidgets();
   void connectSignalAndSlots();
   void resetTexts();

public:
   explicit MainScreen(ICommandsModel *model, IClientsModel *clientsModel, QWidget *parent = 0);
   bool event(QEvent *event);
public slots:
   void fillUserCommandsList();
   void refillClientsList();
   void buttonManageCommandsPressed();
};

#endif // MAINSCREEN_H
