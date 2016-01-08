#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include <QMainWindow>

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

   void createWidgets();
   void connectSignalAndSlots();
   void resetTexts();

public:
   explicit MainScreen(QWidget *parent = 0);
   bool event(QEvent *event);

public slots:

   void buttonManageCommandsPressed();
};

#endif // MAINSCREEN_H
