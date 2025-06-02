
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import ResourceItem 1.0

ColumnLayout {
    Frame {
        Layout.fillWidth: true

        ListView {
            anchors.fill: parent
            clip: true
            id: resources
            implicitHeight: 350
            implicitWidth: 350
            model: resourceModel

            delegate: Item {
                width: ListView.view.width
                height: 50

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        resourceModel.onItemClicked(index, model.name);
                    }
                }

                ColumnLayout {
                    Layout.fillWidth: true
                    anchors.fill: parent
                    RowLayout {
                        state: model.state

                        states: [
                            State {
                                name: "ok"
                                PropertyChanges {
                                    target: rowIcon
                                    source: "resources/ok.svg"
                                }
                            },
                            State {
                                name: "warning"
                                PropertyChanges {
                                    target: rowIcon
                                    source: "resources/warning.svg"
                                }
                            },
                            State {
                                name: "error"
                                PropertyChanges {
                                    target: rowIcon
                                    source: "resources/error.svg"
                                }
                            }
                        ]

                        Image {
                            id: rowIcon
                            Layout.preferredWidth: 24
                            Layout.preferredHeight: 24
                            Layout.margins: 8
                            source: "resources/ok.svg"
                        }

                        Text {
                            Layout.fillWidth: true
                            text: model.name
                        }
                    }

                    Rectangle{
                        Layout.fillWidth: true
                        height: 1
                        color: "#52443d"
                    }
                }
            }
        }
    }
}
