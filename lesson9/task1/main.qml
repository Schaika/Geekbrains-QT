import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5
import myclass.Handler 1.0
Window {
    property var first: true
    onAfterRendering: {
        if(first){
        _handler.init();
        first = false;
        }
    }

    id: mainWindow
    width: 640
    height: 480
    visible: true
    title: qsTr("Органайзер")

    Handler{
        id: _handler
        onAppendTask: {
            var ex = Qt.createQmlObject('
SingleItem{onClicked_remove: _handler.removeTask(parseInt(_ID));
onChanged: {_handler.editTask(_ID,curtask,curdate,parseInt(progress))}
_ID:"'+currentID+'";
curdate:"'+currentDate+'";
progress:"'+currentProgress+'";
curtask:"'+currentText+'";
width: mainWindow.width;
height: mainWindow.height/10}',
                                        list,
                                        "task_"+currentID);}
        onRemoveAll: removeall();
    }

    function removeall()
    {
    for (var i = 0; i < list.children.length; i++)
    {
        list.children[i].destroy()
    //console.log("item "+i);
    }
    }
    ScrollView {
        id: root
        ScrollBar.horizontal.policy: ScrollBar.AlwaysOff;
        ScrollBar.vertical.policy: ScrollBar.AlwaysOn;
        y:_task.height;
        width: mainWindow.width
        height: mainWindow.height - _addButton.height - y
        ColumnLayout {
            id:list
            }
        }
    AddTaskButton{
        id: _addButton
        anchors.left: root.left
        anchors.top: root.bottom
        onClicked: {
            _handler.addTask();
        }
    }
    Text {
        id: _task
        text: qsTr("Задача")
        width: root.width-95-95-mainWindow.height/10-15
        horizontalAlignment: "AlignHCenter"
    }
    Text {
        anchors.left: _task.right
        id: _date
        text: qsTr("Дата окончания")
        width: 95
        horizontalAlignment: "AlignHCenter"
    }
    Text {
        anchors.left: _date.right
        id: _progress
        text: qsTr("Прогресс")
        width: 95
        horizontalAlignment: "AlignHCenter"
    }
}
