#include "bomprinter.h"
#include "bomparser.h"


BomPrinter::BomPrinter(QObject *parent) :  QObject(parent) { }

void BomPrinter::openFile(QString filePath)
{
    struct PluralEntry {
        QString plural;
        bool addTypeFlag;
    };
    // TODO: move next data to global SQLite base
    QHash<QString, PluralEntry> typePluralTable;
    typePluralTable.insert("вилка",                 {"соединители", true});
    typePluralTable.insert("диод",                  {"диоды", false});
    typePluralTable.insert("дроссель",              {"индуктивности", true});
    typePluralTable.insert("конденсатор",           {"конденсаторы", false});
    typePluralTable.insert("микросхема",            {"микросхемы", false});
    typePluralTable.insert("модуль питания",        {"модули питания", false});
    typePluralTable.insert("модуль фильтра",        {"модули фильтра", false});
    typePluralTable.insert("резистор",              {"резисторы", false});
    typePluralTable.insert("резисторная сборка",    {"резисторы", true});
    typePluralTable.insert("резонатор",             {"резонаторы", false});
    typePluralTable.insert("розетка",               {"соединители", true});
    typePluralTable.insert("индикатор",             {"индикаторы", false});
    typePluralTable.insert("индуктивность",         {"индуктивности", false});
    typePluralTable.insert("соединитель",           {"соединители", true});
    typePluralTable.insert("транзистор",            {"транзисторы", false});
    typePluralTable.insert("транзисторная матрица", {"транзисторы", true});
    typePluralTable.insert("трансформатор",         {"трансформатор", false});

    ESchematic eSchematic;
    eSchematic.readFile(filePath);
    BomParser bomParser;
    bomParser.setSchematic(&eSchematic);

    typeGroups.clear();
    group = TypeGroup();
    bool groupEmpty = true;

    QString type, typePlural;
    bool addTypePrefix = false;
    foreach (BomEntry entry, bomParser.getBomSortedByPosition()) {
        addTypePrefix = false;
        typePlural = type = entry.type;
        if (typePluralTable.contains(type.toLower())) {
            PluralEntry pluralEntry = typePluralTable[type.toLower()];
            typePlural = pluralEntry.plural;
            typePlural.replace(0, 1, typePlural[0].toUpper());  // Upper first letter<
            addTypePrefix = pluralEntry.addTypeFlag;
        }

        // empty
        if (groupEmpty) {
            group.prefix = entry.prefix;
            group.type = typePlural;
            groupEmpty = false;
        }
        // equal
        if (group.prefix == entry.prefix && group.type == typePlural) {
            addEntry(entry, addTypePrefix);
        }
        // not equal
        else {
            addEntry(BomEntry(), false);
            typeGroups.append(group);
            addEntry(entry, addTypePrefix);

            group.prefix = entry.prefix;
            group.type = typePlural;
            group.lines.clear();
        }
    }

    addEntry(BomEntry(), false);
    typeGroups.append(group);


    m_richText = QString("<h3>%1</h3>").arg(filePath);
    m_richText.append(
            "<style type=\"text/css\">"
            "table {border-collapse: collapse;} th, td {border: 1px solid black; padding: 5px;}"
            "</style>"            
            "<div><center><table border=1>"
            "<tr><td>Position</td><td>Description</td><td>Qty</td><td>Comment</td></tr>"
    );
    QList<TypeGroup>::iterator groupIt = typeGroups.begin();
    while (groupIt != typeGroups.end()) {
        bool bigGroup = groupIt->lines.size() > 2;  // add header or add type prefix

        m_richText.append("<tr><td></td><td></td><td></td><td></td></tr>");
        if (bigGroup) {
            m_richText.append(QString("<tr><td></td><td>%1</td><td></td><td></td></tr>").
                              arg(groupIt->type));
        }
        foreach(ReportLine line, groupIt->lines) {
            QString desc;
            if (!bigGroup | line.showType)
                desc.append(line.type + " ");
            desc.append(line.desc);
            m_richText.append(QString("<tr><td>%1</td><td>%2</td><td>%3</td><td>%4</td></tr>").
                              arg(line.pos, desc, QString::number(line.qty), line.comment));
        }

        groupIt++;
    }
    m_richText.append("</table></center></div>");

    emit textChanged(m_richText);
}

void BomPrinter::addEntry(const BomEntry &entry, const bool &showType)
{
    static int lastPos = 0, blockQty = 0;
    static QString lastPrefix;
    static ReportLine lastLine =
            {.pos="", .desc="", .qty=0, .comment="", .type="", .showType=false};
    static ReportLine resultLine =
            {.pos="", .desc="", .qty=0, .comment="", .type="", .showType=false};

    QString desc = entry.name;
    if (!entry.specification.isEmpty()) {
        desc.append("  ");
        desc.append(entry.specification);
    }

    // first entry
    if (lastLine.pos.isEmpty()) {
        lastPos = entry.position;
        blockQty = 1;
        lastLine.qty = 1;
        lastPrefix = entry.prefix;
        lastLine.desc = desc;
        lastLine.comment = entry.note;
        lastLine.type = entry.type;
        lastLine.showType = showType;
        lastLine.pos = entry.prefix + QString::number(entry.position);
    }
    else if (entry.prefix == lastPrefix && desc == lastLine.desc && entry.type == lastLine.type) {
        if (lastPos + 1 == entry.position) {
            lastPos++;
            blockQty++;
            lastLine.qty++;
        }
        else {
            if (blockQty > 2)
                lastLine.pos.append("..." + lastPrefix + QString::number(lastPos));
            else if (blockQty > 1)
                lastLine.pos.append(", " + lastPrefix + QString::number(lastPos));
            lastLine.pos.append(", " + entry.prefix + QString::number(entry.position));

            blockQty = 1;
            lastLine.qty++;
            lastPos = entry.position;
        }
    }
    // prefix or name is not equal to the last value
    else {
        if (blockQty > 2)
            lastLine.pos.append("..." + lastPrefix + QString::number(lastPos));
        else if (blockQty > 1)
            lastLine.pos.append(", " + lastPrefix + QString::number(lastPos));
        resultLine = lastLine;
        group.lines.append(resultLine);

        lastPos = entry.position;
        blockQty = 1;
        lastLine.qty = 1;
        lastPrefix = entry.prefix;
        lastLine.desc = desc;
        lastLine.comment = entry.note;
        lastLine.type = entry.type;
        lastLine.showType = showType;
        lastLine.pos = entry.prefix;
        if (entry.position > 0)
            lastLine.pos.append(QString::number(entry.position));
    }
}
