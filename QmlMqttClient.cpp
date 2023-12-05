#include "QmlMqttClient.h"
#include <QDebug>
#include "FileManager.h"

QmlMqttClient::QmlMqttClient(QObject *parent)
    : QMqttClient(parent)
{
}

QmlMqttSubscription* QmlMqttClient::subscribe(const QString &topic)
{
    auto sub = QMqttClient::subscribe(topic, 0);
    auto result = new QmlMqttSubscription(sub, this);
    return result;
}

void QmlMqttClient::sendDataFromFile(const QString& filePath, const QString& topic)
{


    FileManager f;
    auto ans = f.readFromFile();
    while (ans.second){
        this->publish(topic, ans.first.toUtf8());
        ++lineCounter_;
    }
    qDebug() << "total message send = " << lineCounter_;
}

QmlMqttSubscription::QmlMqttSubscription(QMqttSubscription *s, QmlMqttClient *c)
    : sub(s)
    , client(c)
{
    connect(sub, &QMqttSubscription::messageReceived, this, &QmlMqttSubscription::handleMessage);
    m_topic = sub->topic();
}

QmlMqttSubscription::~QmlMqttSubscription()
{
}

void QmlMqttSubscription::handleMessage(const QMqttMessage &qmsg)
{
    emit messageReceived(qmsg.payload());
}
