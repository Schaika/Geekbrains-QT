#include "handler.h"
#include <QSqlDatabase>
#include <QtDebug>
handler::handler(QObject *parent) : QObject(parent)
	{
	}

void handler::validate()
	{
		_marktext = "";
		if (_currentText.isEmpty()) _marktext+=tr("Текст задачи пуст!\n");
		if (_currentDate.isEmpty()) _marktext+=tr("Дата введена неверно!\n");
		_marktext.chop(1);
		if(_marktext.isEmpty()) _marked=false; else _marked=true;
	}

void handler::removeTask(int localID)
	{
		dbmanager->removeTask(localID);
		rebuild();
	}

void handler::init()
	{
		dbmanager = new SQLite("tasklist.db");
		rebuild();
	}

void handler::editTask(int localID, QString text, QString date, int progress)
	{
		dbmanager->updateTask(localID,text,date,progress);
		_currentText = text;
		_currentDate = SQLite::parseDate(date).toString("dd.MM.yyyy");
		_currentProgress = progress;
		_currentID = localID;
		validate();
		emit revalidate();
	}

void handler::addTask()
	{
		dbmanager->addTask();
		rebuild();
	}

void handler::openWindow()
	{
		if (wgt != nullptr) delete wgt;
		wgt = new popupWindow(nullptr,dbmanager->getModel());
		wgt->setWindowFlags(wgt->windowFlags() & ~Qt::WindowContextHelpButtonHint);
		connect(dbmanager,SIGNAL(updateModel(QSqlQueryModel*)),wgt,SLOT(updateModel(QSqlQueryModel*)));

		wgt->show();
	}

void handler::closing()
	{
		if(wgt != nullptr){
		wgt->close();
		}
	}

void handler::rebuild(){
		emit removeAll();
		auto taskList = dbmanager->getList();
		for (int i=0;i<taskList.count();i++){
			taskList[i].setID(i);
			taskcontainer obj = taskList.at(i);
			QDate date = obj.getDate();
			_currentDate = date.toString("dd.MM.yyyy");
			_currentID = obj.getID();
			_currentText = obj.getTaskText();
			_currentProgress = obj.getProgress();
			validate();
			emit appendTask();
		}
		emit updateCounter();
	}

QString handler::marktext() const
	{
		return _marktext;
	}

int handler::taskCount() const
	{
		return dbmanager->getTotal();
    }

bool handler::mark() const
    {
		return _marked;
    }

int handler::currentProgress() const
	{
		return _currentProgress;
	}

QString handler::currentDate() const
	{
		return _currentDate;
	}

QString handler::currentText() const
	{
		return _currentText;
	}

int handler::currentID() const
	{
		return _currentID;
	}
