import QtQuick 2.0
import QtQuick.Window 2.0

Window {
    id: root
    visible: true
    width: 800
    height: 600
    color: "#333333"

    Image {
        id: media
        anchors.fill: parent
        fillMode: Image.PreserveAspectFit

        focus: true
        Keys.onPressed: {
            console.log('pressed Key '+ event.text);
            if (event.key === Qt.Key_Return || event.key === Qt.Key_F) {
                root.visibility === Window.FullScreen ? root.showNormal() : root.showFullScreen()
            } else if (event.key === Qt.Key_Q) {
                Qt.quit();
            }
        }
    }

    Text {
        id: txt
        anchors.centerIn: parent
        text: "Hello World!"
        font.pointSize: 100
        color: "steelblue"
    }

    Connections {
        target: source

        onIncoming: {
//            source.test(cnt)
//            media.source=""
            media.source= "qrc:/img/img/location-pin.png"+Math.random()
        }
    }
    NumberAnimation {
        id: animation
        target: media
        property: "rotation"
        from: 0
        to: 360
        duration: 5000
    }

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        onEntered: {
            animation.running = true;
        }
        onClicked: {
            animation.running = true;
        }
    }

}
