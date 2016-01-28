#ifndef WINEXECUTOR_H
#define WINEXECUTOR_H

#include <QObject>

class PopupMessage;

class WinExecutor : public QObject
{
   Q_OBJECT
   PopupMessage *m_pPopup;
public:
   explicit WinExecutor(QObject *parent = 0);
   ~WinExecutor();
   bool getRunningProcessesList(QStringList &out_data, QString &out_error, QString split = "::");
   bool killProcessByName(QString name, QString &out_error);
   void showMessage(QString header, QString body, int seconds);
};

#endif // WINEXECUTOR_H
