#include "QmlMqttClient.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QLoggingCategory>
#include "FileManager.h"
#include "Logger.h"
int main(int argc, char *argv[])
{

    Logger::init();

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    //FileManager f;
    //qmlRegisterType<FileManager>("FileManager", 1, 0, "FileManager  ");
    qmlRegisterType<QmlMqttClient>("MqttClient", 1, 0, "MqttClient");
    qmlRegisterUncreatableType<QmlMqttSubscription>("MqttClient", 1, 0, "MqttSubscription", QLatin1String("Subscriptions are read-only"));

    engine.load(QUrl(QStringLiteral("qrc:/Main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
