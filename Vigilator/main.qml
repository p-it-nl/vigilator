pragma ComponentBehavior: Bound

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick

import Vigilator

import "." as App

Window {
    height: 520
    id: window
    title: qsTr("Vigilator")
    visible: true
    width: 360
    color: "#ffffff"

    ColumnLayout {
        spacing: 0
        anchors.fill: parent

        RowLayout {
            id: topbar
            Layout.fillWidth: true
            Layout.minimumHeight: 40
            Layout.preferredHeight: 50
            Layout.maximumHeight: 60

            Image {
                source: "resources/logo.svg"
                Layout.fillWidth: false
                Layout.minimumWidth: 30
                Layout.preferredWidth: 40
                Layout.maximumWidth: 50
                Layout.minimumHeight: 30
                Layout.preferredHeight: 40
                Layout.maximumHeight: 50
                Layout.margins: 10
            }

            Rectangle {
                color: 'plum'
                Layout.fillWidth: true
                Layout.minimumWidth: 100
                Layout.preferredWidth: 200
                Layout.minimumHeight: topbar.Layout.minimumHeight
                Layout.preferredHeight: topbar.Layout.preferredHeight
                Layout.maximumHeight: topbar.Layout.maximumHeight
            }
        }

        ColumnLayout {
            anchors.top: topbar.bottom
            Layout.fillWidth: true
            id: resources

            RowLayout {
                Rectangle {
                    color: "lightpink"
                    Layout.fillWidth: true
                    Layout.minimumWidth: 100
                    Layout.preferredWidth: 200
                    Layout.preferredHeight: 100
                }
            }

            RowLayout {
                Rectangle {
                    color: "blue"
                    Layout.fillWidth: true
                    Layout.minimumWidth: 100
                    Layout.preferredWidth: 200
                    Layout.preferredHeight: 100
                }
            }

            RowLayout {
                Rectangle {
                    color: "yellow"
                    Layout.fillWidth: true
                    Layout.minimumWidth: 100
                    Layout.preferredWidth: 200
                    Layout.preferredHeight: 100
                }
            }
        }
    }


    /*
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

    ColumnLayout {
        Layout.minimumWidth: parent.width
        id: holder
        y: header.height + 20;
        width: parent.width
        spacing: 20

        Frame {
            width: parent.width
            spacing: 20

            Column {
                spacing: 80
                width: parent.width
                height: 100
                x: 6

                RadioButton {
                    text: qsTr("First")
                    checked: true
                    width: parent.width
                }
                RadioButton {
                    id: button
                    text: qsTr("Second")
                    width: parent.width
                }
                RadioButton {
                    text: qsTr("Third")
                    width: parent.width
                }
            }
        }
    }
    */
}

