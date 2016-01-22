#include "Common/ProtocolManager.hpp"
#include "Common/Commands/ICommand.hpp"

#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QDebug>

ProtocolManager::ProtocolManager(QObject *parent)
   : QObject(parent)
   , m_programNameTag ("GOT")
   , m_protocolVersionAttribute ("protocol_version")
   , m_protocolVersion ("1.0")
   , m_commandTag ("command")
   , m_commandNameAttribute ("name")
   , m_parameterTag ("parameter")
   , m_successfulAttribute ("successful")
   , m_isSuccessful ("yes")
   , m_isNotSuccessful ("no")
   , m_dataTag ("data")
{
}

QString ProtocolManager::encodeCommand(const ICommand *command)
{
   QString data;
   if(command)
   {
      QXmlStreamWriter xmlWriter(&data);
      xmlWriter.writeStartDocument();
      xmlWriter.writeStartElement(m_programNameTag);
      xmlWriter.writeAttribute(m_protocolVersionAttribute,
                               m_protocolVersion);
      xmlWriter.writeStartElement(m_commandTag);
      xmlWriter.writeAttribute(m_commandNameAttribute, command->getName());
      for (QString paramData: command->getParametersData())
      {
         xmlWriter.writeTextElement(m_parameterTag, paramData);
      }
      xmlWriter.writeEndElement();
      xmlWriter.writeEndElement();
      xmlWriter.writeEndDocument();
   }
   return data;
}

bool ProtocolManager::decodeCommand(const QString &data, QString &out_cmdName, QVector<QString> &out_params, QString &out_error)
{
   bool ret = true;
   QXmlStreamReader xmlReader(data);
   while(!xmlReader.atEnd() && !xmlReader.hasError() && ret)
   {
      QXmlStreamReader::TokenType token = xmlReader.readNext();
      switch(token)
      {
      case QXmlStreamReader::StartElement:
         if(xmlReader.name() == m_programNameTag)
         {
            QXmlStreamAttributes attributes = xmlReader.attributes();
            if(attributes.value(m_protocolVersionAttribute) != m_protocolVersion)
            {
               out_error = tr("Protocol versions is not equal. Client %1; Server %2").arg(m_protocolVersion).arg(attributes.value(m_protocolVersionAttribute).toString());
               ret = false;
               break;
            };
         }
         else if (xmlReader.name() == m_commandTag)
         {
            QXmlStreamAttributes attributes = xmlReader.attributes();
            out_cmdName = attributes.value(m_commandNameAttribute).toString();
         }
         else if (xmlReader.name() == m_parameterTag)
         {
            out_params.append(xmlReader.readElementText());
         }
      break;
      default:
      break;
      }
   }
   if(xmlReader.hasError())
   {
      out_error = xmlReader.errorString();
      ret = false;
   }

   return ret;
}

QString ProtocolManager::encodeResult(QString cmdName, const QStringList result, bool successful)
{
   QString data;
   QXmlStreamWriter xmlWriter(&data);
   xmlWriter.writeStartDocument();
   xmlWriter.writeStartElement(m_programNameTag);
   xmlWriter.writeAttribute(m_protocolVersionAttribute,
                            m_protocolVersion);
   xmlWriter.writeStartElement(m_commandTag);
   xmlWriter.writeAttribute(m_commandNameAttribute, cmdName);
   xmlWriter.writeAttribute(m_successfulAttribute,
                            (successful) ? m_isSuccessful : m_isNotSuccessful);
   for (QString resultElement: result)
   {
      xmlWriter.writeTextElement(m_dataTag, resultElement);
   }
   xmlWriter.writeEndElement();
   xmlWriter.writeEndElement();
   xmlWriter.writeEndDocument();
   qDebug() << "encoded result: " << data;
   return data;
}

bool ProtocolManager::decodeResult(const QString &data,
                                   QString &out_cmdName,
                                   QStringList &out_result,
                                   bool &out_successful,
                                   QString &out_error)
{
   bool ret = true;
   QXmlStreamReader xmlReader(data);
   while(!xmlReader.atEnd() && !xmlReader.hasError() && ret)
   {
      QXmlStreamReader::TokenType token = xmlReader.readNext();
      switch(token)
      {
      case QXmlStreamReader::StartElement:
         if(xmlReader.name() == m_programNameTag)
         {
            QXmlStreamAttributes attributes = xmlReader.attributes();
            if(attributes.value(m_protocolVersionAttribute) != m_protocolVersion)
            {
               out_error = tr("Protocol versions is not equal. Client %1; Server %2").arg(m_protocolVersion).arg(attributes.value(m_protocolVersionAttribute).toString());
               ret = false;
               break;
            };
         }
         else if (xmlReader.name() == m_commandTag)
         {
            QXmlStreamAttributes attributes = xmlReader.attributes();
            out_cmdName = attributes.value(m_commandNameAttribute).toString();
            if(attributes.value(m_successfulAttribute).toString() == m_isSuccessful)
            {
               out_successful = true;
            } else if(attributes.value(m_successfulAttribute).toString() == m_isNotSuccessful)
            {
               out_successful = false;
            } else
            {
               out_error = tr("Error while parsing successful attribute.");
               ret = false;
            }
         }
         else if (xmlReader.name() == m_dataTag)
         {
            out_result.append(xmlReader.readElementText());
         }
      break;
      default:
      break;
      }
   }
   if(xmlReader.hasError())
   {
      out_error = xmlReader.errorString();
      ret = false;
   }

   return ret;
}

