#ifndef XML_WRITER_H
#define XML_WRITER_H

#include <QObject>
#include <QFile>
#include <QXmlStreamWriter>
#include <QIODevice>
#include <QMessageBox>

class xml_writer : public QObject
{
    Q_OBJECT
public:
    explicit xml_writer(QObject *parent = 0);

signals:

public slots:
    void write_xml_document();
};

#endif // XML_WRITER_H
