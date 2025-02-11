
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
            implicitHeight: 250
            implicitWidth: 250

            model: ResourceItemModel {
                list: resourcesList
            }

            delegate: RowLayout {
                width: parent.width

                CheckBox {
                    checked: model.done
                    onClicked: model.done = checked

                }
                TextField {
                    Layout.fillWidth: true
                    onEditingFinished: model.description = text
                    text: model.description
                }
            }
        }
    }

    RowLayout {
        Button {
            Layout.fillWidth: true
            onClicked: resourcesList.appendItem()
            text: qsTr("Add new item")
        }
        Button {
            Layout.fillWidth: true
            onClicked: resourcesList.removeCompletedItems()
            text: qsTr("Remove completed")
        }
    }
}
