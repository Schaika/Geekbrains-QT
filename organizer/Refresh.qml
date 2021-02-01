import QtQuick 2.0

BorderImage {
    id: name
    source: "qrc:///img/refresh.png"
    signal clicked
    width:  50
    height: 50

    MouseArea{
        anchors.fill: parent
        onClicked: parent.clicked()
    }
}
