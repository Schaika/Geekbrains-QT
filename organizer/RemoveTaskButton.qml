import QtQuick 2.0

BorderImage {
    id: name
    source: "qrc:///img/remove.png"
    signal clicked

    MouseArea{
        anchors.fill: parent
        onClicked: parent.clicked()
    }
}
