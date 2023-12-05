#include "FileManager.h"

std::pair<QString, bool> FileManager::readFromFile()
{
    QFile file("/home/max/TestMqtt/input.txt");
    if(!file.open(QIODevice::ReadOnly)) {
        std::cout << file.errorString().toStdString();
    }

    QTextStream in(&file);

    bool fl = !in.atEnd();
    if (fl) {
        QString line = in.readLine();
        std::cout << line.toStdString();
        return std::pair(line, fl);
    }


    file.close();
    return {"", fl};
}

QString FileManager::filePath() const
{
    return QString::fromStdString(filePath_);
}


void FileManager::setFilePath(const QString& filePath){
    filePath_ = filePath.toStdString();
    std::cout << filePath_;
}
