import QtQuick.Window 2.12
import myclass.Handler 1.0
import QtQuick 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5

Window {
    property var first: true
    onAfterRendering: {
        if(first){
        _handler.init();
        first = false;
        }
    }

    id: mainWindow
    width: 800
    height: 600
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
marked:'+ismarked+';
mark_text:"'+marktext+'";
width: mainWindow.width;
height: 40}',
                                        list,
                                        "task_"+currentID);}
        onRemoveAll: removeall();
        onUpdateCounter: {
            counter.count = taskcount
        }
        onRevalidate:{
            recheck();
        }

    }

    function recheck(){
         list.children[_handler.currentID].marked = _handler.ismarked;
         list.children[_handler.currentID].mark_text = _handler.marktext;
       //  console.log(_handler.currentID);
       //  console.log(_handler.ismarked);
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
        property var count: 0
        id: counter
        anchors.left: _addButton.right
        height: _addButton.height
        anchors.top: _addButton.top
        text: qsTr("Текущих задач: " + count)
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.pointSize: _addButton.height*0.25
    }
    Button{
        id: _popup
        anchors.top: root.bottom
        anchors.right: root.right
        text: qsTr("Открыть таблицу")
        onClicked: {
            _handler.openWindow();
        }
        anchors.rightMargin: 15
    }

    Text {
        id: _task
        text: qsTr("Задача")
        width: root.width-95-95-40-30
        horizontalAlignment: "AlignHCenter"
    }
    Text {
        anchors.left: _task.right
        anchors.leftMargin: 5
        id: _date
        text: qsTr("Дата окончания")
        width: 95
        horizontalAlignment: "AlignHCenter"
    }
    Text {
        anchors.left: _date.right
        anchors.leftMargin: 5
        id: _progress
        text: qsTr("Прогресс")
        width: 95
        horizontalAlignment: "AlignHCenter"
    }
}
