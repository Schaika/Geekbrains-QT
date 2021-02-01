#include "taskcontainer.h"


taskcontainer::taskcontainer(QDate _date, QString _taskText, quint16 _progress)
	{
		date = _date;
		taskText = _taskText;
		progress = _progress;
	}

quint16 taskcontainer::getProgress() const
	{
		return progress;
	}

void taskcontainer::setProgress(const quint16& value)
	{
		progress = value;
	}

QString taskcontainer::getTaskText() const
	{
		return taskText;
	}

void taskcontainer::setTaskText(const QString& value)
	{
		taskText = value;
	}

QDate taskcontainer::getDate() const
	{
		return date;
	}

void taskcontainer::setDate(const QDate& value)
	{
		date = value;
	}

quint32 taskcontainer::getID() const
	{
		return ID;
	}

void taskcontainer::setID(const quint32& value)
	{
		ID = value;
	}
