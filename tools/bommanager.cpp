#include "bommanager.h"

#include "eagle/lbr/elibrary.h"
#include "eagle/sch/eschcore.h"

BomManager::BomManager(QObject *parent) : QObject(parent)
{
    schematic = nullptr;
}

void BomManager::setSchematic(ESchematic *schematic)
{
    this->schematic = schematic;
    createBomFromSchematic();
}

static bool positionCompare(const BomManager::BomEntry &first, const BomManager::BomEntry &second)
{
    int prefixResult = QString::localeAwareCompare(first.positionPrefix, second.positionPrefix);
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

QList<BomManager::BomEntry> BomManager::getBomSortedByPosition()
{
    std::sort(bomList.begin(), bomList.end(), positionCompare);

    return bomList;
}

void BomManager::createBomFromSchematic()
{
    bomList.clear();

    ESchCore schCore = schematic->getSchCore();

    foreach (ESchPart part, schCore.getParts()) {
        auto libraryName = part.library();
        auto library = schCore.getLibrary(libraryName);
        auto deviceset = library.getDeviceset(part.deviceset());
        auto device = deviceset.getDevice(part.device());

        if (!device.packageName().isEmpty()) {
            BomEntry entry;
            entry.positionPrefix = deviceset.getPrefix();
            auto positionString = part.name().remove(entry.positionPrefix, Qt::CaseSensitive);
            entry.position = positionString.toInt();

            auto entryName = formatString(deviceset.name());
            // skip part if deviceset empty (after format)
            if (entryName.isEmpty())
                continue;
            entryName.append(formatString(device.name()));

            auto value = formatString(part.value());
            if (!value.isEmpty()) {
                if (value.at(0) != ' ' && value.at(0) != '-' && entryName.back() != ' '
                    && entryName.back() != '-')
                    entryName.append(' ');
                entryName.append(value);
            }

            auto rate = part.getAttribute("RATE");
            if (!rate.isEmpty()) {
                if (rate.at(0) != '+' && rate.at(0) != '-')
                    rate.prepend("+-");
                if (rate.back() != '%')
                    rate.append('%');
                entryName.append(formatString(rate));
            }

            entry.name = entryName;

            bomList.append(entry);
        }
    }
}

QString BomManager::formatString(const QString &input)
{
    if (input.isEmpty())
        return QString();

    QString output;

    // delete string betwin and after "@", "'" , "|"
    QStringList tmpList = input.split(QRegularExpression("[@'|]"));
    for (int i = 0; i < tmpList.size(); i++) {
        if (i % 2 == 0)
            output.append(tmpList.at(i));
    }

    output.replace('_', ' ');
    output.replace("+-", "\u00B1");

    return output;
}
