#ifndef PROTOCOLMANAGER_H
#define PROTOCOLMANAGER_H

#include <QObject>

class ICommand;

class ProtocolManager : public QObject
{
   Q_OBJECT

   const QString m_programNameTag;
   const QString m_protocolVersionAttribute;
   const QString m_protocolVersion;
   const QString m_commandTag;
   const QString m_commandNameAttribute;
   const QString m_parameterTag;
   const QString m_successfulAttribute;
   const QString m_isSuccessful;
   const QString m_isNotSuccessful;
   const QString m_dataTag;

public:
   explicit ProtocolManager(QObject *parent = 0);
   QString encodeCommand(const ICommand *command);
   bool decodeCommand(const QString &data,
               QString &out_cmdName,
               QVector<QString> &out_params,
               QString &out_error);

   QString encodeResult(QString cmdName, const QStringList result, bool successful);
   bool decodeResult(const QString &data,
                     QString &out_cmdName,
                     QStringList &out_result,
                     bool &out_successful,
                     QString &out_error);
signals:

public slots:
};

#endif // PROTOCOLMANAGER_H
