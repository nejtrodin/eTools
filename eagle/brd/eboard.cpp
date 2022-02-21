#include "eboard.h"

bool EBoard::readFile(QString filePath)
{
    // clear all
    m_libraries.clear();
    eElements.clear();
    eSignals.clear();

    QFile boardFile(filePath);
    m_path = filePath;
    if (!boardFile.open(QIODevice::ReadOnly)) {
        boardFile.close();
        return false;
    }
    if (!m_boardDoc.setContent(&boardFile)) {
        boardFile.close();
        return false;
    }
    boardFile.close();

    bool parceResult = true;

    if (m_boardDoc.isNull()) {
        qDebug() << "Error: EBoard::readFile. Document is null";
        parceResult = false;
    }

    QDomElement rootElement;
    if (parceResult) {
        rootElement = m_boardDoc.documentElement();
        if (rootElement.isNull()) {
            qDebug() << "Error: EBoard::readFile. rootElement is null";
            parceResult = false;
        }
    }

    if (parceResult) {
        if (rootElement.tagName() != "eagle") {
            qDebug() << "Error: EBoard::readFile. Document is not eagle file";
            parceResult = false;
        } else {
            QDomElement drawingElement = rootElement.firstChildElement("drawing");
            if (!drawingElement.isNull()) {
                QDomElement boardElement = drawingElement.firstChildElement("board");
                if (!boardElement.isNull()) {
                    QDomElement designrulesElement = boardElement.firstChildElement("designrules");
                    if (!designrulesElement.isNull()) {
                        EDesignRules *designrules = EDesignRules::instance();
                        designrules->parse(designrulesElement);
                    }

                    QDomElement plainElement = boardElement.firstChildElement("plain");
                    if (!plainElement.isNull()) {
                        EBrdPlain plain;
                        plain.setDomElement(plainElement);
                        setPlain(plain);
                    }

                    QDomElement librariesElement = boardElement.firstChildElement("libraries");
                    if (!librariesElement.isNull()) {
                        QDomElement libraryElement = librariesElement.firstChildElement("library");
                        while (!libraryElement.isNull()) {
                            ELibrary library;
                            library.setDomElement(libraryElement);
                            m_libraries.insert(library.name(), library);

                            libraryElement = libraryElement.nextSiblingElement("library");
                        }
                    }

                    QDomElement elementsElement = boardElement.firstChildElement("elements");
                    if (!elementsElement.isNull()) {
                        QDomElement elementElement = elementsElement.firstChildElement("element");
                        while (!elementElement.isNull()) {
                            EElement element;
                            element.setDomElement(elementElement);
                            eElements.append(element);

                            elementElement = elementElement.nextSiblingElement("element");
                        }

                    } // elements

                    QDomElement signalsElement = boardElement.firstChildElement("signals");
                    if (!signalsElement.isNull()) {
                        QDomElement signalElement = signalsElement.firstChildElement("signal");
                        while (!signalElement.isNull()) {
                            ESignal signal;
                            signal.setDomElement(signalElement);
                            eSignals.append(signal);
                            signalElement = signalElement.nextSiblingElement("signal");
                        }
                    } // signals
                } // board
            } // drawing
        } // eagle
    }

    return parceResult;
}

void EBoard::appendElement(EElement eElement)
{
    eElements.append(eElement);
}

void EBoard::appendSignal(ESignal eSignal)
{
    eSignals.append(eSignal);
}

void EBoard::setPlain(EBrdPlain ePlain)
{
    this->ePlain = ePlain;
}

ELibrary EBoard::getLibrary(QString libraryName)
{
    if (m_libraries.contains(libraryName)) {
        return m_libraries.value(libraryName);
    } else {
        return ELibrary();
    }
}
