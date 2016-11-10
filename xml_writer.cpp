#include "xml_writer.h"

xml_writer::xml_writer(QObject *parent) : QObject(parent)
{
    write_xml_document();
}

void xml_writer::write_xml_document()
{
    QXmlStreamWriter xmlWriter;
    QFile file("/home/apaul/Documents/output.xml");

    if (!file.open(QIODevice::WriteOnly))
    {
        QMessageBox::warning(0, "Error!", "Error opening file");
    }
    else
    {
        xmlWriter.setDevice(&file);
        /* Writes a document start with the XML version number. */
        xmlWriter.writeStartDocument();
        xmlWriter.setAutoFormatting(true);
        xmlWriter.setAutoFormattingIndent(4);
        xmlWriter.writeStartElement("students");
        xmlWriter.writeStartElement("student");
        /*add one attribute and its value*/
        xmlWriter.writeAttribute("name","Kate");
        xmlWriter.writeTextElement("title", "Qt Home");
        /*add one attribute and its value*/
        xmlWriter.writeAttribute("surname","Johns");
        /*add one attribute and its value*/
        xmlWriter.writeAttribute("number","154455");
        /*add character data to tag student */
        xmlWriter.writeCharacters ("Student 1");
        /*close tag student  */
        xmlWriter.writeEndElement();
        /*end tag students*/
        xmlWriter.writeEndElement();
        /*end document */
        xmlWriter.writeEndDocument();
    }
}




