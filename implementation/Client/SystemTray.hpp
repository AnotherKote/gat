#ifndef SYSTEMTRAY_H
#define SYSTEMTRAY_H

#include <QLabel>

class QSystemTrayIcon;
class QMenu;

class SystemTray : public QLabel
{
   Q_OBJECT

   QSystemTrayIcon *m_pSystemTray;
   QMenu *m_pSystemTrayMenu;
public:
   explicit SystemTray(QWidget *parent = 0);
};

#endif // SYSTEMTRAY_H
