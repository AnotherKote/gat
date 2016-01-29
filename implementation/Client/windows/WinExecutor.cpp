#include "windows\WinExecutor.hpp"
#include "PopupMessage.hpp"

#include <QStringList>

#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>

#include <QDebug>

WinExecutor::WinExecutor(QObject *parent)
   : QObject(parent)
   , m_pPopup(nullptr)
{
}

WinExecutor::~WinExecutor()
{
   if(m_pPopup)
      m_pPopup->deleteLater();
}

bool WinExecutor::getRunningProcessesList(QStringList &out_data, QString &out_error, QString split)
{
   HANDLE hProcessSnap;
   PROCESSENTRY32 pe32;

   out_data.clear();
   out_error.clear();

   // Take a snapshot of all processes in the system.
   hProcessSnap = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );
   if( hProcessSnap == INVALID_HANDLE_VALUE )
   {
      out_error = "CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 ) returned INVALID_HANDLE_VALUE";
      return false;
   }

   // Set the size of the structure before using it.
   pe32.dwSize = sizeof( PROCESSENTRY32 );

   // Retrieve information about the first process,
   // and exit if unsuccessful
   if( !Process32First( hProcessSnap, &pe32 ) )
   {
      out_error = "Process32First( hProcessSnap, &pe32 ) failed";
      CloseHandle( hProcessSnap );          // clean the snapshot object
      return false;
   }

   // Now walk the snapshot of processes, and
   // display information about each process in turn
   do
   {
      out_data << QString::fromWCharArray(pe32.szExeFile) + split + QString::number(pe32.th32ProcessID);
//      out_name.append();
//      out_pids.append(pe32.th32ProcessID);

   } while( Process32Next( hProcessSnap, &pe32 ) );

   CloseHandle( hProcessSnap );
   return true;
}

bool WinExecutor::killProcessByName(QString name, QString &out_error)
{
   HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, 0);
   PROCESSENTRY32 pEntry;
   pEntry.dwSize = sizeof (pEntry);
   BOOL hRes = Process32First(hSnapShot, &pEntry);
   while (hRes)
   {
      if (QString::fromWCharArray(pEntry.szExeFile).compare(name, Qt::CaseInsensitive) == 0)
      {
         HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, 0,
                                       (DWORD) pEntry.th32ProcessID);
         if (hProcess != NULL)
         {
            TerminateProcess(hProcess, 9);
            CloseHandle(hProcess);
            return true;
         }
      }
      hRes = Process32Next(hSnapShot, &pEntry);
   }
   CloseHandle(hSnapShot);
   out_error = "No process with name \"" + name + "\" was found.";
   return false;
}

void WinExecutor::showMessage(QString header, QString body, int seconds)
{
   if(!m_pPopup)
      m_pPopup = new PopupMessage;
   m_pPopup->setHeader(header);
   m_pPopup->setText(body);
   m_pPopup->setTime(seconds);
   m_pPopup->showFullScreen();
}
