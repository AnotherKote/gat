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
class ICommandsModel;
class QSettings;

class CommandsManager : public QDialog
{
   Q_OBJECT

   QWidget *m_pParent;

   QComboBox *m_pAbstractCommands;

   QLabel *m_pCommandNameLabel;
   QLineEdit *m_pUserCommandName;

   QComboBox *m_pParameterName;
   QLineEdit *m_pParameterData;
   QStringList m_pParameterDataList;
//   int m_currentParameterDataIndex;
   QPushButton *m_pExtendedParameterDataEdit;

   QPushButton *m_pNewCommand;
   QPushButton *m_pSaveCommand;
   QPushButton *m_pRemoveCommand;

   QListWidget *m_pUserCommandsList;

   QTextEdit *m_pCommandDescription;

   ExtendParametrEdit *m_pExtendedParameterEditDialog;

   ICommandsModel *m_pCmdModel;

   QSettings *m_pSettings;

   const QString m_folderName;
   const QString m_cmdAbstractName;

   void createWidgets();
   void connectSignalAndSlots();
   void resetTexts();
   void saveSettings();
   void loadSettings();
public:
   explicit CommandsManager(ICommandsModel *cmdModel, QWidget *parent = 0);

signals:

public slots:
   void openExtendedParameterEditDialog();
   void extendedDialogResult(int result);
   void refillAbstractCommandsList();
   void refillParameterNamesList(QString = "");
   void refillCommandDescription(QString currentAbstractCommand = "");
   void createParameterDataList(QString);
   void fillParameterDataList(QStringList dataList);
   void manageParameterData(int index);
   void saveParameterData();
   void refillUserCommandsList();
   void saveCommand();
   void message(QString message);
   void loadCommand(QString userCmdName);
   void removeCommand(QString userCmdName);
   void clearAll();
   // QWidget interface
protected:
   void showEvent(QShowEvent *);
};

#endif // COMMANDSMANAGER_H
