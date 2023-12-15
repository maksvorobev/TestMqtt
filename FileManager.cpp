#include "FileManager.h"
#include <QDebug>
#include <optional>

FileManager::FileManager(QString filePath): file_(filePath), in_(&file_)
{
    if(!file_.open(QIODevice::ReadOnly)) {
        qCritical() << file_.errorString();
    }
    else {
        qInfo() << "input data file successfully openned !!!";
    }
}

std::optional<QString> FileManager::getLineFromFile()
{
    /*
     * Read file line-by-line and return next line.
     */

    bool fl = in_.atEnd();
    if (!fl){
        return in_.readLine();
    }

    return {};
}

FileManager::~FileManager()
{
    file_.close();
}





