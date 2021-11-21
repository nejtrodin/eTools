#include "bomparser.h"

#include "eagle/lbr/elibrary.h"
#include "eagle/sch/eschcore.h"

BomParser::BomParser(QObject *parent) : QObject(parent)
{
    schematic = nullptr;
}

void BomParser::setSchematic(ESchematic *schematic)
{
    this->schematic = schematic;
    createBomFromSchematic();
}

static bool positionCompare(const BomEntry &first, const BomEntry &second)
{
    int prefixResult = QString::localeAwareCompare(first.prefix, second.prefix);
    if (prefixResult < 0) {
        return true;
    } else if (prefixResult > 0) {
        return false;
    } else {
        if (first.position < second.position)
            return true;
        else
            return false;
    }
}

QList<BomEntry> BomParser::getBomSortedByPosition()
{
    std::sort(bomList.begin(), bomList.end(), positionCompare);

    return bomList;
}

void BomParser::createBomFromSchematic()
{
    bomList.clear();

    ESchCore schCore = schematic->getSchCore();

    foreach (ESchPart part, schCore.getParts()) {
        ELibrary library = schCore.getLibrary(part.library(), part.libraryUrn());
        EDeviceset deviceset = library.getDeviceset(part.deviceset());
        EDevice device = deviceset.getDevice(part.device());

        if (!device.packageName().isEmpty()) {
            BomEntry entry;

            // get type
            auto minIndex = [](int index1, int index2) {
                if (index1 < 0) return index2;
                else if (index2 < 0) return index1;
                else if (index1 < index2) return index1;
                else return index2;
            };
            QString partType = deviceset.getDescription();
            int endOfPart = partType.indexOf("<br>");
            endOfPart = minIndex(endOfPart, partType.indexOf('.'));
            endOfPart = minIndex(endOfPart, partType.indexOf(','));
            endOfPart = minIndex(endOfPart, partType.indexOf(';'));
            if (endOfPart >= 0)
                partType = partType.left(endOfPart);
            entry.type = partType;

            entry.prefix = deviceset.getPrefix();
            auto positionString = part.name().remove(entry.prefix, Qt::CaseSensitive);
            entry.position = positionString.toInt();

            QString entryName = formatString(deviceset.name());
            // skip part if deviceset empty (after format)
            if (entryName.isEmpty())
                continue;
            entryName.append(formatString(device.name()));

            if (deviceset.hasUservalue()) {
                QString value = formatString(part.value());
                if (!value.isEmpty()) {
                    if (value.at(0) != ' ' && value.at(0) != '-' && entryName.back() != ' '
                        && entryName.back() != '-')
                        entryName.append(' ');
                    entryName.append(value);
                }
            }

            QString rate = part.getAttribute("RATE");
            if (rate.isEmpty())
                rate = device.getAttribute("", "RATE");
            if (!rate.isEmpty()) {
                if (rate.at(0) != '+' && rate.at(0) != '-')
                    rate.prepend("+-");
                if (rate.back() != '%')
                    rate.append('%');
                entryName.append(formatString(rate));
            }

            QString suffix = part.getAttribute("SUFFIX");
            if (suffix.isEmpty())
                suffix = device.getAttribute("", "SUFFIX");
            if (!suffix.isEmpty()) {
                suffix = suffix.trimmed();
                if (suffix.right(2) == "ТУ")
                    entryName.append("  ");
                entryName.append(formatString(suffix));
            }

            entry.name = entryName;

            QString specification = part.getAttribute("SPEC");
            if (specification.isEmpty())
                specification = device.getAttribute("", "SPEC");
            entry.specification = specification.trimmed();

            bomList.append(entry);
        }
    }
}


QString BomParser::formatString(const QString &input)
{
    static const QHash<char, QString> superscriptSymbols{
        {'0', "\u2070"}, {'1', "\u00B9"}, {'2', "\u00B2"}, {'3', "\u00B3"}, {'4', "\u2074"},
        {'5', "\u2075"}, {'6', "\u2076"}, {'7', "\u2077"}, {'8', "\u2078"}, {'9', "\u2079"},
        {'+', "\u207A"}, {'-', "\u207B"}, {'=', "\u207C"}
    };
    static const QHash<char, QString> subscriptSymbols{
        {'0', "\u2080"}, {'1', "\u2081"}, {'2', "\u2082"}, {'3', "\u2083"}, {'4', "\u2084"},
        {'5', "\u2085"}, {'6', "\u2086"}, {'7', "\u2087"}, {'8', "\u2088"}, {'9', "\u2089"},
        {'+', "\u208A"}, {'-', "\u208B"}, {'=', "\u208C"}
    };

    enum {
        NormalMode,
        SupSingleMode,
        SupMode,
        SubSingleMode,
        SubMode,
        CutMode
    } textMode;

    if (input.isEmpty())
        return QString();

    QString output;

    QString::const_iterator inputIt = input.begin();
    textMode = NormalMode;
    while (inputIt != input.end()) {
        if ((*inputIt == '@') | (*inputIt == '\'') | (*inputIt == '|')) {
            if (textMode == NormalMode)
                textMode = CutMode;
            else if (textMode == CutMode)
                textMode = NormalMode;
            if (++inputIt == input.end())
                break;
        }

        if (textMode != CutMode) {
            if (*inputIt == '^') {
                textMode = SupSingleMode;
                if (inputIt != input.begin() && *(inputIt - 1) == '(') {
                    textMode = SupMode;
                    output.chop(1);
                }
                if (++inputIt == input.end())
                    break;
                if (*inputIt == '(') {
                    textMode = SupMode;
                    if (++inputIt == input.end())
                        break;
                }
            }
            else if (*inputIt == '_') {
//                textMode = SubSingleMode;
                if (inputIt != input.begin() && *(inputIt - 1) == '(') {
                    textMode = SubMode;
                    if (++inputIt == input.end())
                        break;
                }
                else if ((inputIt + 1) != input.end() && *(inputIt + 1) == '(') {
                    textMode = SubMode;
                    inputIt += 2;
                    if (inputIt == input.end())
                        break;
                }
            }
            else if (*inputIt == ')' && (textMode == SupMode || textMode == SubMode)) {
                textMode = NormalMode;
                if (++inputIt == input.end())
                    break;
            }
        }

        if (textMode == SupMode || textMode == SupSingleMode) {
            output.append(superscriptSymbols.value(inputIt->toLatin1(), QString(*inputIt)));
        }
        else if (textMode == SubMode) {
            output.append(subscriptSymbols.value(inputIt->toLatin1(), QString(*inputIt)));
        }
        else if (textMode == NormalMode /*|| textMode == SubSingleMode*/) {
            output.append(*inputIt);
        }

        inputIt++;
    }


    output.replace('_', ' ');
    output.replace("+-", "\u00B1");

    return output;
}
