#ifndef EFILEINFO_H
#define EFILEINFO_H

#include <QObject>
#include <QUrl>

class EFileInfo : public QObject
{
    Q_OBJECT
public:
    explicit EFileInfo(QObject *parent = nullptr);

    enum FileType { NotFound, Board, Schematic, Library, Other };
    Q_ENUM(FileType)

    Q_INVOKABLE void checkFile(QString path);
    void checkFilePath(QString path);
    Q_INVOKABLE FileType getType() { return type; }
    Q_INVOKABLE QString getInfo() { return report; }
    Q_INVOKABLE QString getFilePath() { return filePath; }

private:
    QString filePath;
    QString report;
    FileType type;
};

#endif // EFILEINFO_H
