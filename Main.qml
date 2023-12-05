import QtQuick 2.8
import QtQuick.Window 2.2
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.1
import MqttClient 1.0


Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Qt Quick MQTT Subscription Example")
    id: root

    property var tempSubscription: 0

    MqttClient {
        id: client
        hostname: hostnameField.text
        port: portField.text
    }

    /*
    FileManager{
        filePath_: filepathField.text
    }
    */


    ListModel {
        id: messageModel
    }

    function addMessage(payload)
    {
        messageModel.insert(0, {"payload" : payload})

        if (messageModel.count >= 100)
            messageModel.remove(99)
    }

    GridLayout {
        anchors.fill: parent
        anchors.margins: 10
        columns: 2

        Label {
            text: "host:"
            enabled: client.state === MqttClient.Disconnected
        }

        TextField {
            id: hostnameField
            Layout.fillWidth: true
            text: "test.mosquitto.org"
            placeholderText: "<Enter host running MQTT broker>"
            enabled: client.state === MqttClient.Disconnected
        }

        Label {
            text: "port:"
            enabled: client.state === MqttClient.Disconnected
        }

        TextField {
            id: portField
            Layout.fillWidth: true
            text: "1883"
            placeholderText: "<Port>"
            inputMethodHints: Qt.ImhDigitsOnly
            enabled: client.state === MqttClient.Disconnected
        }

        Label {
            text: "username:"
            enabled: client.state === MqttClient.Disconnected
        }

        TextField {
            id: usernameField
            Layout.fillWidth: true
            text: ""
            placeholderText: "may be empty"
            inputMethodHints: Qt.ImhDigitsOnly
            enabled: client.state === MqttClient.Disconnected
        }

        Label {
            text: "password:"
            enabled: client.state === MqttClient.Disconnected
        }

        TextField {
            id: passwordField
            Layout.fillWidth: true
            text: ""
            placeholderText: "may be empty"
            inputMethodHints: Qt.ImhDigitsOnly
            enabled: client.state === MqttClient.Disconnected
        }



        Label {
            text: "filepath:"
            enabled: client.state === MqttClient.Disconnected
        }

        TextField {
            id: filepathField
            Layout.fillWidth: true
            text: ""
            placeholderText: "filepath"
            inputMethodHints: Qt.ImhDigitsOnly
            enabled: client.state === MqttClient.Disconnected
        }



        RowLayout {
            // enabled: client.state === MqttClient.Connected
            Layout.columnSpan: 2
            Layout.fillWidth: true

            Label {
                text: "topic:"
            }

            TextField {
                id: subField
                text: "piklema/test"
                placeholderText: "<Subscription topic>"
                Layout.fillWidth: true
                enabled: tempSubscription === 0
            }



            Button {
                id: connectButton
                Layout.columnSpan: 2
                Layout.fillWidth: true
                text: client.state === MqttClient.Connected ? "Disconnect" : "RUN"
                onClicked: {
                    if (client.state === MqttClient.Connected) {
                        client.disconnectFromHost()
                        messageModel.clear()
                        tempSubscription.destroy()
                        tempSubscription = 0
                    } else
                        client.setUsername(usernameField.text)
                        client.setPort(portField.text)
                        client.setPassword(passwordField.text)
                        client.connectToHost()
                        client.sendDataFromFile(filepathField.text)

                }
            }
        }

        ListView {
            id: messageView
            model: messageModel
            height: 300
            width: 200
            Layout.columnSpan: 2
            Layout.fillHeight: true
            Layout.fillWidth: true
            clip: true
            delegate: Rectangle {
                width: messageView.width
                height: 30
                color: index % 2 ? "#DDDDDD" : "#888888"
                radius: 5
                Text {
                    text: payload
                    anchors.centerIn: parent
                }
            }
        }

        Label {
            function stateToString(value) {
                if (value === 0)
                    return "Disconnected"
                else if (value === 1)
                    return "Connecting"
                else if (value === 2)
                    return "Connected"
                else
                    return "Unknown"
            }

            Layout.columnSpan: 2
            Layout.fillWidth: true
            color: "#333333"
            text: "Status:" + stateToString(client.state) + "(" + client.state + ")"
            enabled: client.state === MqttClient.Connected
        }
    }
}
