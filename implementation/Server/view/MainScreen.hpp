#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include <QMainWindow>

class ICommandsModel;
class IClientsModel;
class QComboBox;
class QPushButton;
class QListWidget;
class CommandsManager;
class QLabel;
class QTextEdit;

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
   QLabel *m_pResultedCommandName;
   QTextEdit *m_pResult;

   void createWidgets();
   void connectSignalAndSlots();
   void resetTexts();

public:
   explicit MainScreen(ICommandsModel *model, IClientsModel *clientsModel, QWidget *parent = 0);
   bool event(QEvent *event);

private slots:
   void currentSelectedClientChanged(QString clientName);

public slots:
   void fillUserCommandsList();
   void refillClientsList();
   void buttonManageCommandsPressed();
   void slotFire();
   void clientResultChanged(QString clientName);
signals:
   void fireCommand(QString userCmdName, QStringList clients);
};

#endif // MAINSCREEN_H
