#pragma once

#include <QObject>
#include <string>
#include <iostream>
#include <QFile>
#include <QTextStream>
#include  <utility>


class FileManager : public QObject
{
    Q_OBJECT
    //Q_PROPERTY(QString filePath_ READ filePath WRITE setFilePath)

public:
    FileManager(QString filePath);
    std::optional<QString> getLineFromFile();
    QFile file_;
    QTextStream in_;
    ~FileManager();
signals:
    //void isNightModeChanged();

private:

};


