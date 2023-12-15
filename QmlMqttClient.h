#pragma once

#include <QtCore/QMap>
#include <QtMqtt/QMqttClient>
#include <QtMqtt/QMqttSubscription>
#include <QTimer>

class QmlMqttClient;

class QmlMqttSubscription : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QMqttTopicFilter topic MEMBER m_topic NOTIFY topicChanged)
public:
    QmlMqttSubscription(QMqttSubscription *s, QmlMqttClient *c);
    ~QmlMqttSubscription();

Q_SIGNALS:
    void topicChanged(QString);
    void messageReceived(const QString &msg);

public slots:
    void handleMessage(const QMqttMessage &qmsg);

private:
    Q_DISABLE_COPY(QmlMqttSubscription)
    QMqttSubscription *sub;
    QmlMqttClient *client;
    QMqttTopicFilter m_topic;
};

class QmlMqttClient : public QMqttClient
{
    Q_OBJECT
public:
    QmlMqttClient(QObject *parent = nullptr);

    Q_INVOKABLE QmlMqttSubscription *subscribe(const QString &topic);
    Q_INVOKABLE void sendDataFromFile(const QString& filePath, const QString& topic);
    Q_INVOKABLE void setUpFlow(QString hostName, uint32_t port, QString userName, QString password, QString filePath, QString topic);
    Q_INVOKABLE void startFlow();
private:
    inline static uint64_t lineCounter_ = 0;
    QTimer timer_;
    Q_DISABLE_COPY(QmlMqttClient)
    QString topic_;
    QString filePath_;
};


