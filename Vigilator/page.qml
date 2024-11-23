import QtQuick

Rectangle {
    anchors.fill: parent
    color: "#ffffff"
    id: page

    Image {
        fillMode: Image.Stretch
        height: 60
        id:  logo
        source: "resources/logo.svg"
        width: 60
        x: topLeftRect.x
        y: topLeftRect.y
    }

    Image {
        fillMode: Image.Stretch
        height: 42
        id:  name
        source: "resources/logo-name.svg"
        width: 167
    }

    Rectangle {
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.leftMargin: 20
        anchors.topMargin: 20
        border.color: "#808080"
        color: "#00ffffff"
        height: 60
        id: topLeftRect
        width: 60

        MouseArea {
            id: mouseArea
            anchors.fill: parent
        }
    }

    Rectangle {
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.leftMargin: 20
        anchors.bottomMargin: 20
        border.color: "#808080"
        color: "#00ffffff"
        height: 60
        id: bottomLeftRect
        width: 60

        MouseArea {
            id: mouseAreaBottom
            anchors.fill: parent
        }
    }

    Rectangle {
        anchors.right: parent.right
        anchors.top: parent.Center
        anchors.rightMargin: 20
        anchors.topMargin: 20
        border.color: "#808080"
        color: "#00ffffff"
        height: 60
        id: centerRightRect
        width: 60

        MouseArea {
            id: mouseAreaCenter
            anchors.fill: parent
        }
    }

    states: [
        State {
            name: "State1"

            PropertyChanges {
                target: logo
                x: topLeftRect.x
                y: topLeftRect.y
            }
        },
        State {
            name: "State2"

            PropertyChanges {
                target: logo
                x: bottomLeftRect.x
                y: bottomLeftRect.y
            }
        },
        State {
            name: "State3"

            PropertyChanges {
                target: logo
                x: centerRightRect.x
                y: centerRightRect.y
            }
        }
    ]

    Connections {
        target: mouseArea
        function onClicked()
        {
            page.state = "State1"
        }
    }

    Connections {
        target: mouseAreaBottom
        function onClicked()
        {
            page.state= "State2"
        }
    }

    Connections {
        target: mouseAreaCenter
        function onClicked()
        {
            page.state= "State3"
        }
    }

    transitions: [
        Transition {
            id: toState1
            ParallelAnimation {
                SequentialAnimation {
                    PauseAnimation {
                        duration: 0
                    }

                    PropertyAnimation {
                        target: logo
                        property: "y"
                        duration: 200
                    }
                }

                SequentialAnimation {
                    PauseAnimation {
                        duration: 0
                    }

                    PropertyAnimation {
                        target: logo
                        property: "x"
                        duration: 200
                    }
                }
            }
            to: "State1"
            from: "State2,State3"
        },
        Transition {
            id: toState2
            ParallelAnimation {
                SequentialAnimation {
                    PauseAnimation {
                        duration: 0
                    }

                    PropertyAnimation {
                        target: logo
                        property: "y"
                        easing.type: Easing.OutBounce
                        duration: 1006
                    }
                }

                SequentialAnimation {
                    PauseAnimation {
                        duration: 0
                    }

                    PropertyAnimation {
                        target: logo
                        property: "x"
                        easing.type: Easing.OutBounce
                        duration: 1006
                    }
                }
            }
            to: "State2"
            from: "State1,State3"
        },
        Transition {
            id: toState3
            ParallelAnimation {
                SequentialAnimation {
                    PauseAnimation {
                        duration: 0
                    }

                    PropertyAnimation {
                        target: logo
                        property: "y"
                        easing.type: Easing.InOutQuad
                        duration: 2000
                    }
                }

                SequentialAnimation {
                    PauseAnimation {
                        duration: 0
                    }

                    PropertyAnimation {
                        target: logo
                        property: "x"
                        easing.type: Easing.InOutQuad
                        duration: 2000
                    }
                }
            }
            to: "State3"
            from: "State1,State2"
        }
    ]
}
