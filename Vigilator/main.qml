pragma ComponentBehavior: Bound

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import Vigilator

Window {
    height: 640
    title: qsTr("Vigilator")
    visible: true
    width: 480

    Rectangle {
        color: "#ffffff"
        border.color: "#000000"
        border.width: 1
        id: header
        width: parent.width
        height: 52

        Image {
            fillMode: Image.Stretch
            height: 40
            id:  logo
            source: "resources/logo.svg"
            width: 40
            x: 6
            y: 6
        }

        Image {
            fillMode: Image.Stretch
            height: 32
            id:  name
            source: "resources/logo-name.svg"
            width: 137
            x: logo.x + 60;
            y: logo.y + 6;
        }
    }

    //Page {
    //    id: page
    //    anchors.fill: parent
    //}

    //! [MonitorService QML element]
    MonitorService {
        id: monitorService

        MonitorResource {
            id: manuel
            path: "/manuel-online/monitor"
        }

    }
    //! [MonitorService QML element]

    Connections {
        target: manuel
        // Closes the URL selection popup once we have received data successfully
        function onDataUpdated() {
            fetchTester.stop()
        }
    }

    ColumnLayout {
        id: holder
        spacing: 5
        y: header.height + 20;
        x: 20

        GridLayout {
            id: urlSelectionLayout
            columns: 2
            columnSpacing: 5
            rowSpacing: 5
            Layout.fillWidth: true
            enabled: !fetchTester.running

            Label {
                id: url1TextArea
                text: "https://manuelberoepskleding.nl"
            }
            Button {
                text: qsTr("Use")

                onClicked: fetchTester.update(url1TextArea.text)
            }
        }

        Timer {
            id: fetchTester
            interval: 2000

            function update(url) {
                monitorService.url = url
                manuel.refreshStatus()
                start()
            }
        }

        RowLayout {
            id: fetchIndicator
            Layout.fillWidth: true
            visible: fetchTester.running

            Label {
                text: qsTr("Validating status")
            }

            BusyIndicator {
                running: visible
                Layout.fillWidth: true
            }
        }

        RowLayout {
            id: result
            Layout.fillWidth: true
            visible: !fetchTester.running

            Label {
                text: manuel.data
            }
        }
    }
}

