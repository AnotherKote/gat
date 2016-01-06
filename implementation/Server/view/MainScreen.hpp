#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include <QMainWindow>

class QComboBox;
class QPushButton;
class QTranslator;

class MainScreen : public QMainWindow
{
   Q_OBJECT

   QComboBox *m_pUserCommands;
   QPushButton *m_pFire;
   QPushButton *m_pManageCommands;
   QTranslator *m_pTranslator;

   void createWidgets();
public:
   explicit MainScreen(QWidget *parent = 0);
   void setText();

   void setTranslator(QTranslator *translator);
public slots:
   void translateToEnglish();
   void translateToRussian();
};

#endif // MAINSCREEN_H
