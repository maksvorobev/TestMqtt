#include "QmlMqttClient.h"
#include <QDebug>
#include "FileManager.h"
#include <QMessageBox>
#include <QMqttClient>

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


    FileManager f(filePath);
    auto ans = f.getLineFromFile();
    while (ans){
        qDebug() << ans.value().toUtf8();
        /*
        auto conn = std::make_shared<QMetaObject::Connection>();
        *conn = connect(&timer_, &QTimer::timeout, this, [this, conn, &filePath, &topic, &ans, &f](){

            QObject::disconnect(*conn);
            timer_.stop();



        });
        */
        this->publish(topic, ans.value().toUtf8());
        ans = f.getLineFromFile();
        ++lineCounter_;

        //timer_.start(2000);
    }
    qDebug() << "total message send = " << lineCounter_;
}

void QmlMqttClient::setUpFlow(QString hostName, uint32_t port, QString userName, QString password, QString filePath, QString topic)
{
    topic_ = topic;
    filePath_ = filePath;
    setHostname(std::move(hostName));
    setPort(port);
    setUsername(std::move(userName));
    setPassword(std::move(password));

}

void QmlMqttClient::startFlow()
{
    qDebug() << "Start flow!";

    auto conn = std::make_shared<QMetaObject::Connection>();
    auto connectionFunc = [this, conn](){
        QObject::disconnect(*conn);
        qDebug() << "Connection Established !!!";

        publish(QMqttTopicName(topic_), "Hi i'm from Qt !!!");

        sendDataFromFile(filePath_, topic_);

    };
    *conn = connect(this, &QmlMqttClient::connected, this, connectionFunc);

    auto conn2 = std::make_shared<QMetaObject::Connection>();
    *conn2 = connect(this, &QmlMqttClient::disconnected, this, [conn2](){
        QObject::disconnect(*conn2);
        qDebug() << "Connection enterupted !!!";
    });

    auto conn3 = std::make_shared<QMetaObject::Connection>();
    *conn3  = connect(this, &QmlMqttClient::errorChanged, this, [this, &conn3, &connectionFunc](ClientError error){
        QObject::disconnect(*conn3);
        qDebug() << error;

        auto conn = std::make_shared<QMetaObject::Connection>();
        *conn = connect(&timer_, &QTimer::timeout, this, [this, connectionFunc, conn](){
            if (state() == 0){
                connectionFunc();
            }
            else {
                QObject::disconnect(*conn);
                timer_.stop();
            }

        });

        timer_.start(5000);
    });

    //setHostname("127.0.0.1");
    //setPort(1883);

    connectToHost();

    //FileManager f("/home/max/TestMqtt/input.txt");

    //qDebug() << f.getLineFromFile().value();
    //qDebug() << f.getLineFromFile().value();



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
