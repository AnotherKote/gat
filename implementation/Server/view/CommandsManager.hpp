#ifndef COMMANDSMANAGER_H
#define COMMANDSMANAGER_H

#include <QDialog>

class QComboBox;
class QPushButton;
class QTextEdit;
class QListWidget;
class QLineEdit;
class QLabel;
class ExtendParametrEdit;

class CommandsManager : public QDialog
{
   Q_OBJECT

   QWidget *m_pParent;

   QComboBox *m_pAbstractCommands;

   QLabel *m_pCommandNameLabel;
   QLineEdit *m_pUserCommandName;

   QComboBox *m_pParameterName;
   QLineEdit *m_pParameterData;
   QPushButton *m_pExtendedParameterDataEdit;

   QPushButton *m_pNewCommand;
   QPushButton *m_pSaveCommand;
   QPushButton *m_pRemoveCommand;

   QListWidget *m_pUserCommandsList;

   QTextEdit *m_pCommandDescription;

   ExtendParametrEdit *m_pExtendedParameterEditDialog;

   void createWidgets();
   void connectSignalAndSlots();
   void resetTexts();
public:
   explicit CommandsManager(QWidget *parent = 0);

signals:

public slots:
   void openExtendedParameterEditDialog();
   void extendedDialogResult(int result);
   // QWidget interface
protected:
   void showEvent(QShowEvent *);
};

#endif // COMMANDSMANAGER_H
