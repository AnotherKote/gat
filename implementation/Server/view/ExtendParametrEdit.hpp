#ifndef EXTENDPARAMETREDIT_H
#define EXTENDPARAMETREDIT_H

#include <QDialog>

class QLabel;
class QTextEdit;
class QPushButton;

class ExtendParametrEdit : public QDialog
{
   Q_OBJECT

   QLabel *m_pCommandName;
   QLabel *m_pParameterName;
   QTextEdit *m_pParameterData;
   QPushButton *m_pAcceptButton;
   QPushButton *m_pCancelButton;

   void createWidgets();
   void resetTexts();
   void connectSignalAndSlots();
public:
   explicit ExtendParametrEdit(QWidget *parent = 0);
   void setData(QString commandName, QString parameterName, QString parameterData);
   QString getParameterData();
};

#endif // EXTENDPARAMETREDIT_H
