#include "efileinfo.h"

#include <QDir>
#include <QFile>
#include <QXmlStreamReader>

EFileInfo::EFileInfo(QObject *parent) : QObject(parent) { }

void EFileInfo::checkFile(QString path)
{
    QUrl url(path);
    if (url.isValid() && url.isLocalFile())
        checkFilePath(QDir::toNativeSeparators(url.toLocalFile()));
    else
        checkFilePath(QDir::toNativeSeparators(path));
}

void EFileInfo::checkFilePath(QString path)
{
    filePath = path;
    type = NotFound;
    report = tr("File: %1").arg(filePath);

    if (!filePath.isEmpty()) {
        if (QFile::exists(filePath)) {
            // check xml file
            QFile xmlFile(filePath);
            if (xmlFile.open(QIODevice::ReadOnly)) {
                QXmlStreamReader xmlReader;
                xmlReader.setDevice(&xmlFile);
                type = Other;

                if (xmlReader.readNextStartElement() && xmlReader.name() == QLatin1String("eagle")
                    && xmlReader.attributes().hasAttribute(QLatin1String("version"))) {
                    report.append(
                            tr("\nEagle Cad file. Version: %1.")
                                    .arg(xmlReader.attributes().value(QLatin1String("version"))));

                    if (xmlReader.readNextStartElement()
                        && xmlReader.name() == QLatin1String("drawing")) {
                        // find first identificator
                        while (xmlReader.readNextStartElement()) {
                            if (xmlReader.name() == QLatin1String("schematic")) {
                                type = Schematic;
                                break;
                            } else if (xmlReader.name() == QLatin1String("board")) {
                                type = Board;
                                break;
                            } else if (xmlReader.name() == QLatin1String("library")) {
                                type = Library;
                                break;
                            } else {
                                xmlReader.skipCurrentElement();
                            }
                        }
                    } // if tag <drawing>
                } // if tag <eagle>
                else {
                    report.append(tr(" is not Eagle Cad"));
                }

                xmlFile.close();
            } // if file opened
            else {
                report.append(tr(" is not opened"));
            }
        } // if file exists
        else {
            report.append(tr(" is not exists"));
        }
    }
}
