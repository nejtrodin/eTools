#include "eschematic.h"
#include <QFile>
#include <QDebug>

bool ESchematic::openFile(QString filePath, Settings *settings)
{
    // clear all
    mSheets.clear();
    mSchCore.clear();

    // open new file
    QFile schematicFile(filePath);
    mPath = filePath;

    if (!schematicFile.open(QIODevice::ReadOnly)) {
        schematicFile.close();
        return false;
    }

    if (!mSchDoc.setContent(&schematicFile)) {
        return false;
    }

    bool parseResult = true;

    if (mSchDoc.isNull()) {
        qDebug() << "Error: ESchematic::openFile. Document is null";
        parseResult = false;
    }

    QDomElement rootElement;
    if (parseResult) {
        rootElement = mSchDoc.documentElement();
        if (rootElement.isNull()) {
            qDebug() << "Error: ESchematic::openFile. rootElement is null";
            parseResult = false;
        }
    }

    if (parseResult) {
        if (rootElement.tagName() != "eagle") {
            qDebug() << "Error: SchParser::parse. Document is not eagle file";
            parseResult = false;
        } else {
            QDomElement drawingElement = rootElement.firstChildElement("drawing");
            if (!drawingElement.isNull()) {
                // layers
                QDomElement layersElement = drawingElement.firstChildElement("layers");
                if (!layersElement.isNull()) {
                    if (settings != nullptr)
                        settings->layers.clear();

                    QDomElement layerElement = layersElement.firstChildElement("layer");
                    while (!layerElement.isNull()) {
                        ELayer eLayer;
                        eLayer.setDomElement(layerElement);
                        mLayers.append(eLayer);
                        if (settings != nullptr) {
                            Layer layer = eLayer.getLayer();
                            if (layer.active)
                                settings->layers.insert(layer.number, layer);
                        }

                        layerElement = layerElement.nextSiblingElement("layer");
                    }
                }

                QDomElement schematicElement = drawingElement.firstChildElement("schematic");
                if (!schematicElement.isNull()) {
                    // libraries
                    QDomElement librariesElement = schematicElement.firstChildElement("libraries");
                    if (!librariesElement.isNull()) {
                        QDomElement libraryElement = librariesElement.firstChildElement("library");
                        while (!libraryElement.isNull()) {
                            ELibrary library;
                            library.setDomElement(libraryElement);
                            mSchCore.appendLibrary(library);

                            libraryElement = libraryElement.nextSiblingElement("library");
                        }
                    }

                    // parts
                    QDomElement partsElement = schematicElement.firstChildElement("parts");
                    if (!partsElement.isNull()) {
                        QDomElement partElement = partsElement.firstChildElement("part");
                        while (!partElement.isNull()) {
                            ESchPart part;
                            part.setDomElement(partElement);
                            mSchCore.appendPart(part);

                            partElement = partElement.nextSiblingElement("part");
                        }
                    } // parts

                    // sheets
                    QDomElement sheetsElement = schematicElement.firstChildElement("sheets");
                    if (!sheetsElement.isNull()) {
                        QDomElement sheetElement = sheetsElement.firstChildElement("sheet");
                        while (!sheetElement.isNull()) {
                            ESchSheet sheet;
                            sheet.setDomElement(sheetElement);

                            mSheets.append(sheet);
                            sheetElement = sheetElement.nextSiblingElement("sheet");
                        }
                    } // sheets
                } // board
            } // drawing
        } // eagle
    }

    return parseResult;
}

void ESchematic::paint(QPainter *painter, Settings *settings, int sheetNumber)
{
    if (mSheets.size() >= sheetNumber) {
        mSheets[sheetNumber].paint(painter, settings, &mSchCore);
    }
}

QStringList ESchematic::sheetList()
{
    QStringList result;
    QVector<ESchSheet>::iterator iSheet;
    int sheetNumber = 1;
    for (iSheet = mSheets.begin(); iSheet != mSheets.end(); ++iSheet) {
        QString description = iSheet->description();
        if (description.isEmpty())
            result.append(QString("%1").arg(sheetNumber));
        else
            result.append(QString("%1: %2").arg(sheetNumber).arg(description));
        sheetNumber++;
    }
    return result;
}
