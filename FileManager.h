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
    Q_PROPERTY(QString filePath_ READ filePath WRITE setFilePath)

public:
    std::string filePath_;
    std::pair<QString, bool> readFromFile();

    //bool isNightMode() const;
    //void setIsNightMode(bool isNightMode);

    QString filePath() const;
    void setFilePath(const QString& filePath);

signals:
    //void isNightModeChanged();

private:
    //bool m_isNightMode = false;
};


