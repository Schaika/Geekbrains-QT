import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
Item {
    id:root
    property var _elementmargin: 5
    property var _ID
    property alias curtask: _task.text
    property alias curdate: _date.text
    property alias progress: _progress.text
    signal clicked_remove;
    signal changed;
    TextField{
        id: _task
        anchors.left: root.left
        anchors.leftMargin: _elementmargin
        width: root.width - (_date.width + _progress.width + _remove.width) - _elementmargin*7
        placeholderText: qsTr("Введите текст")
        horizontalAlignment: "AlignHCenter"
        onTextEdited: root.changed()

    }
    TextField{
        id: _date
        anchors.left: _task.right
        anchors.leftMargin: _elementmargin
        width: 95
        horizontalAlignment: "AlignHCenter"
        inputMask: "00.00.0000"
        onTextEdited: root.changed()
    }
    TextField{
        id: _progress
        anchors.left: _date.right
        anchors.leftMargin: _elementmargin
        width: 95
        horizontalAlignment: "AlignHCenter"
        validator: IntValidator{bottom: 0; top: 10;}
        onTextEdited: {
            check()
            root.changed()
        }
    }
    Button{
        id: _remove
        anchors.left: _progress.right
        anchors.leftMargin: _elementmargin
        width: 75
        text: qsTr("Удалить")
        onClicked: root.clicked_remove()
    }
    function check(){
        if (_progress.text>10) _progress.text = 10;
    }
}

