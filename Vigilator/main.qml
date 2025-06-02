import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Vigilator

import "." as App

Window {
    height: 620
    id: window
    title: qsTr("Vigilator")
    visible: true
    width: 480
    color: "#ffffff"

    ColumnLayout {
        width: window.width
        Layout.fillWidth: true

        RowLayout {
            id: topbar
            Layout.fillWidth: true
            Layout.leftMargin: 20
            Layout.maximumHeight: 60
            Layout.minimumHeight: 40
            Layout.preferredHeight: 50
            Layout.topMargin: 5
            spacing: 20

            Image {
                source: "resources/logo.svg"
                Layout.fillWidth: false
                Layout.maximumWidth: 50
                Layout.minimumWidth: 30
                Layout.preferredWidth: 40
                Layout.maximumHeight: 50
                Layout.minimumHeight: 30
                Layout.preferredHeight: 40
            }

            Rectangle {
                id: menu
                Layout.fillWidth: true
                Layout.minimumHeight: topbar.Layout.minimumHeight
                Layout.preferredHeight: topbar.Layout.preferredHeight
                Layout.maximumHeight: topbar.Layout.maximumHeight
            }
        }

        ResourcesList {
            Layout.fillWidth: true
        }
    }
}

