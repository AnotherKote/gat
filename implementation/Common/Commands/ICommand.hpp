#ifndef ICOMMAND_HPP
#define ICOMMAND_HPP

#include <QString>
#include <QVector>
#include <QObject>
#include <QDebug>

class ICommand : public QObject
{
   Q_OBJECT

//   static const QString commandOpenTag = "<command name=%1>"; // /* id=%2*/
//   static const QString commandCloseTag = "</command>";
//   static const QString paramTag = "<parameter>%1</parameter>";

protected:
   const QString m_name;
   const QVector<QString> m_parameterNames;
   QVector<QString> m_parameterData;
   QString m_description;

public:
   explicit ICommand(const QString name,
                     const QVector<QString> parameterNames,
                     QObject *parent = 0)
      : QObject(parent)
      , m_name(name)
      , m_parameterNames(parameterNames)
   {
   }

   bool setParameters(QVector<QString> params)
   {
      bool ret = false;
      if(params.size() != m_parameterNames.size())
      {
         qWarning() << "vectors size is not equal! expect:" << m_parameterNames.size() << " received:" << params.size();
      } else {
         m_parameterData = params;
         ret = true;
      }
      return ret;
   }

   const QString &getName() const { return m_name; }
   const QVector<QString> &getParameterNames() const { return m_parameterNames; }
   const QVector<QString> &getParametersData() const { return m_parameterData; }
   const QString &getDescription() const { return m_description; }

};
#endif // ICOMMAND_HPP
