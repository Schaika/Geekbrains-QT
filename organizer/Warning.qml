import QtQuick 2.0
import QtQuick.Controls 2.15
BorderImage {
    property alias text: tooltip.text
    id: name
    source: "qrc:///img/mark.png"
    MouseArea{
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true
    }
    ToolTip{
        id: tooltip
        delay: 500
        timeout: 5000
        visible: mouseArea.containsMouse
        text: qsTr("placeholder")
    }
}
